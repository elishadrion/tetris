#ifndef WaitPanelCLI_HPP
#define	WaitPanelCLI_HPP

#include <panel.h>

#include "client/PacketManager.hpp"

class CLI;
#include "client/CLI.hpp"

class CLIPanel;
#include "CLIPanel.hpp"

class WaitPanelCLI : public CLIPanel {
    WINDOW *window;
    PANEL  *panel;
    
    bool _inGame;
public:
    WaitPanelCLI(CLI*);
    ~WaitPanelCLI() = default;
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* WaitPanelCLI_HPP */
