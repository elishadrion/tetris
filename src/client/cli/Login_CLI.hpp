#ifndef LOGIN_CLI_HPP

#define LOGIN_CLI_HPP

class Login_CLI;
#include <string>
#include <iostream>
#include <ncurses.h>
#include <form.h>
#include "../WizardInfo.hpp"

#include "../PacketManager.hpp"
extern WizardInfo *info;

class Login_CLI {

    private:

       
        FIELD *field[2];
         FORM  *my_form;
        
        std::string pseudo;
        std::string password;

    public:    


       
        
        /* Create or remove interface (CLI/GUI) */
        Login_CLI();
        ~Login_CLI();


        void play();
        void window();
        void try_login();
        bool connect();
        std::string empty_space_string(const char*str, int len );

};

#endif  /* WIZARDDISPLAY_HPP */
