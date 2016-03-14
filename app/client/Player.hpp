#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

#include "common/Constants.hpp"
class CacheManager;
#include "CacheManager.hpp"


class Player {

    static Player* instance;


    std::string _username;
    unsigned _collection[MAX_CARDS];
    int _decks[MAX_DECKS];
    std::string _friendsList[MAX_FRIENDS];
    unsigned _victories;
    unsigned _defeats;
    CacheManager *_cm;
    
    /* In-game infos */
    bool _inGame;
    std::vector<int> _hand;
    int _deckSize;
    int _trashSize;
    int _ennemyPosed[MAX_POSED_CARD];
    int _posed[MAX_POSED_CARD];
    std::string _ennemy;


public:
    Player(std::string username, unsigned collection[MAX_CARDS], int decks[MAX_DECKS],
           std::string friends[MAX_FRIENDS],unsigned victories, unsigned defeats);
    
    /* Setter */
    inline void addCardCollection(unsigned ID) { _collection[ID]++; }
    inline void adjudicateVictory() { _victories++; }
    inline void adjudicateDefeat() { _defeats++; }
    void addDeck(int ID);
    void removeDeck(int ID);
    void addFriend(std::string pseudo);
    void removeFriend(std::string pseudo);
    
    /* Getter */
    inline std::string getName() const { return _username; }
    inline unsigned *getCollection() { return _collection; }
    inline int *getDeck() { return _decks; }
    inline std::string *getFriends() { return _friendsList; }
    inline unsigned getVictories() const { return _victories; }
    inline unsigned getDefeats() const { return _defeats; }
    
    /* Setter in-game */
    inline void setGame(bool game) { _inGame = game; }
    inline void drawCard(int ID) { _hand.push_back(ID); }
    inline void dropCard(int ID) {
        for(int i = 0; i < _hand.size(); ++i)
            if(_hand[i] == ID) _hand.erase(_hand.begin()+i);
    }
    inline void changeDeck(int amount) { _deckSize += amount; }
    inline void changeTrash(int amount) { _trashSize += amount; }
    inline void ennemyPose(int ID) {
        for(int i = 0; i < MAX_POSED_CARD; ++i)
            if(_ennemyPosed[i] == -1) _ennemyPosed[i] = ID;
    }
    inline void ennemyDrop(int ID) {
        for(int i = 0; i < MAX_POSED_CARD; ++i)
            if(_ennemyPosed[i] == ID) _ennemyPosed[i] = -1;
    }
    inline void pose(int ID) { for(int i = 0; i < MAX_POSED_CARD; ++i) if(_posed[i] == -1) _posed[i] = ID; }
    inline void drop(int ID) { for(int i = 0; i < MAX_POSED_CARD; ++i) if(_posed[i] == ID) _posed[i] = -1; }
    inline void setEnnemy(std::string ennemy) { _ennemy = ennemy; }
    
    /* Getter in-game */
    inline bool isGame() const { return _inGame; }
    inline std::vector<int> *getHand() { return &_hand; }
    inline int getDeckSize() const { return _deckSize; }
    inline int getTrashSize() const { return _trashSize; }
    inline int *getEnnemyPosed() { return _ennemyPosed; }
    inline int *getPosed() { return _posed; }
    inline std::string getEnnemy() const { return _ennemy; }
    
    ~Player() = default;


    static Player* getPlayer() { return instance; }
};

#endif  /* PLAYER_HPP */
