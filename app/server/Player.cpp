#include "include/json.hpp"
#include "Player.hpp"

Player::Player(nlohmann::json& info, int sockfd) : _sockfd(sockfd) {
    _username = info["username"];
    _password = info["password"];
    _victories = info["victories"];
    _defeats = info["defeats"];
    for (size_t i = 0; i < info["decks"].size(); ++i) {
        std::string deckName = info["decks"][i]["deckName"];
        std::vector<unsigned> cards = info["decks"][i]["cards"];
        _decks.push_back(new Deck(deckName, cards));
    }

    std::vector<unsigned> collection_cards= info["collection"];
    _collection = Collection(collection_cards);
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
        res = true;
    }

    return res;
}

/**
 * Add a deck to the player
 *
 * @param deck the to wich must be add
 * @return True if all is ok (do nothing if not)
 */
bool Player::addDeck(Deck* deck) {
    bool res = false;
    if(_decks.size() <= MAX_DECKS) {
        _decks.push_back(deck);
        res = true;
    }

    return res;
}

bool Player::operator<(const Player &other) const {
    return ((*this).getVictories() < other.getVictories());
}

bool Player::operator>(const Player &other) const {
    return !((*this) < other);
}

bool Player::operator==(const std::string &other_name) const {
    return ((*this).getName() == other_name);
}

std::string Player::serialise() const {
    nlohmann::json info;
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

    return info.dump();
}

std::ostream& operator<<(std::ostream& os, const Player& c) {
    os << c._username << c.getVictories() << "\t" << c.getDefeats() << "\n";
    return os;
}

std::string& operator<<(std::string& str, const Player& c) {
    str.append(c.getName() + "\t\t" +
	       std::to_string(c.getVictories()) + "\t\t" +
	       std::to_string(c.getDefeats()) + "\n");
    return str;
}

/* Send a packet to the client trought the socket
 * @param packet : the packet to send. Default pointer to manage only one type
 * @param size : the packet global size, to be sure to send all data
 * @throw : an error occure during sending packet, must catch it
 */
void Player::sendPacket(Packet::packet *packet, size_t size) {
    try {
        if (send(_sockfd, packet, size, 0) != size) {
            throw std::string("Tout le packet n'a pas été envoyé à "+getName());
        }
    } catch (const std::string &message) {
        WizardLogger::error(message);
        throw;
    }
}

/* Entry point for threaded player
 * Keep alive socket connection and listen for client message
 */
void Player::recvLoop() {
    /* Read data from buffer */
    ssize_t readSize;
    
    /* Loop to wait with select client messages */
    while(1) {
        /* Allocate maximum size for an unknow incoming packet */
        void *packet = malloc(Packet::packetMaxSize);
        
        /* Try to get packet from server */
        readSize = recv(_sockfd, packet, Packet::packetMaxSize, 0);
        if (readSize <= 0) {
            WizardLogger::error("Connexion interrompue avec le client : "+getName());
            break;
        } else if (readSize < Packet::packetSize) {
            WizardLogger::error("Impossible de récupérer un packet du client : "+getName());
        } else {
            /* We terminate resize memory alloc */
            packet = realloc(packet, readSize);
            
            /* We send the packet to the PacketManager for verification and interpretation */
            PacketManager::managePacket(this, reinterpret_cast<Packet::packet*>(packet));
        }
        
        /* Free packet from memory */
        free(packet);
    }
    
    /* ERROR occure so we must remove current Player from loaded list */
    WizardLogger::error("La connexion avec le client \""+getName()+"\" semble avoir été interrompue !");
    //TODO remove player
}

/* Unsuscribe player from player online
 * Close socket and interrupt player's thread
 */
void Player::logout() {
    //TODO remove player from list and game, etc...
    pthread_exit(0);
}
