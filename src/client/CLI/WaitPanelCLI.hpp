#ifndef WaitPanelCLI_HPP
#define	WaitPanelCLI_HPP

#include <panel.h>

#include <vector>

#include "client/PacketManager.hpp"

#include "client/Player.hpp"

class CLI;
#include "client/CLI.hpp"

class CLIPanel;
#include "CLIPanel.hpp"

class WaitPanelCLI : public CLIPanel {
    WINDOW *windows[2];
    PANEL  *panel;
    FIELD *field[2];
    FORM *form;
    
    bool _inGame;
    
    bool checkDeck(char*);
    void askDeck();
public:
    WaitPanelCLI(CLI*);
    ~WaitPanelCLI() = default;
    
    void startGame();
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* WaitPanelCLI_HPP */
