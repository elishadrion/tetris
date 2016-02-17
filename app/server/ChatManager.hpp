
#ifndef CHATMANAGER_HPP
#define	CHATMANAGER_HPP

#include<string>


class ChatManager {

    Player _p1;
    Player _p2;

public:
    // Called when a player sends a message
    sendMessage(Player player, std::string message);



};


#endif	/* CHATMANAGER_HPP */

