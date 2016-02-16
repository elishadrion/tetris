#ifndef CONSOLE_HPP
#define	CONSOLE_HPP

#include <ncurses.h>
#include <panel.h>

#include "common/WizardLogger.hpp"

/**
#################################### ############
#                                  # #          #
#                                  # # cardInfo #
#                                  # #          #
#                                  # ############
#                                  # ############
#                                  # #          #
#                                  # #          #
#            gamePanel             # #          #
#                                  # #  tchat   #
#                                  # #          #
#                                  # #          #
#                                  # #          #
#################################### ############
#################################### ############
#                                  # #   tchat  #
#        playersInfos              # #   input  #
#################################### ############
#################################################
#          commandeList (key shortcut)          #
#################################################
**/

/* Nbr of space char used to seperate panel */
#define DEFAULT_EMPTY_SPACE 2

/* Define maximum of the mainWindow */
#define LINES 37
#define COLLONNES 40

/* Define commandListPanel size (take all window width) */
#define COMMANDE_PANEL_HEIGTH 1

/* Define gamePanel size */
#define GAME_HEIGTH 21
#define GAME_WIDTH 63

/* Define card's size
 * With 5 card max on bord per player (and ico fro trash and deck)
 * And space for 3 card from top to bottom (2 for player and one for spell action)
 */
#define CARD_HEIGTH (GAME_HEIGTH%3)
#define CARD_WIDTH (GAME_WIDTH%7)

/* Define playersInfoPanel size (same width as gamePanel) */
#define PLAYER_INFO_HEIGTH (3+2*DEFAULT_EMPTY_SPACE)
#define PLAYER_INFO_WIDTH GAME_WIDTH

/* Define tchatInputPanel size (same height as playerInfoPanel) */
#define TCHAT_INPUT_HEIGTH PLAYER_INFO_HEIGTH
#define TCHAT_INPUT_WIDTH 27

/* Define tchatLogPanel size (same width as tchatInputPanel) */
#define TCHAT_HEIGTH 14
#define TCHAT_WIDTH TCHAT_INPUT_WIDTH

/* Define cardInfoPanel size (same width as tchatInputPanel) */
#define CARD_INFO_HEIGTH 5
#define CARD_INFO_WIDTH TCHAT_INPUT_WIDTH

namespace Console {
    void init();
    void close();
}

#endif /* CONSOLE_HPP */
