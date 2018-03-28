#ifndef STATISTICSMANAGER_HPP
#define STATISTICSMANAGER_HPP


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
class StatisticsManager;

#include "../common/WizardLogger.hpp"
#include "../common/Constants.hpp"
#include "PacketManager.hpp"


class StatisticsManager {

  public:

    StatisticsManager() = default;
    ~StatisticsManager() = default;

    void showOption();

    void displayStatisticsMenu();

    void displayMyStatistics();

    void printAllStats(char *allStats);

    void displayAllStatistics();

    void displayAllUsersStatistics();

};

#endif
