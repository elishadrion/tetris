/* 
 * File:   ChatManager.hpp
 * Author: Detobel36
 *
 * Created on 3 février 2016, 10:57
 */

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

