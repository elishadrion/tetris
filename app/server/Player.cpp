#include "include/json.hpp"
#include "Player.hpp"

Player::Player(nlohmann::json& info, int sockfd) {
    _username = info["username"];
    _password = info["password"];

}

/**
 * Get the deck with this name
 *
 * @param deckname the name of the deck
 * @return the deck (or nullptr if not found)
 */
Deck* Player::getDeck(std::string deckName) {
    return Deck::getDeck(deckName, _decks);
}


/**
 * Remove a Deck
 *
 * @param deck to remove
 * @return True if all is ok (cann't delete if one deck)
 */
bool Player::removeDeck(Deck* deck) {
    bool res = false;
    if(_decks.size() > 1) {
        delete deck;
        // remove to memory ?
        // TO DO: @carlos JSON
        res = true;
    }

    return res;
}


bool Player::operator<(const Player &other) const {
    return ((*this).getVictories() < other.getVictories());
}

bool Player::operator==(const std::string &other_name) const {
    return ((*this).getName() == other_name);
}

std::string Player::serialise() const {
    nlohmann::json info;
    info["name"] = _username;
    info["password"] = _password;

    return info.dump();
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
