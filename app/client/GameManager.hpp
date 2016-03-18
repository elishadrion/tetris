#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <vector>
#include <string>

#include "common/Constants.hpp"
#include "common/WizardLogger.hpp"
#include "PacketManager.hpp"


class GameManager {

    static GameManager* _instance;

    bool _inGame;
    std::vector<int> _hand;
    std::string _deckName; // Selected deck
    std::vector<int> _cardInDeck;
    std::vector<int> _trash;
    std::vector<int> _posed;
    std::vector<int> _ennemyPosed;
    std::string _ennemy;



public:
    static GameManager* getInstance();

    GameManager(std::string pseudo): _ennemy(pseudo) {}

    // Getters
    inline bool isGame() const { return _instance != nullptr; }
    inline int getTrashSize() const { return _trash.size(); }
    inline std::vector<int> getAdversePosed() { return _ennemyPosed; }
    inline std::vector<int> getPosed() { return _posed; }
    inline std::string getEnnemy() const { return _ennemy; }

    // Action during the game
    inline void drawCard(int ID) { _hand.push_back(ID); }
//    inline void ennemyPlaceCard(int ID, int position);
//    inline void placeCard(int ID, int position);
    void setDeck(std::string);
    inline std::string getDeckName() { return _deckName; }




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
