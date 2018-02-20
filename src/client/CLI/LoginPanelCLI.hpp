#ifndef PANEL_HPP
#define	PANEL_HPP

/** login layout
#####################################
#                                   #
#            ERROR MSG              #
#    Pseudo:__________________      #
#    Pasww :__________________      #
#                                   #
#   F1:ann   F2:login   F3:reg      #
#####################################
**/

#include <ncurses.h>
#include <panel.h>
#include <form.h>

#include <string>

/* Logger */
#include "../../common/WizardLogger.hpp"

/* To call the login process */
#include "../PacketManager.hpp"

#include "../WizardDisplay.hpp"

class CLI;
#include "../CLI.hpp"

class CLIPanel;
#include "CLIPanel.hpp"

#define LABEL_LENGHT 26
#define DEFAULT_LABEL "   LOGIN/REGISTRATION     "
#define PSEUDO_ERROR "     PSEUDO INCONUE       "
#define PASSWORD_ERROR "   MAUVAIS MOT DE PASS    "
#define MAX_SIZE_ERROR "TAILLE MAXIMUM DE 30 CHAR "
#define LOGIN_IN_PROGRESS "      LOGIN EN COURS      "
#define REGISTRATION_IN_PROGRESS " ENREGISTREMENT EN COURS  "
#define CARDS_LOADING "  CHARGEMENT DES CARTES   "

extern WizardDisplay *wizardDisplay;

class LoginPanelCLI : public CLIPanel {
    WINDOW *window;
    FORM  *form;
    FIELD *field[4];

    /* Control bool */
    bool success;

    /* cols of form (for printInMiddle) */
    int colsForm;

    /* Define work variable using for verification and beep */
    int indexPseudo = 0;
    int sizePseudo = 0;
    int indexPassword = 0;
    int sizePassword = 0;

    void proceed(bool=false);
    void printWait(char*);

    void setFocusToField();
    void printInMiddle(char*, chtype);
public:
    LoginPanelCLI(CLI*);
    ~LoginPanelCLI() = default;

    void printError(std::string);

    void hide() override;
    void focus() override;

    /* Not used */
    void show() override {}
};

#endif /* PANEL_HPP */
