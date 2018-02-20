#ifndef MainPanelCLI_HPP
#define	MainPanelCLI_HPP

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

/* To send disconnection signal */
#include "../PacketManager.hpp"

#include "../WizardDisplay.hpp"

class CLI;
#include "../CLI.hpp"

class CLIPanel;
#include "CLIPanel.hpp"

/* define starting line for mainMeny entry */
#define START_LINE 5

extern WizardDisplay *wizardDisplay;

class MainPanelCLI : public CLIPanel {
    WINDOW *window;
    PANEL  *panel;

    void updateColor(int, int);
    void doRequest(int);
public:
    MainPanelCLI(CLI*);
    ~MainPanelCLI() = default;

    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* MainPanelCLI_HPP */