/*
 * File:   Player.hpp
 * Author: Detobel36
 *
 * Created on 2 février 2016, 20:41
 */

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

    static std::vector<Player> allPlayer;


    int _sockfd;
    std::string _username;
    std::string _pass;
    int _victory;
    int _defeat;
    Collection _collection;
    std::vector<Deck*> _listDeck;
    bool _online;

protected:
    std::vector<Deck*> getListDeck() {return _listDeck;}


public:
    Player() {} // TO DO
    // Create the player (and open the file (if it exist) to complete the informations)
    // Stock the new player in the allPlayer list
    Player(int sockfd, std::string username);

    virtual bool login(std::string pass) {return true;} // Try to login

    virtual ~Player() = default;


    ///// STATIC /////
    static Player getPlayer(std::string username);
    static Player createPlayer(std::string username, std::string password);


private:
    virtual void save() {} // Save the player in a file TO DO


};



#endif	/* PLAYER_HPP */

