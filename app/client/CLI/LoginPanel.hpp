#ifndef PANEL_HPP
#define	PANEL_HPP

#include <ncurses.h>
#include <panel.h>
#include <form.h>

#include <string>

/* Logger */
#include "common/WizardLogger.hpp"

/* To call the login process */
#include "client/PacketManager.hpp"

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

#define DEFAULT_LABEL "   LOGIN/REGISTRATION     "
#define PSEUDO_ERROR "     PSEUDO INCONUE       "
#define PASSWORD_ERROR "   MAUVAIS MOT DE PASS    "
#define MAX_SIZE_ERROR "TAILLE MAXIMUM DE 30 CHAR "
#define TIMEOUT_ERROR "LE SERVEUR N'A PAS REPONDU"
#define UNKOW_ERROR " MAUVAISE REPONSE SERVEUR "
#define LOGIN_IN_PROGRESS "      LOGIN EN COURS      "
#define REGISTRATION_IN_PROGRESS " ENREGISTREMENT EN COURS  "

class LoginPanel {
    FORM  *form;
    FIELD *field[2];
    bool isWainting;

    void proceed(bool=false);
    void setFocus();
    void printWait(std::string);
public:
    LoginPanel();
    ~LoginPanel();

    void askLogin();
    void printError(std::string);
};

#endif /* PANEL_HPP */
