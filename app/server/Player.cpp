#include "include/json.hpp"
#include "Player.hpp"

// Player::Player() {}

Player::Player(nlohmann::json& info, int sockfd) {

}

//Saves player's data in a json file
void Player::save() const {

    std::ifstream fichierJson("server/assets/Players.json");
    if(fichierJson) {
        std::string ligne;

	while(getline(fichierJson, ligne)) {
            std::cout << ligne << std::endl;

	}
    } else {
        std::cout << "ERROR: Impossible to open the file." << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Player& c) {
    os << c._username << c._victory << "\t" << c._defeat << "\n";
    return os;
}
