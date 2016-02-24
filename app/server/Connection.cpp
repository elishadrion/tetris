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
            WizardLogger::error("Impossible de s'attribuer un socket pour le serveur");
            throw std::system_error(EFAULT, std::system_category()); /* Convert errno to exception */
        }

        /* We bind socket with informations */
        if (bind(_serverSocket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
            WizardLogger::error("Impossible d'initialiser le socket server");
            throw std::system_error(EFAULT, std::system_category());
        }

        /* We configure waiting list for the socket */
        if (listen(_serverSocket, BACKLOG) == -1) {
            WizardLogger::error("Impossible d'initialiser la fils d'attente du socket");
            throw std::system_error(EFAULT, std::system_category());
        }

        _sinSize = sizeof(struct sockaddr_in);
    } catch (const std::system_error &error) {
        /* We throw the error, program must close after that so all memory will be clear */
        throw;
    }
}

Connection::~Connection() {
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
            WizardLogger::error("Impossible d'accepter la connexion d'un client", std::system_error(EFAULT, std::system_category()));
        } else {
            /* We need to append a char* so we must use string to do that */
            std::string *info = new std::string("Nouvelle connexion pour le client : ");
            WizardLogger::info(info->append(inet_ntoa(client_addr.sin_addr))); //TODO don't support IPv6
            delete info; /* Don't forget to free memory */

            /* We create a new Thread for listen the server informations */
            if (pthread_create(&_newThread, NULL, newPlayerThread, (void*)&clientSocket) == -1) {
                WizardLogger::error("Impossible de créer un nouveau thread pour le client");
                close(clientSocket);
            } else {
                /* We register these new thread to keep trace of it and esaly manage it */
                _clientThreads.push_back(move(_newThread));
            }
        }
    }
}

void* Connection::newPlayerThread(void* data) {
    /* Enable asynchronous cancel (thread can be canceled at any time) from deferred */
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, (int*) PTHREAD_CANCEL_DEFERRED);

    /* Convert to get clientSocket addr */
    int clientSocket = *static_cast<int *>(data);

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
        if (readSize < size) {
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
                    //newPlayer = PlayerManager::signIn(pseudo, password, clientSocket);
                } else {
                    //newPlayer = PlayerManager::logIn(pseudo, password, clientSocket);
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

    Connection::sendResponse(0, clientSocket);

    //TODO we lets Player entity to manage communication from now (must be non returnant)
}

void Connection::sendResponse(int errorCode, int socket) {
    Packet::loginResultPacket *loginResult = new Packet::loginResultPacket();
    loginResult->resultCode = errorCode;
    send(socket, loginResult, sizeof(Packet::loginResultPacket), 0);
    free(loginResult);
}
