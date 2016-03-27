#ifndef DeckPanelCLI_HPP
#define	DeckPanelCLI_HPP

#include <panel.h>

#include "client/Player.hpp"
#include "common/WizardLogger.hpp"

#include "CLIPanel.hpp"

class DeckPanelCLI : public CLIPanel {
    WINDOW *window;
    PANEL  *panel;
public:
    DeckPanelCLI();
    ~DeckPanelCLI() = default;
    
    void updatePanel();
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* DeckPanelCLI_HPP */
