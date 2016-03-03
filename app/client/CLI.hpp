#ifndef CLI_HPP
#define	CLI_HPP

#include <ncurses.h>
#include <panel.h>

#include <string>
#include <iostream>

/* Logger */
#include "common/WizardLogger.hpp"

/* Main type */
#include "Display.hpp"

/* All used panel */
#include "client/CLI/CLIPanel.hpp"
#include "client/CLI/LoginPanel.hpp"
#include "client/CLI/MainPanel.hpp"
#include "client/CLI/TchatPanel.hpp"
#include "client/CLI/FriendPanel.hpp"
#include "client/CLI/CollectionPanel.hpp"
#include "client/CLI/DeckPanel.hpp"
#include "client/CLI/WaitPanel.hpp"
#include "client/CLI/GamePanel.hpp"

/* Define some label for HELP */
#define MAIN_LABEL "F1 : TCHAT    F2 : ENVOYER (TCHAT)    F3 : VALIDER    F10 : QUITTER                                                   "
#define AMIS_LABEL "F1 : TCHAT    F2 : ENVOYER (TCHAT)    F3 : AJOUTER    F4 : RETIRER    F10 : RETOUR                                    "
#define COLL_LABEL "F1 : TCHAT    F2 : ENVOYER (TCHAT)    F3 : AFFICHER DECK    F10 : RETOUR                                              "
#define DECK_LABEL "F1 : TCHAT    F2 : ENVOYER (TCHAT)    F3 : CREER    F4 : SUPPRIMER    F10 : RETOUR                                    "
#define WAIT_LABEL "F1 : TCHAT    F2 : ENVOYER (TCHAT)    F10 : ANNULER                                                                   "
#define GAME_LABEL "F1 : TCHAT    F2 : ENVOYER (TCHAT)    F3 : PIOCHER    F4 : JOUER    F5 : JETER    F6 : FIN DE TOUR    F10 : ABANDONNER"

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

#define PANEL_TOTAL_NUMBER 8

class CLI : public Display {
    /* All panel used by the CLI */
    CLIPanel *_panelList[PANEL_TOTAL_NUMBER];
    
    enum panelID {
        LOGIN = 0,
        MAIN = 1,
        TCHAT = 2,
        FRIEND = 3,
        COLL = 4,
        DECK = 5,
        CARD = 6,
        WAIT = 7,
        GAME = 8,
    };
public:
    CLI();
    ~CLI();
    void displayFatalError(std::string);
    void displayLoginPrompt();
    void displayLoginResult(std::string);
    void valideLogin();
    void displayMainWindow();
    void displayFriendsWindow();
    void displayCollectionWindow();
    void displayDeckWindow(); //TODO get ID ?
    void displayWait();
    void displayGame();
    void focusTchat();
};

#endif /* CLI_HPP */
