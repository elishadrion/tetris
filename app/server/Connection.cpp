#include "Connection.hpp"

Connection::Connection() {
    try {
        /* We create informations for use with a socket */
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);
        server_addr.sin_addr.s_addr = INADDR_ANY;

        /* We check/fix size */
        memset(&(server_addr.sin_zero), '\0', 8);


        /* SYS_CALL to create a new socket */
        _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (_serverSocket == -1) {
            std::string error = "Impossible de s'attribuer un socket pour le serveur : ";
            error += hstrerror(h_errno);
            throw std::runtime_error(error);
        }

        /* If previous server crash, try to reuse his socket */
        if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &_reuse, sizeof(_reuse)) == -1) {
            std::string error = "Impossible de reutiliser socket : ";
            error += hstrerror(h_errno);
            throw std::runtime_error(error);
        }

        /* We bind socket with informations */
        if (bind(_serverSocket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
            std::string error = "Impossible d'initialiser le socket server : ";
            error += hstrerror(h_errno);
            throw std::runtime_error(error);
        }

        /* We configure waiting list for the socket */
        if (listen(_serverSocket, BACKLOG) == -1) {
            std::string error = "Impossible d'initialiser la fils d'attente du socket : ";
            error += hstrerror(h_errno);
            throw std::runtime_error(error);
        }

        _sinSize = sizeof(struct sockaddr_in);
    } catch (const std::runtime_error &error) {
        WizardLogger::fatal("Impossible de lancer le socket serveur", error.what());
        throw;
    } catch (const std::exception &error) {
        WizardLogger::fatal("Erreur inconnue durant la préparation du socket serveur", error.what());
        throw;
    }
}

Connection::~Connection() {
    WizardLogger::warning("Closing server connection");
    PlayerManager::savePlayers();
    close(_serverSocket);
}

/* Wait for client connection and start a dedicated thread for login/registration and game
 * Must be as fast as possible to manage more new connection in seconde
 * So we don't do anything after accepting connection and launching the thread
 * All client's communication are manage by these dedicated thread
 */
void Connection::mainLoop() {
    /* We wait for client connection */
    WizardLogger::info("Serveur en attente de connexion client");
    while(1) {
        /* Accept connection and create a new clientSocket */
        int clientSocket = accept(_serverSocket, (struct sockaddr *)&client_addr, &_sinSize);
        if (clientSocket == -1) {
            WizardLogger::error("Impossible d'accepter la connexion d'un client", std::runtime_error(hstrerror(h_errno)).what());
        } else {
            /* We need to append a char* so we must use string to do that */
            std::string *info = new std::string("Nouvelle connexion pour le client : ");
            WizardLogger::info(info->append(inet_ntoa(client_addr.sin_addr))); //TODO don't support IPv6
            delete info; /* Don't forget to free memory */

            /* Configure socket to use TCP keepalive protocole */
            setsockopt(clientSocket, SOL_SOCKET, SO_KEEPALIVE, &_keepon, sizeof(_keepon));
            setsockopt(clientSocket, IPPROTO_TCP, TCP_KEEPIDLE, &_keepidle, sizeof(_keepidle));
            setsockopt(clientSocket, IPPROTO_TCP, TCP_KEEPCNT, &_keepcnt, sizeof(_keepcnt));
            setsockopt(clientSocket, IPPROTO_TCP, TCP_KEEPINTVL, &_keepintvl, sizeof(_keepintvl));

            /* We create a new Thread for listen the server informations */
            if (pthread_create(&_newThread, NULL, newPlayerThread, (void*)&clientSocket) == -1) {
                WizardLogger::error("Impossible de créer un nouveau thread pour le client");
                close(clientSocket);
            }
        }
    }
}

