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
    PANEL *panel;
    FORM  *form;
    FIELD *field[2];
    int input;
public:
    LoginPanel(WINDOW*);
    ~LoginPanel();
    
    void printError(std::string);
    void setVisibility(bool);
    void askLogin();
};

#endif /* PANEL_HPP */
