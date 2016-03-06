#ifndef WAITPANEL_HPP
#define	WAITPANEL_HPP

#include <panel.h>

#include "client/WizardDisplay.hpp"

#include "client/PacketManager.hpp"

#include "CLIPanel.hpp"

extern WizardDisplay *wizardDisplaydisplay;

class WaitPanel : public CLIPanel {
    WINDOW *window;
    PANEL  *panel;
    
    bool _inGame;
public:
    WaitPanel();
    ~WaitPanel() = default;
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* WAITPANEL_HPP */
