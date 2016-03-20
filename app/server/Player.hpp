#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sys/socket.h>

#include "include/json.hpp"

#include "unistd.h"
#include "common/Error.hpp"
#include "Collection.hpp"
#include "Deck.hpp"
#include "common/Packet.hpp"
#include "PacketManager.hpp"
#include "FriendsManager.hpp"

class Player;
class PlayerInGame;
class PlayerConnect;
class PlayerManager;
#include "PlayerConnect.hpp"
#include "PlayerManager.hpp"

#include "common/WizardLogger.hpp"
#include "common/Constants.hpp"


/**
 * One class per player.  This object stocks the socket to communicate with player
 * When the server starts, he must load all Players
 */
class Player {

    std::string _username;
    std::string _password;
    Collection _collection;

    unsigned getRatio() const;


protected:
    PlayerConnect *_playerConnect;
    std::vector<Deck*> _decks;
    std::vector<Player*> _friends;
    unsigned _victories;
    unsigned _defeats;

public:
    Player(nlohmann::json&, int sockfd = 0);

    virtual inline bool isPlayerInGame() {return false;}

    inline void adjudicateVictory() {_victories++;}
    inline void adjudicateDefeat() {_defeats++;}
    inline Error addCardCollection(Card* c) {return _collection.addCard(c);}
    inline Collection *getCollection() {return &_collection;} //TODO needed for send collection to user
    void updateSockfd(int sock);
    inline std::string getName() const {return _username;}
    inline std::string getPass() const {return _password;}
    inline unsigned getVictories() const {return _victories;}
    inline unsigned getDefeats() const {return _defeats;}

    std::vector<Deck*> getListDeck() {return _decks;}
    Deck* getDeck(std::string);
    Error removeDeck(Deck*);
    Error addDeck(Deck *);

    void sendPacket(Packet::packet*, size_t);
    void recvLoop();
    void logout();
    void setPlayerInGame(PlayerInGame*);

    nlohmann::json serialise() const;
    friend std::ostream& operator<<(std::ostream&, const Player&); // remove ?
    friend std::string& operator<<(std::string&, const Player&); // remove ?
    bool operator==(const std::string&) const;
    bool operator<(const Player&) const;
    bool operator>(const Player&) const;

    void removePlayerInGame(PlayerInGame*);
    void overwrite(const Player&);


    virtual ~Player() { delete _playerConnect; }
};

#endif  /* PLAYER_HPP */
