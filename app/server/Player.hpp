#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <fstream>

#include "Collection.hpp"
#include "Deck.hpp"
#include "include/json.hpp"

/**
 * One class per player.  This object stocks the socket to communicate with player
 * When the server starts, he must load all Players
 */
class Player {

    int _sockfd;
    std::string _username;
    std::string _pass;
    std::vector<Deck*> _listDeck;

    virtual void save() const;
protected:
    std::vector<Deck*> getListDeck() {return _listDeck;}
    unsigned _victory;
    unsigned _defeat;

public:
    Player() = default; // Must exist for PlayerInGame()
    Player(nlohmann::json&, int);

    friend std::ostream& operator<<(std::ostream&, const Player&);
    virtual ~Player() = default;
};



#endif  /* PLAYER_HPP */
