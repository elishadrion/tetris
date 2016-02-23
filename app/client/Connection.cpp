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
        _clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (_clientSocket == -1) {
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
        if (connect(_clientSocket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
            WizardLogger::error("Impossible de se connecter au serveur");
            throw std::system_error(EFAULT, std::system_category());
        }

        /* We create a new Thread for listen the server informations */
        if (pthread_create(&_recvThread, NULL, recvLoop, (void*)&_clientSocket) == -1) {
            WizardLogger::error("Impossible de créer un nouveau thread pour écouter le serveur");
            throw std::system_error(EFAULT, std::system_category());
        }
        
        WizardLogger::info("Connexion réussie");
    } catch (const std::system_error &error) {
        /* We throw the error, program must close after that so all memory will be clear */
        throw;
    }
}

Connection::~Connection() {
    /* Close thread and socket */
    if (_recvThread != NULL)
        pthread_cancel(_recvThread);
    close(_clientSocket);
}

/* Send a packet to the server trought the socket
 * @param packet : the packet to send. Default pointer to manage only one type
 * @param size : the packet global size, to be sure to send all data
 * @throw : an error occure during sending packet, CLI/GUI must catch it
 */
void Connection::sendPacket(Packet *packet, long unsigned int size) {
    try {
        if (send(_clientSocket, &size, sizeof(int), 0) != sizeof(int)) {
            throw std::string("Impossible de renseigner la taille du packet à envoyer");
        }
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
 * @param data : int* to the tchatSocked
 */
void* Connection::recvLoop(void* data) {
    /* Enable asynchronous cancel (thread can be canceled at any time) from deferred */
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, (int*) PTHREAD_CANCEL_DEFERRED);
    
    /* Convert to get _clientSocket addr */
    int clientSocket = *((int *)data);
    
    /* Read data from buffer */
    int readSize;
    
    /* Loop to wait with select server messages */
    while(1) {
        /* Allocate maximum size for an unknow incoming packet */
        void *packet = malloc(Packet::packetMaxSize);
        
        /* Try to get packet from server */
        while ((readSize = recv(clientSocket, packet, Packet::packetMaxSize, 0)) <= 0);
        if (readSize < Packet::packetSize) {
            WizardLogger::error("Impossible de récupérer le packet du serveur");
        } else {
            /* We terminate resize memory alloc */
            realloc(packet, readSize);
            
            /* We send the packet to the PacketManager for verification and interpretation */
            PacketManager::managePacket(reinterpret_cast<Packet::packet*>(packet));
        }
        
        /* Free packet from memory */
        free(packet);
    }
}
