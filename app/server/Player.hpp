#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <fstream>

#include "include/json.hpp"

#include "common/Error.hpp"
#include "Collection.hpp"
#include "Deck.hpp"
#include "common/Packet.hpp"

#include "common/WizardLogger.hpp"


/**
 * One class per player.  This object stocks the socket to communicate with player
 * When the server starts, he must load all Players
 */
class Player {

    int _sockfd;
    std::string _username;
    std::string _password;
    Collection _collection;
    std::vector<Deck*> _decks;


protected:
    std::vector<Deck*> getListDeck() {return _decks;}
    unsigned _victories;
    unsigned _defeats;

public:
    Player(nlohmann::json&, int sockfd = 0);

    inline void adjudicateVictory() {_victories++;};
    inline void adjudicateDefeat() {_defeats++;}
    inline Error addCardCollection(Card* c) {return _collection.addCard(c);}
    inline void updateSockfd(int a) {_sockfd = a;}
    inline std::string getName() const {return _username;}
    inline std::string getPass() const {return _password;}
    inline unsigned getVictories() const {return _victories;}
    inline unsigned getDefeats() const {return _defeats;}

    Deck* getDeck(std::string deckName);
    bool removeDeck(Deck*);

    std::string serialise() const;
    friend std::ostream& operator<<(std::ostream&, const Player&);
    friend std::string& operator<<(std::string&, const Player&);
    bool operator==(const std::string&) const;
    bool operator<(const Player&) const;
    bool operator>(const Player&) const;
    virtual ~Player() = default;
};



#endif  /* PLAYER_HPP */
