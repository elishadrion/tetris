#ifndef PLAYERINGAME_HPP
#define	PLAYERINGAME_HPP

#include <vector>

#include "Deck.hpp"
#include "Player.hpp"

#include "common/Card.hpp"
#include "common/CardMonster.hpp"
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
    int const _limitEnergy;
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


    virtual ~PlayerInGame() = default;
};


#endif	/* PLAYERINGAME_HPP */

