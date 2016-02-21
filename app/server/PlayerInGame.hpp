#ifndef PLAYERINGAME_HPP
#define	PLAYERINGAME_HPP

#include <vector>
#include <algorithm>


#include "Deck.hpp"
#include "Player.hpp"

#include "Card.hpp"
#include "CardMonster.hpp"
#include "common/Packet.hpp"


struct dataIGPlayer {
    int playerHeal;
    int energy;
    int maxEnergy;
    int limitEnergy;
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
    int _maxEnergy;
    int const _limitEnergy = 10; //The maximum energy can't go further than this
    Game* game;


public:

    PlayerInGame(); // not valide but better for less Warnings :D
    PlayerInGame(Player player, Game* game);

    dataIGPlayer getDataPlayer();
    std::vector<CardMonster*> getCardsPlaced();
    // std::vector<Card*> getCardInHand() {} not used now
    //unsigned nbrCardInHand() {return _cardsInHand.size();}
    unsigned nbrCardInHand();

    void setDeck(Deck *deck);
    bool isDeckDefined();
    void draw();

    bool haveEnoughEnergy(Card* card);
    void addMaxEnergy();
    void resetEnergy();
    void defausseCardPlaced(CardMonster*);
    void placeCard(CardMonster*);

    virtual ~PlayerInGame() = default;
};


#endif	/* PLAYERINGAME_HPP */

