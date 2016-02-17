#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

#include "Collection.hpp"
#include "Deck.hpp"


/**
 * One class per player.  This object stocks the socket to communicate with player
 * When the server starts, he must load all Players
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
    Player() {}
    // Creates the player (and opens the file (if it exists) to complete the information)
    // Stocks the new player in the allPlayers list
    Player(int sockfd, int playerID) {}
    virtual ~Player() = default;

private:
    virtual void save() const;

};



#endif  /* PLAYER_HPP */
