#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <algorithm>

#include "common/Constants.hpp"
#include "common/Error.hpp"

class CacheManager;
#include "CacheManager.hpp"


class Player {

    static Player* instance;

    std::string _username;
    unsigned _collection[MAX_CARDS];
    std::vector<std::string> _decks;
    std::vector<unsigned> _listCardDeck;
    std::string _friendsList[MAX_FRIENDS];
    unsigned _victories;
    unsigned _defeats;
    CacheManager *_cm;


public:
    Player(std::string username, unsigned collection[MAX_CARDS], std::vector<std::string> decks,
           std::string friends[MAX_FRIENDS],unsigned victories, unsigned defeats);
    
    /* Setter */
    inline void addCardCollection(unsigned ID) { _collection[ID]++; }
    inline void adjudicateVictory() { _victories++; }
    inline void adjudicateDefeat() { _defeats++; }
    Error addDeck(std::string);
    Error removeDeck(std::string);
    void addFriend(std::string pseudo);
    void removeFriend(std::string pseudo);
    void addDeckCard(std::vector<unsigned>);
    
    /* Getter */
    inline std::string getName() const { return _username; }
    inline unsigned *getCollection() { return _collection; }
    inline std::vector<std::string> getDecks() { return _decks; }
    inline std::string *getFriends() { return _friendsList; }
    inline unsigned getVictories() const { return _victories; }
    inline unsigned getDefeats() const { return _defeats; }
    inline bool isDeckCardDefine() const { return _listCardDeck.size() > 0; }

    // Deck
    std::vector<unsigned> getCardDeck(std::string);
    void loadDeckCard();

    
    ~Player() = default;


    static Player* getPlayer() { return instance; }
};

#endif  /* PLAYER_HPP */
