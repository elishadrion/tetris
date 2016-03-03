#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player {

    std::string _username;
    int _collection[MAX_CARDS];
    int _decks[MAX_DECKS];
    std::string _friendsList[MAX_FRIENDS];
    unsigned _victories;
    unsigned _defeats;

public:
    Player(std::string username, int *collection, int *decks, std::string *friends,
    unsigned victories, unsigned defeats) : _username(username), _collection(collection), _decks(decks),
    _friendsList(friends), _victories(victories), _defeats(defeats) {}
    
    /* Setter */
    inline void addCardCollection(int ID) { _collection[ID]++; }
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
    inline int *getCollection() { return _collection; }
    inline int *getDeck() { return _decks; }
    inline std::string *getFriends() { return _friendsList; }
    inline unsigned getVictories() const { return _victories; }
    inline unsigned getDefeats() const { return _defeats; }
    
    ~Player() = default;
};

#endif  /* PLAYER_HPP */
