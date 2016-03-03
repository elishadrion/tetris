#ifndef GAMEPANEL_HPP
#define	GAMEPANEL_HPP

/** in-game layout
#################################### ############
#                                  # #          #
#                                  # #          #
#                                  # #          #
#                                  # #          #
#           gamePanel              # #          #
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

#include "CLIPanel.hpp"

#include "client/Display.hpp"

extern Display *display;

class GamePanel : public CLIPanel {
    WINDOW *window;
    PANEL  *panel;
    
    std::vector<int> ennemyPosedCard;
    std::vector<int> posedCard;
    std::vector<int> ennemyHandCardNumber;
    std::vector<int> handCard;
    int ennemyLife;
    int life;
    int energy;
    
    void update();
public:
    GamePanel();
    ~GamePanel() = default;
    
    void ennemyPoseCard(int);
    void poseCard(int);
    void updateEnnemyLife(int);
    void updateLife(int);
    void updateEnergy(int);
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* GAMEPANEL_HPP */
