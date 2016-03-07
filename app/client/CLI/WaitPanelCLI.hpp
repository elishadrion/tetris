#ifndef WaitPanelCLI_HPP
#define	WaitPanelCLI_HPP

#include <panel.h>

#include "client/WizardDisplay.hpp"

#include "client/PacketManager.hpp"

#include "CLIPanel.hpp"

extern WizardDisplay *wizardDisplaydisplay;

class WaitPanelCLI : public CLIPanel {
    WINDOW *window;
    PANEL  *panel;
    
    bool _inGame;
public:
    WaitPanelCLI();
    ~WaitPanelCLI() = default;
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* WaitPanelCLI_HPP */
