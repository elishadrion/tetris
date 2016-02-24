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
    Collection collection;
    std::vector<Deck*> _decks;


    virtual void save() const;
protected:
    std::vector<Deck*> getListDeck() {return _decks;}
    unsigned _victories;
    unsigned _defeats;

public:
    Player() = default; // Must exist for PlayerInGame()
    Player(nlohmann::json&, int sockfd = 0);

    inline void adjudicateVictory() {_victories++;};
    inline Error addCardCollection(Card* c) {return collection.addCard(c);}
    inline void adjudicateDefeat() {_defeats++;}
    inline void updateSockfd(int a) {_sockfd = a;}
    inline std::string getName() const {return _username;}
    inline std::string getPass() const {return _password;}
    inline unsigned getVictories() const {return _victories;}
    inline unsigned getDefeats() const {return _defeats;}

    Deck* getDeck(std::string deckName);
    bool removeDeck(Deck*);


    friend std::ostream& operator<<(std::ostream&, const Player&);
    friend std::string& operator<<(std::string&, const Player&);
    bool operator==(const std::string&) const;
    bool operator==(const Packet::loginRequestPacket&) const;
    bool operator<(const Player&) const;
    virtual ~Player() = default;
};



#endif  /* PLAYER_HPP */
