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
    
    void ennemyPoseCard(int);
    void poseCard(int);
    void updateEnnemyLife(int);
    void updateLife(int);
    void updateEnergy(int);
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* GamePanelCLI_HPP */
