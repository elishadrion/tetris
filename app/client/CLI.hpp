#ifndef CLI_HPP
#define	CLI_HPP

#include <ncurses.h>
#include <panel.h>

#include <string>
#include <iostream>

/* Logger */
#include "common/WizardLogger.hpp"

/* Main type */
#include "WizardDisplay.hpp"

/* All used panel */
#include "client/CLI/CLIPanel.hpp"
#include "client/CLI/LoginPanelCLI.hpp"
#include "client/CLI/MainPanelCLI.hpp"
#include "client/CLI/TchatPanelCLI.hpp"
#include "client/CLI/FriendPanelCLI.hpp"
#include "client/CLI/CollectionPanelCLI.hpp"
#include "client/CLI/DeckPanelCLI.hpp"
#include "client/CLI/WaitPanelCLI.hpp"
#include "client/CLI/GamePanelCLI.hpp"

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

#define PANEL_TOTAL_NUMBER 8


class CLI : public WizardDisplay {
    /* All panel used by the CLI */
    CLIPanel *_panelList[PANEL_TOTAL_NUMBER];
    
    enum panelID {
        LOGIN = 0,
        MAIN = 1,
        TCHAT = 2,
        FRIEND = 3,
        COLL = 4,
        DECK = 5,
        WAIT = 6,
        GAME = 7,
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
    void displayDeckWindow();
    void displayWait();
    void displayGame();
    void displayClassement();
    void focusTchat();
    
    

    /* Ask to te play to choose her deck */
    void askDeck() {}

    /**
     * Call when the player recieve one new card
     *
     * @param card wich is draw
     */
    void drawCard(Card*) {}

    /**
     * Call when adverse player draw a card
     */
    void adverseDrawCard() {}

    /**
     * The turn change
     */
    void changeTurn() {}

    /**
     * Call when adverse player place card
     *
     * @param card which is place
     */
    void placeAdverseCard(Card*) {}

    /**
     * Call when a adverse spell card is placed (and attack an other)
     *
     * @param the new card
     * @param the target card
     */
    void placeAdverseSpellCard(Card*, Card*) {}

    /**
     * Call when a adverse spell card is placed (and attack adverse player)
     *
     * @param the new card
     */
    void placeAdverseSpellPlayer(Card*) {}


    /**
     * Call when card is placed (and attack an other)
     *
     * @param the new card
     * @param the target card
     */
    void placeCardAndAttack(Card*, Card*) {}

    /**
     * Call when card is placed (and attack adverse player)
     *
     * @param the new card
     */
    void placeCardAndAttackPlayer(Card*) {}

    /**
     * Call when a adverse spell card is placed (and attack an other)
     *
     * @param the new card
     * @param the target card
     */
    void placeAdverseCardAndAttack(Card*, Card*) {}

    /**
     * Call when a adverse spell card is placed (and attack other player)
     *
     * @param the new card
     */
    void placeAdverseCardAndAttackPlayer(Card*) {}

    /**
     * Call when a card attack an other card
     *
     * @param the card wich attack
     * @param the card wich IS attack
     */
    void attackCard(Card*, Card*) {}

    /**
     * Call when an adverse card attack an other card
     *
     * @param the card wich attack
     * @param the card wich IS attack
     */
    void adverseAttackCard(Card*, Card*) {}

    /**
     * Call when a card attack adverse player
     *
     * @param the card wich attack
     */
    void attackPlayer(Card*) {}

    /**
     * Call when an adverse card attack current player
     *
     * @param the card wich attack
     */
    void adverseAttackPlayer(Card*) {}

    /**
     * Call when a card is dead
     * @param card which is dead
     * @param adverse card or not
     */
    void cardIsDead(Card*, bool) {}


    //////////////////////// TCHAT ////////////////////////

    /**
     * Call when player recev message
     * @param playerFrom who send the message
     * @param playerTo who recev the message
     * @param msg the message
     */
    void recevTchatMsg(std::string, std::string, std::string) {}
};

#endif /* CLI_HPP */
