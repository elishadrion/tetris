#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

class Player {

    std::string _username;
    int _collection[200];
    std::vector<int> _decks;
    std::vector<std::string> _friendsList;
    unsigned _victories;
    unsigned _defeats;

public:
    Player(std::string username, int *collection, std::vector<int> decks, std::vector<std::string> friends,
    unsigned victories, unsigned defeats) : _username(username), _collection(collection), _decks(decks),
    _friendsList(friends), _victories(victories), _defeats(defeats) {}
    
    /* Setter */
    inline void addCardCollection(int ID) { _collection[ID]++; }
    inline void addDeck(int ID) { _decks.push_back(ID); }
    inline void removeDeck(int ID) { for (int i = 0 ; i < _decks.size() ; ++i) if (_decks[i] == ID) _decks.remove(i); }
    inline void addFriend(std::string pseudo) { _friendsList.push_back(pseudo); }
    inline void removeFriend(std::string pseudo) {
        for (int i = 0 ; i < _friendsList.size() ; ++i) if (_friendsList[i] == pseudo) _friendsList.remove(i);
    }
    inline void adjudicateVictory() { _victories++; };
    inline void adjudicateDefeat() { _defeats++; }
    
    /* Getter */
    inline std::string getName() const { return _username; }
    inline int *getCollection() { return _collection; }
    inline std::vector<int> getDeck() { return _decks; }
    inline std::vector<std::string> getFriends() { return _friendsList; }
    inline unsigned getVictories() const { return _victories; }
    inline unsigned getDefeats() const { return _defeats; }
    
    ~Player() = default;
};

#endif  /* PLAYER_HPP */
