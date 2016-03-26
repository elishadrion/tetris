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


// Declares before to avoid errors :/
class Game;
class PlayerInGame;
#include "Game.hpp"



class PlayerInGame : public Player {

    std::vector<Card*> _cardsInHand;
    std::vector<Card*> _defausse;
    CardMonster* _cardsPlaced[MAX_POSED_CARD];
    Deck *_deck;
    int _playerHeal;
    int _energy;
    unsigned int _maxEnergy;
    Game* _game;


public:

    PlayerInGame(const PlayerInGame&) = default; // copy constructor
    PlayerInGame& operator=(const PlayerInGame&) = default; // copy operator
    PlayerInGame(const Player &, Game*);

    virtual inline bool isPlayerInGame() {return true;}

    // Getters
    CardMonster** getCardsPlaced();
    std::vector<Card*> getCardsInHand();
    Card* getCardInHand(unsigned);
    unsigned nbrCardInHand();
    std::vector<Card*> getDefausse();
    unsigned nbrCardDefausse();

    // Deck information
    void setDeck(std::string);
    bool isDeckDefined();
    Deck* getDeck();
    unsigned nbrCardDeck();
    Card* draw();
    int getPlacedCardPosition(CardMonster*);
    CardMonster* getCardAtPosition(unsigned);

    // Game info and action
    bool haveEnoughEnergy(Card* card);
    void addMaxEnergy();
    int resetEnergy();
    void removeEnergyFromCard(Card*);
    Error defausseCardPlaced(unsigned);
    Error removeInHandCard(Card*);
    Error defausseCardInHand(Card*);
    int placeCard(CardMonster*);
    void takeDamage(unsigned);
    void addHeal(unsigned);
    int getHeal();
    bool isDead();
    void incrementAllPlaceCard();
    bool haveOneCardTaunt();
    bool havePlace();
    Game* getGame();

    // Request from client
    Error reqAttack(int, int);
    Error reqPlaceCard(int);
    Error reqPlaceAttackCard(int, int);
    Error reqEndTurn();


    // End Game
    void addDefeat();
    void addWin();

    virtual ~PlayerInGame();
};


#endif	/* PLAYERINGAME_HPP */
