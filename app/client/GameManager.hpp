#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <vector>
#include <string>

#include "Card.hpp"
#include "common/Constants.hpp"
#include "common/WizardLogger.hpp"
#include "PacketManager.hpp"


class GameManager {

    static GameManager* _instance;

    bool _inGame;
    int _nbrTurn;
    bool _isTurn;
    std::string _deckName; // Selected deck
    std::vector<Card*> _hand;
    unsigned _adverseHandNumber;
    std::vector<Card*> _trash;
    Card* _posed[MAX_POSED_CARD];
    Card* _ennemyPosed[MAX_POSED_CARD];
    std::string _ennemy;

    unsigned _heal;
    unsigned _adverseHeal;

    unsigned _energy;
    unsigned _adverseEnergy;


public:
    static GameManager* getInstance();

    GameManager(std::string);

    // Getters
    inline bool isGame() const { return _instance != nullptr; }
    inline bool isTurn() const { return _isTurn; }
    inline Card** getAdversePosed() { return _ennemyPosed; }
    inline Card** getPosed() { return _posed; }
    inline int getTrashSize() const { return _trash.size(); }
    inline std::string getEnnemy() const { return _ennemy; }
    inline unsigned getEnergy() const { return _energy; }
    inline unsigned getAdverseEnergy() const { return _adverseEnergy; }
    inline unsigned getHeal() const { return _heal; }
    inline unsigned getAdverseHeal() const { return _adverseHeal; }

    // Init game
    void setDeck(std::string);
    inline void setAdverse(std::string pseudo) { _ennemy = pseudo; }

    // Action during the game
    void setTurn(int, bool);
    inline void drawCard(Card* card) { _hand.push_back(card); }
    void removeCardFromHand(Card*);
    void removeAdverseCardFromHand();
    inline std::string getDeckName() { return _deckName; }
    void placeCard(int, unsigned);
    void ennemyPlaceCard(int, unsigned);
    void placeCardAndAttack(bool, int, unsigned, int, unsigned);
    void placeAdverseCardAndAttack(bool, int, unsigned, int, unsigned);
    void attackCard(unsigned, int, unsigned);
    void adverseAttackCard(unsigned, int, unsigned);


//    Not allready implemented
//    inline void dropCard(int ID) {
//        for(int i = 0; i < _hand.size(); ++i)
//            if(_hand[i] == ID) _hand.erase(_hand.begin()+i);
//    }

//    Not allready implemented
//    inline void ennemyDrop(int ID) {
//        for(int i = 0; i < MAX_POSED_CARD; ++i)
//            if(_ennemyPosed[i] == ID) _ennemyPosed[i] = -1;
//    }
//        inline void drop(int ID) { for(int i = 0; i < MAX_POSED_CARD; ++i) if(_posed[i] == ID) _posed[i] = -1; }

};




#endif // GAMEMANAGER_HPP
