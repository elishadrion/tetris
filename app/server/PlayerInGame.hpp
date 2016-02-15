#ifndef PLAYERINGAME_HPP
#define	PLAYERINGAME_HPP

#include <vector>

#include "Deck.hpp"
#include "Player.hpp"

#include "common/Card.hpp"
#include "common/Packet.hpp"


struct dataIGPlayer {
    int playerHeal;
    int energy;
    std::vector<Card*> cardsInHand;
    std::vector<Card*> cardsPlaced;
    bool turn;
};

// Declare before to avoid errors :/
class Game;
class PlayerInGame;
#include "Game.hpp"



class PlayerInGame : public Player {

    std::vector<Card*> _cardsInHand;
    std::vector<Card*> _deffause;
    std::vector<Card*> _cardsPlaced;
    Deck *_deck;
    int _playerHeal;
    int _energy;
    Game* game;


public:

    PlayerInGame(); // not valide but better for less of Warning :D
    PlayerInGame(Player player, Game* game);

    dataIGPlayer getDataPlayer();
    std::vector<Card*> getCardPlaced();

    void setDeck(Deck *deck);
    bool isDeckDefine();


    virtual ~PlayerInGame() = default;
};


#endif	/* PLAYERINGAME_HPP */

