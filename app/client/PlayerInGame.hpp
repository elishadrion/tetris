/* 
 * File:   PlayerInGame.hpp
 * Author: Detobel36
 *
 * Created on 3 février 2016, 8:51
 */

#ifndef PLAYERINGAME_HPP
#define	PLAYERINGAME_HPP

#include <vector>



class PlayerInGame : public Player {
    
    std::vector<Card> _cardsInHand;
    std::vector<Card> _deffause;
    std::vector<Card> _cardsPlaced;
    Deck _deck;
    int _playerHeal;
    int _energy;
    
    
public:
    virtual void sendData(Package package);
    
    
};


#endif	/* PLAYERINGAME_HPP */

