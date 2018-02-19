#ifndef CLI_HPP
#define	CLI_HPP

#include <ncurses.h>
#include <panel.h>

#include <string>
#include <iostream>

/* Logger */
#include "../common/WizardLogger.hpp"

/* Main type */
#include "WizardDisplay.hpp"

/* All used panel */
#include "CLI/CLIPanel.hpp"
#include "CLI/LoginPanelCLI.hpp"
#include "CLI/MainPanelCLI.hpp"
#include "CLI/TchatPanelCLI.hpp"
#include "CLI/FriendPanelCLI.hpp"
#include "CLI/CollectionPanelCLI.hpp"
#include "CLI/DeckPanelCLI.hpp"
#include "CLI/WaitPanelCLI.hpp"
#include "CLI/GamePanelCLI.hpp"

/* Define some label for HELP */
#define MAIN_LABEL "[F1 : TCHAT    F2 : ENVOYER (TCHAT)    F3 : VALIDER                                                    F10 : QUITTER   ]"
#define AMIS_LABEL "[F1 : TCHAT    F2 : ENVOYER (TCHAT)    F3 : AJOUTER    F4 : RETIRER                                    F10 : RETOUR    ]"
#define WAIT_LABEL "[F1 : TCHAT    F2 : ENVOYER (TCHAT)                                                                    F10 : ANNULER   ]"
#define GAME_LABEL "[F1 : TCHAT    F2 : ENVOYER (TCHAT)    F3 : PIOCHER    F4 : JOUER    F5 : JETER    F6 : FIN DE TOUR    F10 : ABANDONNER]"

/* Defines maximum of the CLI */
#define LINES 37
#define COLLONNES 96

/* Nbr of space char used to seperate panel */
#define DEFAULT_EMPTY_SPACE 2

/* Defines playersInfoPanel size (same width as gamePanel) */
#define PLAYER_INFO_HEIGTH (3+2*DEFAULT_EMPTY_SPACE)
#define PLAYER_INFO_WIDTH GAME_WIDTH

#define PANEL_TOTAL_NUMBER 5


class CLI : public WizardDisplay {
    /* All panel used by the CLI */
    CLIPanel *_panelList[PANEL_TOTAL_NUMBER];
    
    enum panelID {
        LOGIN = 0,
        MAIN = 1,
        TCHAT = 2,
        WAIT = 3,
        GAME = 4,
    };
public:
    CLI();
    ~CLI();
    
    void displayFatalError(std::string) override;
    void displayLoginPrompt() override;
    void diaplayError(std::string) override;
    
    void displayMainWindow();
    void displayFriendsWindow();
    void focusTchat();

    void receive_message(std::string, std::string, std::string);
    
};

#endif /* CLI_HPP */
