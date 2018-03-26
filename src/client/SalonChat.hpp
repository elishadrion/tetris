#ifndef SALONCHAT_HPP
#define SALONCHAT_HPP

class SalonChat;

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


//INCLUDE D ABDERR
#include "../common/WizardLogger.hpp"
#include "../common/Constants.hpp"
#include "PacketManager.hpp"


class SalonChat {

    WINDOW *msg_win_chat,*user_win,*input_win;

public:



    SalonChat() = default;
    ~SalonChat() = default;

    char username[MAX_PSEUDO_SIZE];

    char* trim_whitespaces(char *str);

    void chatReceiver(char* , char* );

    void print_online_users_chat(char* users);

    void startChat();

};

#endif  /* SALONCHAT_HPP */
