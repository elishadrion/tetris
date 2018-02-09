#ifndef USER_HPP
#define USER_HPP

#include <string.h>

#define MAX_SIZE 140

class User {

    private:
        std::string username;
        std::string message;

    public:
        //SETTERS
        void set_message(std::string);
        void set_username(std::string);
        //GETTERS
        std::string get_username();
        std::string get_message();

};

#endif
