#ifndef MAINPANEL_HPP
#define	MAINPANEL_HPP

#include <panel.h>
#include <form.h>

#include <string>
#include <vector>

#include "common/WizardLogger.hpp"

/* define size for panel */
#define MAIN_HEIGHT 30
#define MAIN_WIDTH 65

class MainPanel : PANEL {
    WINDOW *window;
    PANEL  *panel;
public:
    MainPanel();
    ~MainPanel();
    
    void panelLoop();
};

#endif	/* MAINPANEL_HPP */
