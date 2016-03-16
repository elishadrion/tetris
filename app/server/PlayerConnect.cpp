#include "PlayerConnect.hpp"

#include "PlayerInGame.hpp"

Player* PlayerConnect::getPlayerPtr() {
    Player* ptr;
    if(_pIG == nullptr) {
        ptr = _player;
        WizardLogger::info("PConnect: player");
    } else {
        ptr = _pIG;
        WizardLogger::info("PConnect: player In Game");
    }

    return ptr;
    //return (_pIG == nullptr) ? _player : _pIG;
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

    /* Loop to wait with select client messages */
    while(1) {
        /* Allocate maximum size for an unknow incoming packet */
        void *packet = malloc(Packet::packetMaxSize);

        /* Try to get packet from server */
        readSize = recv(_sockfd, packet, Packet::packetMaxSize, 0);
        if (readSize <= 0) {
            WizardLogger::error("Connexion interrompue avec le client : "+getPlayerPtr()->getName());
            break;
        } else if (readSize < Packet::packetSize) {
            WizardLogger::error("Impossible de récupérer un packet du client : "+getPlayerPtr()->getName());
        } else {
            /* We terminate resize memory alloc */
            packet = realloc(packet, readSize);

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
