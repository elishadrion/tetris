#include "Connection.hpp"

/* Initialize connection between client and server
 * @param hostName: hostName where server run
 * @throw : Cannot connect to the server, we must stop the client
 */
Connection::Connection(std::string address) {
    if ((_host=gethostbyname(address.c_str())) == NULL) {
        exit(1);
    }

    _socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_socketfd == -1) {
        std::cout << "\nImpossible de créer le socket!" << std::endl;
        exit(1);
    }

    _server_addr.sin_family = AF_INET;
    _server_addr.sin_port = htons(PORT);
    _server_addr.sin_addr = *((struct in_addr*)_host->h_addr);

    memset(&(_server_addr.sin_zero), '\0', 8);

    if (connect(_socketfd, (struct sockaddr *)&_server_addr, sizeof(struct sockaddr)) == -1) {
        std::cout << "Impossible de se connecter au serveur" << std::endl;
        exit(1);
    }

    /* We create a new Thread for listen the server informations */
    if (pthread_create(&_thread, NULL, receive, (void*)&_socketfd) == -1) {
        std::cout << "Impossible de créer un nouveau thread pour écouter le serveur" << std::endl;
        exit(1);
    }
    std::cout << "Client initialisé!" << std::endl;
}

Connection::~Connection() {
    /* Close thread and socket */
    pthread_cancel(_thread);
    close(_socketfd);
}

void Connection::send_packet(void* packet, size_t size) {
    if (send(_socketfd, packet, size, 0) != size) {
        WizardLogger::error("Tout le paquet n'a pas été envoyé");
    }
}

void* Connection::receive(void* data) {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, (int*) PTHREAD_CANCEL_DEFERRED);

    int socket = *static_cast<int*>(data);

    /* Read data from buffer */
    ssize_t readSize;

    /* Loop to wait with select server messages */
    while(1) {
        /* Allocate maximum size for an unknow incoming packet */
        void *packet = malloc(Packet::packetMaxSize);

        /* Try to get packet from server */
        readSize = recv(socket, packet, Packet::packetMaxSize, 0);
        if (readSize <= 0) {
            break;
        } else if (readSize < Packet::packetSize) {
            WizardLogger::error("Impossible de récupérer un packet du serveur " +
                                std::to_string(reinterpret_cast<Packet::packet*>(packet)->ID));
        } else {
            /* We terminate resize memory alloc */
            packet = realloc(packet, readSize);
            PacketManager::manage_packet(packet);
        }

        /* Free packet from memory */
        free(packet);
    }

    return nullptr;
}
