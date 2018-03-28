#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include "./database/sqlite3.h"
#include <cstring>
#include <stdio.h>
#include <vector>

typedef struct {
    int size = 0;
    std::vector<std::string> friendList = std::vector<std::string>();
} friendListPacket;


class Database {

    protected:
      sqlite3 *db;

    public:

        Database();
        void initialiseDatabase();
        void prettyPrint();

        //GETTERS
        bool checkNamePassword(std::string name, std::string password);
        bool checkNameExist(std::string name);

        char * getUserNameFriends(std::string name);
        char * getUserNameFriendsRequests(std::string name);

        std::string getLevelFromName(std::string name);
        char * getAllUser();
        char * getGlobalStatistics();
        char * getUserNameStatistics(std::string name);
        char * getAllUsersStatistics();


        //SETTERS
        void registerUser(std::string name, std::string password);
        void updateUserNameScore(std::string name, int victoryAdd, int lostAdd);
        void sendFriendRequest(std::string name, std::string FriendName);
        void confirmFriendRequest(std::string name, std::string FriendName);
        void deleteFriendFromUserName(std::string name, std::string FriendName);
        void updateGlobalStatistic(int gameMode, int victoryAdd, int lostAdd, int score, int time, int completeLine);

};

#endif
