#include "MainPanel.hpp"

MainPanel::MainPanel() {
    /* We create mainWindow where player can select what to do */
    window = newwin(MAIN_HEIGTH, MAIN_WIDTH, 0, 0);
    box(window, 0, 0);
    keypad(window, TRUE);

    /* Attach a panel to window */
    panel = new_panel(window);

    /* Update the stacking order */
    update_panels();
    doupdate();

    /* Display menu entry */
    mvwprintw(window, START_LINE, 8, "* Commencer une partie");
    mvwprintw(window, START_LINE+2, 8, "* Afficher la collection");
    mvwprintw(window, START_LINE+4, 8, "* Liste d'amis");
    refresh();
}

void MainPanel::show() {
    show_panel(panel);
    update_panels();
    doupdate();
}

void MainPanel::hide() {
    hide_panel(panel);
    update_panels();
    doupdate();
}

void MainPanel::focus() {
    /* Set focus to mainPanel */
    top_panel(panel);
    update_panels();
    doupdate();

    /* Set focus on first element */
    int currentMenu = START_LINE;
    updateColor(0, currentMenu);

    /* Loop through to get user requests with F1 to valide */
    int input;
    while((input = wgetch(window)) != KEY_F(10)) {
        switch(input) {
            case KEY_DOWN:
                /* Go to next menu (or first) */
                if (currentMenu < START_LINE+4) {
                    updateColor(currentMenu, currentMenu+2);
                    currentMenu += 2;
                } else {
                    updateColor(currentMenu, START_LINE);
                    currentMenu = START_LINE;
                }
                break;
            case KEY_UP:
                /* Go to previous menu (or last) */
                if (currentMenu > START_LINE) {
                    updateColor(currentMenu, currentMenu-2);
                    currentMenu -= 2;
                } else {
                    updateColor(currentMenu, START_LINE+4);
                    currentMenu = START_LINE+4;
                }
                break;
            case KEY_F(1):
                display->focusTchat();
                break;
            case KEY_F(3):
                doRequest(currentMenu);
                break;
            default:
                beep();
                break;
        }
        
        /* Make sure current line is correctly colored */
        updateColor(0, currentMenu);
    }
    
    /* Send deconnection packet before close program */
    PacketManager::sendDisconnection();
}

//================================PRIVATE=======================================

void MainPanel::updateColor(int previous, int next) {
    /* Remove color from previous menu entry (0: no previous entry) */
    if (previous != 0) {
        mvwprintw(window, previous, 8, "*");
    }

    /* Set color for new menu entry (0: no new entry) */
    if (next != 0) {
        wattron(window, COLOR_PAIR(2));
        mvwprintw(window, next, 8, "*");
        wattroff(window, COLOR_PAIR(2));
    }

    wrefresh(window);
}

void MainPanel::doRequest(int entry) {
    switch(entry) {
        case START_LINE:
            display->displayWait();
            break;
        case START_LINE+4:
            display->displayFriendsWindow();
            break;
        default:
            display->displayFatalError("pas implémenter pour le moment");
            break;
    }
    refresh();
}
