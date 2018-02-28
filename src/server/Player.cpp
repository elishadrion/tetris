#include "Player.hpp"

void Player::send_packet(void* packet, size_t size) {
    try {
        if (send(_sockfd, packet, size, 0) != size) {
            throw std::string("Tout le packet n'a pas été envoyé à "+ get_username());
        }
    } catch (const std::string &message) {
        WizardLogger::error(message);
        throw;
    }
}

void Player::receive() {
    ssize_t readSize;
    while(1) {
        void* packet = malloc(Packet::packetMaxSize);

        readSize = recv(_sockfd, packet, Packet::packetMaxSize, 0);
        if (readSize <= 0) {
            break;
        } else if (readSize < Packet::packetSize) {
            WizardLogger::warning("Impossible de récupérer un packet du client : " + get_username());
        } else {
            packet = realloc(packet, readSize);

            PacketManager::manage_packet(this, packet);
        }

        free(packet);
    }

    WizardLogger::warning("La connexion avec le client \""+get_username()+"\" semble avoir été interrompue !");
}

void Player::logout() {
    PlayerManager::logout(this);
}
