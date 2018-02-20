#ifndef DeckPanelCLI_HPP
#define	DeckPanelCLI_HPP

#include <panel.h>

#include "client/Player.hpp"
#include "common/WizardLogger.hpp"

class CLI;
#include "client/CLI.hpp"

class CLIPanel;
#include "CLIPanel.hpp"

class DeckPanelCLI : public CLIPanel {
    WINDOW *window;
    PANEL  *panel;
public:
    DeckPanelCLI(CLI*);
    ~DeckPanelCLI() = default;
    
    void updatePanel();
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* DeckPanelCLI_HPP */
