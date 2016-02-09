
#ifndef CHATMANAGER_HPP
#define	CHATMANAGER_HPP

#include<string>


class ChatManager {

    Player _p1;
    Player _p2;

public:
    // Call when a player send a message
    sendMessage(Player player, std::string message);



};




#endif	/* CHATMANAGER_HPP */

