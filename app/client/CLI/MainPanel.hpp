#ifndef MAINPANEL_HPP
#define	MAINPANEL_HPP

#include <panel.h>
#include <form.h>

#include <string>
#include <vector>

#include "common/WizardLogger.hpp"

#include "CLIPanel.hpp"

/* define size for panel */
#define MAIN_HEIGHT 30
#define MAIN_WIDTH 65

/* define starting line for mainMeny entry */
#define START_LINE 5

class MainPanel : public CLIPanel {
    WINDOW *window;
    PANEL  *panel;
    
    void updateColor(int, int);
public:
    MainPanel();
    ~MainPanel();
    
    void show();
    void hide();
    void focus();
};

#endif	/* MAINPANEL_HPP */
