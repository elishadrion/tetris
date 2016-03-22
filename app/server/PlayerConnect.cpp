#include "PlayerConnect.hpp"

#include "PlayerInGame.hpp"

Player* PlayerConnect::getPlayerPtr() {
    return (_pIG == nullptr) ? _player : _pIG;
}


/**
 * Constructor
 * @param sockfd socket for the connection
 */
PlayerConnect::PlayerConnect(int sockfd, Player* player): _sockfd(sockfd),
    _player(player), _pIG(nullptr) { }


/**
 * Send a packet to the client trought the socket
 *
 * @param packet : the packet to send. Default pointer to manage only one type
 * @param size : the packet global size, to be sure to send all data
 * @throw : an error occure during sending packet, must catch it
 */
void PlayerConnect::sendPacket(Packet::packet *packet, size_t size) {
    try {
        if (send(_sockfd, packet, size, 0) != size) {
            throw std::string("Tout le packet n'a pas été envoyé à "+ getPlayerPtr()->getName());
        }
    } catch (const std::string &message) {
        WizardLogger::error(message);
        throw;
    }
}

/**
 * Entry point for threaded player
 * Keep alive socket connection and listen for client message
 */
void PlayerConnect::recvLoop() {
    /* Read data from buffer */
    ssize_t readSize;
    
    /* Packet's data size (for buffer) */
    size_t dataSize;

    /* Loop to wait with select client messages */
    while(1) {
        /* Allocate size to read the two first int (ID and size) */
        void *packet = malloc(Packet::packetSize);

        /* Try to get packet from server */
        readSize = recv(_sockfd, packet, Packet::packetSize, 0);
        if (readSize <= 0) {
            break;
        } else if (readSize < Packet::packetSize) {
            WizardLogger::error("Impossible de récupérer un packet du client : "+getPlayerPtr()->getName());
        } else {
            /* If there are other informations, we need to read the buffer again */
            dataSize = reinterpret_cast<Packet::packet*>(packet)->size;
            if (dataSize > 0) {
                /* We terminate resize memory alloc */
                packet = realloc(packet, Packet::packetSize+dataSize);
                
                /* Get all data and combine array (and clean memory after) */
                readSize = recv(_sockfd, packet+Packet::packetSize, dataSize, 0);
                //TODO what do we do ??? if (readSize < dataSize) throw std::string("Impossible de récupérer les données du packet");
            }

            /* We send the packet to the PacketManager for verification and interpretation */
            PacketManager::managePacket(getPlayerPtr(),reinterpret_cast<Packet::packet*>(packet));
        }

        /* Free packet from memory */
        free(packet);
    }

    /* ERROR occure so we must remove current Player from loaded list */
    WizardLogger::error("La connexion avec le client \""+getPlayerPtr()->getName()+"\" semble avoir été interrompue !");
    //TODO remove player
}

/**
 * Define the player InGame
 * @param pIG playerInGame
 */
void PlayerConnect::setPlayerInGame(PlayerInGame* pIG) {
    _pIG = pIG;
}


/**
 * Overwrite Player information with PlayerInGame information
 *
 * @param pIG playerInGame
 */
void PlayerConnect::removePlayerInGame(PlayerInGame* pIG) {
    _player->overwrite(*pIG); // overwrite
    _pIG = nullptr; // remove PlayerInGame
}

/**
 * Unsuscribe player from player online
 * Close socket and interrupt player's thread
 */
void PlayerConnect::logout() {
    //TODO remove player from list and game, etc...
    pthread_exit(0);
}
