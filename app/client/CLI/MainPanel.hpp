#ifndef MAINPANEL_HPP
#define	MAINPANEL_HPP

/** main menu layout
#################################### ############
#                                  # #          #
#                                  # #          #
#                                  # #          #
#                                  # #          #
#                                  # #          #
#                                  # #  tchat   #
#           menu entry             # #          #
#                                  # #          #
#                                  # #          #
#                                  # #          #
#                                  # #          #
#                                  # #          #
#                                  # ############
#                                  # ############
#                                  # #   tchat  #
#                                  # #   input  #
#################################### ############


            commandList (key shortcut)
**/

#include <panel.h>
#include <form.h>

#include <string>
#include <vector>

/* For logging */
#include "common/WizardLogger.hpp"

/* To send disconnection signal */
#include "client/PacketManager.hpp"

#include "CLIPanel.hpp"
#include "client/Display.hpp"

/* define starting line for mainMeny entry */
#define START_LINE 5

extern Display *display;

class MainPanel : public CLIPanel {
    WINDOW *window;
    PANEL  *panel;
    
    void updateColor(int, int);
    void doRequest(int);
public:
    MainPanel();
    ~MainPanel() = default;
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* MAINPANEL_HPP */
