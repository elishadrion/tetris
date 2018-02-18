#include "PlayerManager.hpp"
#include <fstream>

std::vector<Player*> PlayerManager::_connected = std::vector<Player*>();

bool PlayerManager::player_connected(const std::string& usr) {
    for (size_t i = 0; i < _connected.size(); i++) {
        Player* current = _connected.at(i);
        
        if (current->get_name() == usr) {
            return true;
        }
    }
    return false;
}

bool PlayerManager::player_existing(const std::string& usr) {
    csv::Parser file = csv::Parser("../../data/database.csv");
    for (unsigned i = 0; i < file.rowCount(); i++) {
        if (file[i][0] == usr) {
            return true;
        }
    }
    return false;
}

Player* PlayerManager::login(std::string username, std::string password, int sockfd) {
    Player* player = nullptr;
    if (!player_connected(username)) {
        csv::Parser file = csv::Parser("../../data/database.csv");
        for (unsigned i = 0; i < file.rowCount(); i++) {
            if (file[i][0] == username && file[i][1] == password) {
                player = new Player(username, sockfd);
                _connected.push_back(player);
                player->set_sockfd(sockfd);
                break;
            }
        }
    }
    return player;
}

Player* PlayerManager::signup(std::string username, std::string password, int sockfd) {

    Player* player = nullptr;

    if(username.size() > MAX_PSEUDO_SIZE) {
        username = username.substr(0, MAX_PSEUDO_SIZE);
    }

    if (!player_existing(username)) {
        std::ofstream outfile;
        outfile.open("../../data/database.csv", std::ios_base::app);
        outfile << "\n" << username << "," << password << std::endl;
        player = new Player(username, sockfd);
        _connected.push_back(player);
        player->set_sockfd(sockfd);
    }

    return player;
}


void PlayerManager::logout(Player* player) {
    for (size_t i = 0; i < _connected.size(); i++) {
        Player* current = _connected.at(i);

	    if (current == player) {
	        _connected.erase(_connected.begin()+i);
	        return;
	    }
    }
}
