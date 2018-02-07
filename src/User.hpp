#ifndef USER_HPP
#define USER_HPP

#include <string.h>

#define MAX_SIZE 140

class User {

    private:
        string username;
        char* message[MAX_SIZE];
        bool is_online;

    public:
        string get_username();
        void set_message(char * buffer);
        char* get_message();

}

#endif