#include "include/json.hpp"
#include "Player.hpp"

Player::Player(nlohmann::json& info, int sockfd) {

}

bool Player::operator<(const Player &other) const {
    return ((*this).getVictories() < other.getVictories());
}

bool Player::operator==(const std::string &other_name) const {
    return ((*this).getName() == other_name);
}

bool Player::operator==(const Packet::loginRequestPacket &req) const {
    return ( ((*this).getName() == req.pseudo) &&
	     ((*this).getPass() == req.password));
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
    os << c._username << c.getVictories() << "\t" << c.getDefeats() << "\n";
    return os;
}

std::string& operator<<(std::string& str, const Player& c) {
    str.append(c.getName() + "\t" +
	       std::to_string(c.getVictories()) + "\t" +
	       std::to_string(c.getDefeats()) + "\n");
    return str;
}
