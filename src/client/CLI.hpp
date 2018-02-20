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
#include "CLI/WaitPanelCLI.hpp"

/* Define some label for HELP */
#define MAIN_LABEL "[F1 : TCHAT    F2 : ENVOYER (TCHAT)    F3 : VALIDER                                                    F10 : QUITTER   ]"
#define AMIS_LABEL "[F1 : TCHAT    F2 : ENVOYER (TCHAT)    F3 : AJOUTER    F4 : RETIRER                                    F10 : RETOUR    ]"
#define COLL_LABEL "[F1 : TCHAT    F2 : ENVOYER (TCHAT)    F3 : DECK                                                       F10 : RETOUR    ]"
#define DECK_LABEL "[F1 : TCHAT    F2 : ENVOYER (TCHAT)    F3 : CREER      F4 : SUPPRIMER                                  F10 : RETOUR    ]"
#define WAIT_LABEL "[F1 : TCHAT    F2 : ENVOYER (TCHAT)                                                                    F10 : ANNULER   ]"
#define GAME_LABEL "[F1 : TCHAT    F2 : ENVOYER (TCHAT)    F3 : PIOCHER    F4 : JOUER    F5 : JETER    F6 : FIN DE TOUR    F10 : ABANDONNER]"

/* Defines maximum of the CLI */
#define LINES 37
#define COLLONNES 96

/* Nbr of space char used to seperate panel */
#define DEFAULT_EMPTY_SPACE 2

/* Defines card's size
 * With 5 cards max on bord per player (and ico for trash and deck)
 * And space for 3 cards from top to bottom (2 for player and one for spell action)
 */
#define CARD_HEIGTH (GAME_HEIGTH%3)
#define CARD_WIDTH (GAME_WIDTH%7)

/* Defines playersInfoPanel size (same width as gamePanel) */
#define PLAYER_INFO_HEIGTH (3+2*DEFAULT_EMPTY_SPACE)
#define PLAYER_INFO_WIDTH GAME_WIDTH

/* Defines cardInfoPanel size (same width as tchatInputPanel) */
#define CARD_INFO_HEIGTH 5
#define CARD_INFO_WIDTH TCHAT_INPUT_WIDTH

#define PANEL_TOTAL_NUMBER 5


class CLI : public WizardDisplay {
    /* All panel used by the CLI */
    CLIPanel *_panelList[PANEL_TOTAL_NUMBER];
    
    enum panelID {
        LOGIN = 0,
        MAIN = 1,
        TCHAT = 2,
        FRIEND = 3,
        WAIT = 6,
    };
public:
    CLI();
    ~CLI();
    
    void displayFatalError(std::string) override;
    void displayLoginPrompt() override;
    void diaplayError(std::string) override;
    
    void displayMainWindow();
    void displayFriendsWindow();
    void displayCollectionWindow();

    void displayWait();

    void displayClassement();
    void focusTchat();
    void askDeck();

    void recevTchatMsg(std::string, std::string, std::string);

};

#endif /* CLI_HPP */