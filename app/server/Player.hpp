#ifndef PLAYER_HPP
#define	PLAYER_HPP

#include <string>
#include <vector>

#include "Collection.hpp"
#include "Deck.hpp"


/**
 * One class per player.  This object stock the socket to communicate with player
 * When the server start, he must load all Player
 */
class Player {

    int _sockfd;
    std::string _username;
    std::string _pass;
    int _victory;
    int _defeat;
    std::vector<Deck*> _listDeck;

protected:
    std::vector<Deck*> getListDeck() {return _listDeck;}

public:
    // Create the player (and open the file (if it exist) to complete the informations)
    // Stock the new player in the allPlayer list
    Player(int sockfd, int playerID);
    virtual ~Player() = default;

private:
    virtual void save() const;

};



#endif	/* PLAYER_HPP */
