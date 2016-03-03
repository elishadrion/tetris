#ifndef WAITPANEL_HPP
#define	WAITPANEL_HPP

#include <panel.h>

#include "common/WizardLogger.hpp"

#include "CLIPanel.hpp"

class WaitPanel : public CLIPanel {
    WINDOW *windows;
    PANEL  *panel;
public:
    WaitPanel();
    ~WaitPanel() = default;
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* WAITPANEL_HPP */
