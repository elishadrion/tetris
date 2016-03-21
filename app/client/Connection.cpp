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
        setsockopt(_clientSocket, IPPROTO_TCP, TCP_KEEPIDLE, &_keepidle, sizeof(_keepidle));
        setsockopt(_clientSocket, IPPROTO_TCP, TCP_KEEPCNT, &_keepcnt, sizeof(_keepcnt));
        setsockopt(_clientSocket, IPPROTO_TCP, TCP_KEEPINTVL, &_keepintvl, sizeof(_keepintvl));

        /* We connect to the server using socket informations */
        WizardLogger::info("Tentative de connexion au serveur");
        if (connect(_clientSocket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
            std::string error = "Impossible de se connecter au serveur : ";
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
    /* Close socket */
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

/* Listen for an incoming packet from server
 * @throw : an error occure during reading packet, CLI/GUI must catch it
 */
void Connection::recvPacket() {
    try {
        /* Read packet from buffer */
        ssize_t readSize;
        
        /* Packet's data size (for buffer) */
        size_t dataSize;

        /* Allocate size to read the two first int (ID and size) */
        void *packet = malloc(Packet::packetSize);

        /* Try to get packet from server */
        readSize = recv(_clientSocket, packet, Packet::packetSize, 0);
        if (readSize < Packet::packetSize) throw std::string("Impossible de récupérer un packet du serveur");
        
        /* If there are other informations, we need to read the buffer again */
        dataSize = reinterpret_cast<Packet::packet*>(packet)->size;
        if (dataSize > 0) {
            /* We resize memory alloc */
            packet = realloc(packet, dataSize);
            
            /* Get all data and combine array (and clean memory after) */
            readSize = recv(_clientSocket, packet+Packet::packetSize, dataSize, 0);
            if (readSize < dataSize) throw std::string("Impossible de récupérer les données du packet");
        }
            

        /* We send the packet to the PacketManager for verification and interpretation */
        PacketManager::managePacket(reinterpret_cast<Packet::packet*>(packet));

        /* Free packet from memory */
        free(packet);
    } catch (const std::string &message) {
        WizardLogger::error(message);
        throw;
    }
}