void* Connection::newPlayerThread(void* data) {
    /* Enable asynchronous cancel (thread can be canceled at any time) from deferred */
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, (int*) PTHREAD_CANCEL_DEFERRED);

    /* Convert to get clientSocket addr */
    int clientSocket = *static_cast<int*>(data);

    size_t readSize;
    size_t size;
    Player *newPlayer;

    /* Allocate specific size for an login/register incoming packet */
    size = sizeof(Packet::loginRequestPacket);
    Packet::loginRequestPacket *packet = (Packet::loginRequestPacket*) malloc(size);

    /* Loop to test login/registration before accepting it */
    bool loginOK = false;
    while(!loginOK) {
        /* Try to get packet from server */
        readSize = recv(clientSocket, packet, size, 0);
        if (readSize <= 0) {
            WizardLogger::error("Login interrompu, connexion avec le client perdu");
            break;
        } else if (readSize < size) {
            WizardLogger::warning("Le packet reçu est incomplet");
        } else {
            /* Check if it's a valide packet */
            if (packet->ID != Packet::LOGIN_REQ_ID && packet->ID != Packet::REGIST_REQ_ID) {
                WizardLogger::warning("Le packet reçu n'est pas un packet de login");
            } else if (packet->size != sizeof(packet->pseudo)+sizeof(packet->password)) {
                WizardLogger::error("Paquet de login corrompu reçu");
            } else {
                /* Try to get a clean pseudo from packet */
                std::string pseudo = "";
                int i = 0;
                char ch;
                while((ch = packet->pseudo[i]) != NULL && ch != ' ') {
                    pseudo += ch;
                    ++i;
                }

                /* Try to get a clean password from packet */
                std::string password = "";
                i = 0;
                while((ch = packet->password[i]) != NULL && ch != ' ') {
                    password += ch;
                    ++i;
                }

                /* We check if it's a login or a registration and send pseudo/password */
                if (packet->ID != Packet::LOGIN_REQ_ID) {
                    newPlayer = PlayerManager::signUp(pseudo, password, clientSocket);
                } else {
                    newPlayer = PlayerManager::logIn(pseudo, password, clientSocket);
                }

                /* If no player object created we fail and restart */
                if (newPlayer != nullptr) {
                    loginOK = true;
                } else {
                    sendResponse(-1, clientSocket);
                }
            }
        }
    }

    /* Free packet from memory */
    free(packet);

    /* If login is ok, we launch recvloop from Player after sending player's info to client */
    if (loginOK) {
        sendSucess(newPlayer, clientSocket);
        usleep(100);
    
        /* Send all cards */
        for (int i = 1; i <= CardManager::getNbrCard(); ++i) {
            Card* card = CardManager::getCardById(i);
            if (card != nullptr) {
                PacketManager::sendCardInfo(newPlayer, card);
                Packet::packet *confirm = (Packet::packet*) malloc(sizeof(Packet::packet));
                readSize = recv(clientSocket, packet, sizeof(Packet::packet), 0);
                free(confirm);
            }
        }
        
        Packet::packet *endLogin = new Packet::packet();
        endLogin->ID = Packet::LOGIN_COMPLETE_ID;
        WizardLogger::info("Fin du chargement. Nombre de cartes: " +
                           std::to_string(CardManager::getNbrCard()));
        send(clientSocket, endLogin, sizeof(Packet::packet), 0);
        delete endLogin;
        
        newPlayer->recvLoop();
        
        /* Logout after deconnection */
        PlayerManager::logOut(newPlayer);
    }
}

void Connection::sendResponse(int errorCode, int socket) {
    Packet::intPacket *loginResult = new Packet::intPacket();
    loginResult->data = errorCode;
    loginResult->ID = Packet::LOGIN_RES_ID;
    send(socket, loginResult, sizeof(Packet::intPacket), 0);
    delete loginResult;
}

void Connection::sendSucess(Player* player, int socket) {
    Packet::playerInfoPacket *playerPacket = new Packet::playerInfoPacket();

    /* Get collection */
    std::vector<unsigned> collection = player->getCollection()->getCardsId();

    /* Get pseudo */
    std::string pseudo = player->getName();

    /* Add player's info to packet */
    for (int i = 0 ; i < pseudo.size() ; ++i) playerPacket->data.pseudo[i] = pseudo[i];
    for (int i = 0 ; i < collection.size() ; ++i) playerPacket->data.collection[i] = collection[i];

    std::vector<Deck*> listDeck = player->getListDeck();
    for(unsigned allDeck = 0; allDeck < MAX_DECKS; ++allDeck) {
        // Variable
        unsigned i = 0;
        unsigned current = allDeck*MAX_DECK_NAME;

        if(allDeck < listDeck.size()) {
            std::string nomDeck = static_cast<Deck*>(listDeck[allDeck])->getName();
            for(; i < nomDeck.size(); ++i) playerPacket->data.decks[current+i] = nomDeck[i];
        }

        for(; i < MAX_DECK_NAME; ++i) playerPacket->data.decks[current+i] = ' ';
    }


    //TODO playerPacket->data.friendsList = player->getName(); /!\ voir client/PacketManager::playerInfo(...)
    playerPacket->data.victories = player->getVictories();
    playerPacket->data.defeats = player->getDefeats();

    /* Send informations */
    send(socket, playerPacket, sizeof(Packet::playerInfoPacket), 0);
    delete playerPacket;
}
