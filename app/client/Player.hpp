#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "CacheManager.hpp"

class Player {
    std::string _username;
    unsigned _collection[MAX_CARDS];
    int _decks[MAX_DECKS];
    std::string _friendsList[MAX_FRIENDS];
    unsigned _victories;
    unsigned _defeats;

public:
    Player(std::string username, unsigned collection[MAX_CARDS], int decks[MAX_DECKS], std::string friends[MAX_FRIENDS],
    unsigned victories, unsigned defeats) : _username(username), _victories(victories), _defeats(defeats) {
        for (int i = 0 ; i < MAX_CARDS ; ++i) _collection[i] = collection[i];
        for (int i = 0 ; i < MAX_DECKS ; ++i) _decks[i] = decks[i];
        for (int i = 0 ; i < MAX_FRIENDS ; ++i) _friendsList[i] = friends[i];
    }
    
    /* Setter */
    inline void addCardCollection(unsigned ID) { _collection[ID]++; }
    inline void addDeck(int ID) { for (int i = 0 ; i < MAX_DECKS ; ++i) if (_decks[i] == -1) _decks[i] = ID; }
    inline void removeDeck(int ID) { for (int i = 0 ; i < MAX_DECKS ; ++i) if (_decks[i] == ID) _decks[i] = -1; }
    inline void addFriend(std::string pseudo) {
        for (int i = 0 ; i < MAX_FRIENDS ; ++i) if (_friendsList[i] == "") _friendsList[i] = pseudo;
    }
    inline void removeFriend(std::string pseudo) {
        for (int i = 0 ; i < MAX_FRIENDS ; ++i) if (_friendsList[i] == pseudo) _friendsList[i] = "";
    }
    inline void adjudicateVictory() { _victories++; };
    inline void adjudicateDefeat() { _defeats++; }
    
    /* Getter */
    inline std::string getName() const { return _username; }
    inline unsigned *getCollection() { return _collection; }
    inline int *getDeck() { return _decks; }
    inline std::string *getFriends() { return _friendsList; }
    inline unsigned getVictories() const { return _victories; }
    inline unsigned getDefeats() const { return _defeats; }
    
    ~Player() = default;
};

#endif  /* PLAYER_HPP */
