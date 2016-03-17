#include "Connection.hpp"

/* Initialize connection between client and server
 * @param hostName: hostName where server run
 * @throw : Cannot connect to the server, we must stop the client
 */
Connection::Connection(char* hostName) {
    try {
        /* Test to convert hostName to IP or throw an invalid_argument */
        if ((host=gethostbyname(hostName)) == NULL) {
            std::string error = "Impossible de trouver ";
            error += hostName;
            error += " : ";
            error += hstrerror(h_errno);
            throw std::invalid_argument(error);
        }

        /* We don't support IPv6 */
        if (host->h_addrtype != AF_INET) {
            throw std::domain_error("Nous ne supportons pas les adresses IPv6");
        }

        /* SYS_CALL to create a new socket */
        _clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (_clientSocket == -1) {
            std::string error = "Impossible d'avoir un nouveau socket pour le serveur : ";
            error += strerror(errno);
            throw std::runtime_error(error);
        }

        /* We create informations for use with a socket */
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);
        server_addr.sin_addr = *((struct in_addr*)host->h_addr);

        /* We test if struct has good size */
        memset(&(server_addr.sin_zero), '\0', 8);

        /* Configure socket to use TCP keepalive protocole */
        setsockopt(_clientSocket, SOL_SOCKET, SO_KEEPALIVE, &_keepon, sizeof(_keepon));
        #ifdef __linux__
        setsockopt(_clientSocket, IPPROTO_TCP, TCP_KEEPIDLE, &_keepidle, sizeof(_keepidle));
        #else
        setsockopt(_clientSocket, IPPROTO_TCP, TCP_KEEPIDLE_ALL, &_keepidle, sizeof(_keepidle));
        #endif
        setsockopt(_clientSocket, IPPROTO_TCP, TCP_KEEPCNT, &_keepcnt, sizeof(_keepcnt));
        setsockopt(_clientSocket, IPPROTO_TCP, TCP_KEEPINTVL, &_keepintvl, sizeof(_keepintvl));

        /* We connect to the server using socket informations */
        WizardLogger::info("Tentative de connexion au serveur");
        if (connect(_clientSocket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
            std::string error = "Impossible de se connecter au serveur : ";
            error += strerror(errno);
            throw std::runtime_error(error);
        }

        /* We create a new Thread for listen the server informations */
        if (pthread_create(&_recvThread, NULL, recvLoop, (void*)&_clientSocket) == -1) {
            std::string error = "Impossible de créer un nouveau thread pour écouter le serveur : ";
            error += strerror(errno);
            throw std::runtime_error(error);
        }

        WizardLogger::info("Connexion réussie");
    } catch (const std::invalid_argument &error) {
        WizardLogger::fatal("Impossible d'établire une connection avec le serveur", error.what());
        throw;
    } catch (const std::domain_error &error) {
        WizardLogger::fatal("Impossible d'établire une connection avec le serveur", error.what());
        throw;
    } catch (const std::runtime_error &error) {
        WizardLogger::fatal("Impossible d'établire une connection avec le serveur", error.what());
        throw;
    } catch (const std::exception &error) {
        WizardLogger::fatal("Erreur inconnue durant la connexion au serveur", error.what());
        throw;
    }
}

Connection::~Connection() {
    /* Close thread and socket */
    pthread_cancel(_recvThread);
    close(_clientSocket);
}

/* Send a packet to the server trought the socket
 * @param packet : the packet to send. Default pointer to manage only one type
 * @param size : the packet global size, to be sure to send all data
 * @throw : an error occure during sending packet, CLI/GUI must catch it
 */
void Connection::sendPacket(Packet::packet *packet, size_t size) {
    try {
        if (send(_clientSocket, packet, size, 0) != size) {
            throw std::string("Tout le packet n'a pas été envoyé");
        }
    } catch (const std::string &message) {
        WizardLogger::error(message);
        throw;
    }
}

/* Threaded loop to wait and receve server packet
 * It can be cancelled at any time, normally override block from recv
 * @param data : int* to the clientSocked
 */
void* Connection::recvLoop(void* data) {
    /* Enable asynchronous cancel (thread can be canceled at any time) from deferred */
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, (int*) PTHREAD_CANCEL_DEFERRED);

    /* Convert to get _clientSocket addr */
    int clientSocket = *static_cast<int*>(data);

    /* Read data from buffer */
    ssize_t readSize;

    /* Loop to wait with select server messages */
    while(1) {
        /* Allocate maximum size for an unknow incoming packet */
        void *packet = malloc(Packet::packetMaxSize);

        /* Try to get packet from server */
        readSize = recv(clientSocket, packet, Packet::packetMaxSize, 0);
        if (readSize <= 0) {
            WizardLogger::fatal("Connexion interrompue avec le serveur");
            break;
        } else if (readSize < Packet::packetSize) {
            WizardLogger::error("Impossible de récupérer un packet du serveur");
        } else {
            /* We terminate resize memory alloc */
            packet = realloc(packet, readSize);

            /* We send the packet to the PacketManager for verification and interpretation */
            PacketManager::managePacket(reinterpret_cast<Packet::packet*>(packet));
        }

        /* Free packet from memory */
        free(packet);
    }

    /* ERROR occure so we must inform the user */
    wizardDisplay->displayFatalError("La connexion avec le serveur semble avoir été interrompue !");
    return nullptr;
}
