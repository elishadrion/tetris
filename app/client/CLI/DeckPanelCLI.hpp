#ifndef DECKPANEL_HPP
#define	DECKPANEL_HPP

#include <panel.h>

#include "common/WizardLogger.hpp"

#include "CLIPanel.hpp"

class DeckPanel : public CLIPanel {
    WINDOW *window;
    PANEL  *panel;
public:
    DeckPanel();
    ~DeckPanel() = default;
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* DECKPANEL_HPP */
