#ifndef GamePanelCLI_HPP
#define	GamePanelCLI_HPP

/** in-game layout
#################################### ############
#                                  # #          #
#                                  # #          #
#                                  # #          #
#                                  # #          #
#           GamePanelCLI           # #          #
#               +                  # #  tchat   #
#        cardInfo popup            # #          #
#                                  # #          #
#                                  # #          #
#                                  # #          #
#                                  # #          #
#                                  # #          #
#################################### ############
#################################### ############
#                                  # #   tchat  #
#        playersInfo               # #   input  #
#################################### ############


            commandList (key shortcut)
**/

#include <panel.h>
#include <form.h>

#include <string>
#include <vector>

#include "common/WizardLogger.hpp"

#include "client/PacketManager.hpp"

#include "client/GameManager.hpp"

class CLI;
#include "client/CLI.hpp"

class CLIPanel;
#include "CLIPanel.hpp"

class GamePanelCLI : public CLIPanel {
    WINDOW *window;
    PANEL  *panel;
    
    int _ennemyHandSize;
    
    void update();
public:
    GamePanelCLI(CLI*);
    ~GamePanelCLI() = default;
    
    void show() override;
    void hide() override;
    void focus() override;
    
    void drawCard(Card*);
    void adverseDrawCard();
    void changeTurn();
    void placeAdverseCard(Card*);
    void placeAdverseSpellCard(Card*, Card*);
    void placeAdverseSpellPlayer(Card*);
    void placeCardAndAttack(Card*, Card*);
    void placeCardAndAttackPlayer(Card*);
    void placeAdverseCardAndAttack(Card*, Card*);
    void placeAdverseCardAndAttackPlayer(Card*);
    void attackCard(Card*, Card*);
    void adverseAttackCard(Card*, Card*);
    void attackPlayer(Card*);
    void adverseAttackPlayer(Card*);
    void cardIsDead(Card*, bool);
};

#endif	/* GamePanelCLI_HPP */
