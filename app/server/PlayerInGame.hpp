/*
 * File:   PlayerInGame.hpp
 * Author: Detobel36
 *
 * Created on 3 février 2016, 8:51
 */

#ifndef PLAYERINGAME_HPP
#define	PLAYERINGAME_HPP

#include <vector>

#include "Deck.hpp"
#include "Player.hpp"

#include "common/Card.hpp"
#include "common/Package.hpp"


class PlayerInGame : public Player {

    std::vector<Card*> _cardsInHand;
    std::vector<Card*> _deffause;
    std::vector<Card*> _cardsPlaced;
    Deck _deck;
    int _playerHeal;
    int _energy;


public:

    PlayerInGame();
    PlayerInGame(Player player);

    std::vector<Card*> getCardPlaced();
    void sendData(unsigned int currentPlayer, unsigned int turn,
        std::vector<Card*> adversePlacedCards);

    virtual ~PlayerInGame() = default;
};


#endif	/* PLAYERINGAME_HPP */

