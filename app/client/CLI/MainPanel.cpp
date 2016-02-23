#include "MainPanel.hpp"

MainPanel::MainPanel() {
    /* We create mainWindow where player can select what to do */
    window = newwin(MAIN_HEIGHT, MAIN_WIDTH, 0, 0);
    box(window, 0, 0);
    
    /* Attach a panel to window */
    panel = new_panel(window);

    /* Update the stacking order */
    update_panels();
    doupdate();
}

MainPanel::~MainPanel() {
}

//TODO
void MainPanel::panelLoop() {}
