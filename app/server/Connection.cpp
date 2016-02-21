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
            
            //TODO create a new thread specific to the player to communicate with him
        }
    }
}
