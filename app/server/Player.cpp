#include "include/json.hpp"
#include "Player.hpp"

Player::Player(nlohmann::json& info, int sockfd): _playerConnect(new PlayerConnect(sockfd, this)) {
    _username = info["name"];
    _password = info["password"];
    _victories = info["victories"];
    _defeats = info["defeats"];

    for (size_t i = 0; i < info["decks"].size(); ++i) {
        std::string deckName = info["decks"][i]["deckName"];
        std::vector<unsigned> cards = info["decks"][i]["cards"];
        _decks.push_back(new Deck(deckName, cards));
    }

    for (size_t i = 0; i < info["friends"].size(); ++i) {
        //TODO Player* player = PlayerManager::findPlayerByName(info["friends"][i]);
        //if (player != nullptr)
            //_friends.push_back(player);
    }

    std::vector<unsigned> collection_cards= info["collection"];
    _collection = Collection(collection_cards);

}

/**
 * Get the ration (victories/(victories+defeats))
 */
unsigned Player::getRatio() const {
    unsigned res = 0;
    unsigned total = getVictories()+getDefeats();
    if(total > 0) {
        res = getVictories()/total;
    }

    return res;
}

/**
 * Update the socket for connexion
 * @param sock new socket
 */
void Player::updateSockfd(int sock) {
    _playerConnect->updateSockfd(sock);
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
Error Player::removeDeck(Deck* deck) {
    Error res = Error::MustOneDeckMin;

    if(_decks.size() > 1) {
        _decks.erase(
            std::remove(_decks.begin(), _decks.end(), deck),
            _decks.end());
        delete deck;
        res = Error::NoError;
    }

    return res;
}

/**
 * Add a deck to the player
 *
 * @param deck the to wich must be add
 * @return True if all is ok (do nothing if not)
 */
Error Player::addDeck(Deck* deck) {
    Error res = Error::MaxDeck;

    if(_decks.size() < MAX_DECKS) {
        _decks.push_back(deck);
        res = Error::NoError;
    }

    return res;
}

bool Player::operator<(const Player &other) const {
    return this->getRatio() < other.getRatio();
}

bool Player::operator>(const Player &other) const {
    return !((*this) < other);
}

bool Player::operator==(const std::string &other_name) const {
    return ((*this).getName() == other_name);
}

nlohmann::json Player::serialise() const {
    nlohmann::json info;
    std::cout << _username << "\n";
    info["name"] = _username;
    info["password"] = _password;
    info["defeats"] = _defeats;
    info["victories"] = _victories;
    info["collection"] = _collection.getCardsId();
    info["decks"];
    for (size_t i = 0; i < _decks.size(); ++i) {
        nlohmann::json deck;
        deck["deckName"] = _decks.at(i) -> getName();
        deck["cards"] = _decks.at(i) -> getCardsId();
        info["decks"].push_back(deck);
    }

    return info;
}

// Not used now
std::ostream& operator<<(std::ostream& os, const Player& c) {
    os << c._username << c.getVictories() << "\t" << c.getDefeats() << "\n";
    return os;
}

// Not used now
std::string& operator<<(std::string& str, const Player& c) {
    str.append(c.getName() + "\t\t" +
	       std::to_string(c.getVictories()) + "\t\t" +
	       std::to_string(c.getDefeats()) + "\n");
    return str;
}

/**
 * Send a packet to the client trought the socket
 * @param packet : the packet to send. Default pointer to manage only one type
 * @param size : the packet global size, to be sure to send all data
 * @throw : an error occure during sending packet, must catch it
 */
void Player::sendPacket(Packet::packet *packet, size_t size) {
    _playerConnect->sendPacket(packet, size);
}

/**
 * Entry point for threaded player
 * Keep alive socket connection and listen for client message
 */
void Player::recvLoop() {
    _playerConnect->recvLoop();
}

/**
 * Unsuscribe player from player online
 * Close socket and interrupt player's thread
 */
void Player::logout() {
    _playerConnect->logout();
}


void Player::setPlayerInGame(PlayerInGame* pIG) {
    _playerConnect->setPlayerInGame(pIG);
}

void Player::removePlayerInGame(PlayerInGame* pIG) {
    _playerConnect->removePlayerInGame(pIG);
}

void Player::overwrite(const Player& player) {
    _username = player._username;
    _password = player._password;
    _collection = player._collection;
    _playerConnect = player._playerConnect;

    _decks = player._decks;
    _victories = player._victories;
    _defeats = player._defeats;
}
