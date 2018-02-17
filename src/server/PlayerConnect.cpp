#include "PlayerConnect.hpp"

PlayerConnect::PlayerConnect(int sockfd, Player* player): _sockfd(sockfd), _player(player) { }

void PlayerConnect::send_packet(Packet::packet *packet, size_t size) {
    try {
        if (send(_sockfd, packet, size, 0) != size) {
            throw std::string("Tout le packet n'a pas été envoyé à "+ get_player_ptr()->get_name());
        }
    } catch (const std::string &message) {
        std::cout << message << std::endl;
        throw;
    }
}

void PlayerConnect::receive() {
    ssize_t readSize;

    while(1) {

        void *packet = new Packet::packetMaxSize();

        readSize = recv(_sockfd, packet, Packet::packetMaxSize, 0);
        if (readSize <= 0) {
            break;
        } else if (readSize < Packet::packetSize) {
            std::cout << "Impossible de récupérer un packet du client : " + get_player_ptr()->get_name() << std::endl;
        } else {
            packet = realloc(packet, readSize);

            PacketManager::managePacket(getPlayerPtr(),reinterpret_cast<Packet::packet*>(packet));
        }

        free(packet);
    }

    std::cout << "La connexion avec le client \""+get_player_ptr()->get_name()+"\" semble avoir été interrompue !" << std::endl;
}

void PlayerConnect::logout() {
    PlayerManager::logOut(_player);
}
