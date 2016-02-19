#include "Connection.hpp"
#include "common/WizardLogger.hpp"

/* Initialize connection between client and server
 * @param hostName: hostName where server run
 * @throw : Cannot connect to the server, we must stop the client
 */
Connection::Connection(char *hostName) {
    try {
        /* Test to convert hostName to IP or throw an error */
        if ((host=gethostbyname(hostName)) == NULL) { 
            WizardLogger::error("Impossible de récupérer les infos de connexion au serveur");
            throw std::system_error(EFAULT, std::system_category()); /* Convert errno to exception */
        }

        /* SYS_CALL to create a new socket */
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == -1) {
            WizardLogger::error("Impossible d'avoir un nouveau socket pour le serveur");
            throw std::system_error(EFAULT, std::system_category());
        }
        
        /* We create informations for use with a socket */
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);
        server_addr.sin_addr = *((struct in_addr*)host->h_addr);

        /* We test if struct has good size */
        memset(&(server_addr.sin_zero), '\0', 8);
        
        /* We connect to the server using socket informations */
        WizardLogger::info("Tentative de connexion au serveur");
        if (connect(clientSocket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
            WizardLogger::error("Impossible de se connecter au serveur");
            throw std::system_error(EFAULT, std::system_category());
        }

        /* We create a new Thread for listen the server informations */
        if (pthread_create(&recvThread, NULL, recvLoop, (void*)&clientSocket) == -1) {
            WizardLogger::error("Impossible de créer un nouveau thread pour écouter le serveur");
            throw std::system_error(EFAULT, std::system_category());
        }
        
        WizardLogger::info("Connexion réussie");
    } catch (const std::system_error &error) {
        /* We try the error, program must close after that so all memory will be clear */
        throw;
    }
}

Connection::~Connection() {
    /* Close thread and socket */
    if (recvThread != NULL)
        pthread_cancel(recvThread);
    close(clientSocket);
}

/* Send a packet to the server trought the socket
 * @param packet : the packet to send. Default pointer to manage only one type
 * @param size : the packet global size, to be sure to send all data
 * @throw : an error occure during sending packet, CLI/GUI must catch it
 */
void Connection::sendPacket(Packet *packet, long unsigned int size) {
    try {
        if (send(clientSocket, &size, sizeof(int), 0) != sizeof(int)) {
            throw std::string("Impossible de renseigner la taille du packet à envoyer");
        }
        if (send(clientSocket, packet, size, 0) != size) {
            throw std::string("Tout le packet n'a pas été envoyé");
        }
    } catch (const std::string &message) {
        WizardLogger::error(message);
        throw;
    }
}

/* Threaded loop to wait and receve server packet
 * It can be cancelled at any time, normally override block from recv
 * @param data : int* to the tchatSocked
 */
void* Connection::recvLoop(void* data) {
    /* Enable asynchronous cancel (thread can be canceled at any time) from deferred */
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, (int*) PTHREAD_CANCEL_DEFERRED);
    
    /* Convert to get clientSocket addr */
    int clientSocket = *((int *)data);
    
    /* To know how much memory we need */
    int packetSize;
    
    /* Loop to wait with select server messages */
    while(1) {
        /* Try to get next packet size, maybe it's a default one ? */
        if (recv(clientSocket, &packetSize, sizeof(int), 0) == 0) {
            WizardLogger::warning("Impossible de connaître la taille du packet");
            packetSize = Packet::packetSize;
        }
        
        /* Allocate precise size for packet */
        void *packet = malloc(packetSize);
        
        /* Try to get packet from server */
        if (recv(clientSocket, packet, packetSize, 0) == 0) {
            WizardLogger::error("Impossible de récupérer le packet du serveur");
        } else {
            /* We send the packet to the CommService for interpretation */
            CommService::managePacket(reinterpret_cast<Packet::packet*>(packet));
        }
        
        /* Free packet from memory */
        free(packet);
    }
}
