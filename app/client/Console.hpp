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
#        playersInfo              # #    input  #
#################################### ############
#################################################
#           commandList (key shortcut)          #
#################################################
**/

/* Nbr of space char used to seperate panel */
#define DEFAULT_EMPTY_SPACE 2

/* Defines maximum of the mainWindow */
#define LINES 37
#define COLLONNES 96

/* Defines commandListPanel size (take all windows width) */
#define COMMANDE_PANEL_HEIGTH 1

/* Defines gamePanel size */
#define GAME_HEIGTH 21
#define GAME_WIDTH 63

/* Defines card's size
 * With 5 cards max on bord per player (and ico for trash and deck)
 * And space for 3 cards from top to bottom (2 for player and one for spell action)
 */
#define CARD_HEIGTH (GAME_HEIGTH%3)
#define CARD_WIDTH (GAME_WIDTH%7)

/* Defines playersInfoPanel size (same width as gamePanel) */
#define PLAYER_INFO_HEIGTH (3+2*DEFAULT_EMPTY_SPACE)
#define PLAYER_INFO_WIDTH GAME_WIDTH

/* Defines tchatInputPanel size (same height as playerInfoPanel) */
#define TCHAT_INPUT_HEIGTH PLAYER_INFO_HEIGTH
#define TCHAT_INPUT_WIDTH 27

/* Defines tchatLogPanel size (same width as tchatInputPanel) */
#define TCHAT_HEIGTH 14
#define TCHAT_WIDTH TCHAT_INPUT_WIDTH

/* Defines cardInfoPanel size (same width as tchatInputPanel) */
#define CARD_INFO_HEIGTH 5
#define CARD_INFO_WIDTH TCHAT_INPUT_WIDTH

namespace Console {
    void init();
    void close();
}

#endif /* CONSOLE_HPP */
