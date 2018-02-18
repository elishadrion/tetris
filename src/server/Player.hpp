#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sys/socket.h>
#include "../dependencies/json.hpp"
#include "unistd.h"
#include "../common/Packet.hpp"
//#include "PacketManager.hpp"
#include "../common/Constants.hpp"
class Player;
class PlayerConnect;
#include "PlayerConnect.hpp"


class Player {

    std::string _username;


protected:
    PlayerConnect *_playerConnect;
    unsigned _victories;
    unsigned _defeats;

public:
    //Player(nlohmann::json&, int sockfd = 0);
    Player(std::string, int);
    inline void increment_victories() {_victories++;}
    inline void increment_defeats() {_defeats++;}
    void set_sockfd(int);
    inline std::string get_name() const {return _username;}
    inline unsigned get_victories() const {return _victories;}
    inline unsigned get_defeats() const {return _defeats;}
    unsigned get_ratio() const;

    void send_packet(Packet::packet*, size_t);
    void receive();
    void logout();

    bool operator==(const std::string&) const;
    bool operator<(const Player&) const;
    bool operator>(const Player&) const;

    virtual ~Player() { delete _playerConnect; }
};

#endif
