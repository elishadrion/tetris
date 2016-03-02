#ifndef FRIENDPANEL_HPP
#define	FRIENDPANEL_HPP

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

/* define size for panel */
#define FRIEND_HEIGHT 30
#define FRIEND_WIDTH 65

extern Display *display;

class FriendPanel : public CLIPanel {
    WINDOW *window;
    PANEL  *panel;
    
    void updateList();
public:
    FriendPanel();
    ~FriendPanel() = default;
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* FRIENDPANEL_HPP */