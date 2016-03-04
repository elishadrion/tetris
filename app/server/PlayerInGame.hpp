#ifndef PLAYERINGAME_HPP
#define	PLAYERINGAME_HPP

#include <vector>
#include <algorithm>


#include "Deck.hpp"
class Player;
#include "Player.hpp"

class Card;
class CardMonster;

#include "common/Packet.hpp"
#include "CardManager.hpp"
#include "common/Constants.hpp"


/*
Je pense que l'on en a plus besoin
à voir avec @remy et @tutul
*/
struct dataIGPlayer {
    int playerHeal;
    int energy;
    int maxEnergy;
    int limitEnergy; // const here make error :/
    std::vector<Card*> cardsInHand;
    std::vector<CardMonster*> cardsPlaced;
    bool turn;
};

// Declares before to avoid errors :/
class Game;
class PlayerInGame;
#include "Game.hpp"



class PlayerInGame : public Player {

    std::vector<Card*> _cardsInHand;
    std::vector<Card*> _defausse;
    std::vector<CardMonster*> _cardsPlaced;
    Deck *_deck;
    int _playerHeal;
    int _energy;
    unsigned int _maxEnergy;
    unsigned int const _limitEnergy = MAX_ENERGY; //The maximum energy can't go further than this
    Game* _game;


public:

    //PlayerInGame(); // not valide but better for less Warnings :D
    PlayerInGame(const PlayerInGame&) = default; // copy constructor
    PlayerInGame& operator=(const PlayerInGame&) = default; // copy operator
    PlayerInGame(const Player &, Game*);

    dataIGPlayer getDataPlayer();
    std::vector<CardMonster*> getCardsPlaced();
    std::vector<Card*> getCardsInHand();
    unsigned int nbrCardInHand();

    void setDeck(Deck *deck);
    bool isDeckDefined();
    Card* draw();

    bool haveEnoughEnergy(Card* card);
    void addMaxEnergy();
    int resetEnergy();
    void defausseCardPlaced(CardMonster*);
    void placeCard(CardMonster*);
    void takeDamage(unsigned int);
    void getHealed(unsigned int);

    int getHeal();
    void addDefeat();
    void addWin();
    bool isDead();

    virtual ~PlayerInGame() = default;
};


#endif	/* PLAYERINGAME_HPP */
