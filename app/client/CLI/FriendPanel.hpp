#ifndef FRIENDPANEL_HPP
#define	FRIENDPANEL_HPP

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
#include "client/Display.hpp"

extern Display *display;

class FriendPanel : public CLIPanel {
    WINDOW *windows[2];
    PANEL  *panel;
    FIELD *field[2];
    FORM *form;
    
    void updateList();
    void manageFriend(bool remove = false);
public:
    FriendPanel();
    ~FriendPanel() = default;
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* FRIENDPANEL_HPP */
