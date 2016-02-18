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
    std::vector<Card*> _deffause;
    std::vector<CardMonster*> _cardsPlaced;
    Deck *_deck;
    int _playerHeal;
    int _energy;
    Game* game;


public:

    PlayerInGame(); // not valide but better for less Warnings :D
    PlayerInGame(Player player, Game* game);

    dataIGPlayer getDataPlayer();
    std::vector<CardMonster*> getCardPlaced();
    // std::vector<Card*> getCardInHand() {} not used now
    unsigned nbrCardInHand() {return _cardsInHand.size();}

    void setDeck(Deck *deck);
    bool isDeckDefine();


    virtual ~PlayerInGame() = default;
};


#endif	/* PLAYERINGAME_HPP */

