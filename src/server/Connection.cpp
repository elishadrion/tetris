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
            std::string error = "Impossible d'initialiser la file1 d'attente du socket : ";
            error += hstrerror(h_errno);
            throw std::runtime_error(error);
        }

        _sinSize = sizeof(struct sockaddr_in);
    } catch (const std::runtime_error &error) {
        std::cout << "Impossible de lancer le socket serveur" << std::endl;
        throw;
    } catch (const std::exception &error) {
        std::cout << "Erreur inconnue durant la préparation du socket serveur" << std::endl;
        throw;
    }
}

Connection::~Connection() {
    std::cout << "Fermeture du serveur" << std::endl;
    close(_serverSocket);
}

//On attend une connexion client et on lance un thread pour le gérer
void Connection::start() {
    std::cout << "Serveur en attente de connexion client" << std::endl;
    int client_socket;
    while(1) {
        client_socket = accept(_serverSocket, (struct sockaddr *)&client_addr, &_sinSize);
        if (clientSocket == -1) {
            std::cout << "Impossible d'accepter la connexion d'un client" << std::endl;
        } else {
            std::cout << "Client " << inet_ntoa(_client_address.sin_addr) << " s'est connecté!" << std::endl;
            //On essaie de lancer le thread, si pas possible, on ferme la connexion
            try {
                std::thread t(&Connection::manage_player, this, client_socket);
                t.detach();
            } catch (std::system_error& e) {
                std::cout << "Impossible de créer un nouveau thread pour le client" << std::endl;
                close(client_socket);
            }
        }
    }
}

void Connection::manage_player(int client_socket) {
    size_t read_size;
    size_t size;
    Player *new_player;
    size = sizeof(Packet::loginRequestPacket);
    Packet::loginRequestPacket *packet = new Packet::loginRequestPacket();

    //Tant qu'on est pas connecté, on loop
    bool logged_in = false;
    while(!logged_in) {
        readSize = recv(clientSocket, packet, size, 0);
        if (readSize <= 0) {
            std::cout << "Login interrompu, connexion avec le client perdu" << std::endl;
            break;
        } else if (readSize < size) {
            std::cout << "Le packet reçu est incomplet" << std::endl;
        } else {
            //Vérification si le paquet est valide
            if (packet->ID != Packet::LOGIN_REQ_ID && packet->ID != Packet::REGIST_REQ_ID) {
                std::cout << "Le packet reçu n'est pas un packet de login" << std::endl;
            } else if (packet->size != sizeof(packet->pseudo)+sizeof(packet->password)) {
                std::cout << "Paquet de login corrompu reçu" std::endl;
            } else {
                std::string pseudo = packet->pseudo;
                std::string password = packet->password;

                //On détermine si c'est pour le login ou inscription
                if (packet->ID == Packet::REGIST_REQ_ID) {
                    new_player = PlayerManager::signup(pseudo, password, client_socket);
                } else {
                    new_player = PlayerManager::login(pseudo, password, client_socket);
                }

                /* If no player object created we fail and restart */
                if (new_player != nullptr) {
                    logged_in = true;
                } else {
                    sendResponse(-1, client_socket);
                }
            }
        }
    }

    //Libère la mémoire
    delete packet;

    if (logged_in) {
        send_success(new_player, client_socket);
        usleep(100);
        Packet::packet *endLogin = new Packet::packet();
        endLogin->ID = Packet::LOGIN_COMPLETE_ID;
        send(clientSocket, endLogin, sizeof(Packet::packet), 0);
        delete endLogin;
        newPlayer->receive();
        PlayerManager::logOut(newPlayer);
    }
}

void Connection::send_response(int errorCode, int socket) {
    Packet::intPacket *loginResult = new Packet::intPacket();
    loginResult->data = errorCode;
    loginResult->ID = Packet::LOGIN_RES_ID;
    send(socket, loginResult, sizeof(Packet::intPacket), 0);
    delete loginResult;
}

void Connection::send_success(Player* player, int socket) {
    Packet::playerInfoPacket *player_packet = new Packet::playerInfoPacket();

    std::string pseudo = player->get_name();

    player_packet->data.victories = player->get_victories();
    player_packet->data.defeats = player->get_defeats();
    player_packet->pseudo = pseudo.c_str();

    send(socket, playerPacket, sizeof(Packet::playerInfoPacket), 0);
    delete playerPacket;
}
