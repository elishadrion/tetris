#ifndef FRIENDSMANAGER_HPP
#define FRIENDSMANAGER_HPP


#include <stdio.h> //
#include <ncurses.h> //
#include <string.h> //
#include <sys/socket.h> //
#include <stdlib.h> //
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h> //
#include <netdb.h>
#include <form.h> //
#include <menu.h>
#include <time.h> //
#include <locale> //
class FriendsManager;

#include "../common/WizardLogger.hpp"
#include "../common/Constants.hpp"
#include "PacketManager.hpp"


class FriendsManager {

  public:

    FriendsManager() = default;
    ~FriendsManager() = default;

    void displayFriendsMenu();

    void displayAllFriends();

    void displayAddFriend();

    void displayDeleteFriend();

    void showOption();

    void printAllUsers(char *allUsers);

    void displayFirendsRequests();

    void addFriend(char *Name);

    void deleteFriend(char *Name);

};

#endif
