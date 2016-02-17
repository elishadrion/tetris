#ifndef PANEL_HPP
#define	PANEL_HPP

#include <ncurses.h>
#include <panel.h>
#include <form.h>

#include <string>

/* Logger */
#include "common/WizardLogger.hpp"

/**
#####################################
#                                   #
#            ERROR MSG              #
#    Pseudo:__________________      #
#    Pasww :__________________      #
#                                   #
#   F1:ann   F2:login   F3:reg      #
#####################################
**/

class LoginPanel {
    FORM  *form;
    FIELD *field[2];
    int input;
    
    void setFocus();
public:
    LoginPanel();
    ~LoginPanel();
    
    void askLogin();
    void printError(std::string);
};

#endif /* PANEL_HPP */
