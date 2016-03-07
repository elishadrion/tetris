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

/* For logging */
#include "common/WizardLogger.hpp"

/* To send disconnection signal */
#include "client/PacketManager.hpp"

/* To get friends info */
#include "client/Player.hpp"

#include "CLIPanel.hpp"
#include "client/WizardDisplay.hpp"

extern WizardDisplay *wizardDisplay;

class FriendPanelCLI : public CLIPanel {
    WINDOW *windows[2];
    PANEL  *panel;
    FIELD *field[2];
    FORM *form;

    void updateList();
    void manageFriend(bool remove = false);
public:
    FriendPanelCLI();
    ~FriendPanelCLI() = default;

    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* FriendPanelCLI_HPP */
