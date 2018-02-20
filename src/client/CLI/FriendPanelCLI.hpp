#ifndef FriendPanelCLI_HPP
#define	FriendPanelCLI_HPP

/** friend layout
#################################### ############
#                                  # #          #
#                                  # #          #
#                                  # #          #
#                                  # #          #
#           tchatHelp              # #          #
#               +                  # #  tchat   #
#           friendList             # #          #
#               +                  # #          #
#        add/remove popup          # #          #
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

#include "../../common/Constants.hpp"

/* For logging */
#include "../../common/WizardLogger.hpp"

/* To send disconnection signal */
#include "../PacketManager.hpp"

/* To get friends info */
#include "../Player.hpp"

class CLI;
#include "../CLI.hpp"

class CLIPanel;
#include "CLIPanel.hpp"

extern WizardDisplay *wizardDisplay;
extern Player *player;

class FriendPanelCLI : public CLIPanel {
    WINDOW *windows[2];
    PANEL  *panel;
    FIELD *field[2];
    FORM *form;

    void updateList();
    void manageFriend(bool remove = false);
public:
    FriendPanelCLI(CLI*);
    ~FriendPanelCLI() = default;

    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* FriendPanelCLI_HPP */
