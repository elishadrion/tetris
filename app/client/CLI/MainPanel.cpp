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

    /* Display menu entry */
    mvwprintw(window, START_LINE, 8, "* Commencer une partie");
    mvwprintw(window, START_LINE+2, 8, "* Afficher la collection");
    mvwprintw(window, START_LINE+4, 8, "* Liste d'amis");
    attron(COLOR_PAIR(3));
    mvwprintw(window, START_LINE+6, 8, "F10 pour quitter le programme");
    attroff(COLOR_PAIR(3));
    mvwprintw(window, START_LINE+8, 10, "(utiliser F1 pour accéder au Tchat)");
    refresh();
}

MainPanel::~MainPanel() {
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

    /* Loop through to get user requests with F1 to go to the tchatPanel */
    int input;
    while((input = getch()) != KEY_ENTER) {
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
            case KEY_F(10):
                /* Call closing methode to stop program */

                return;
            default:
                beep();
                break;
        }
    }
}

//=======================================================================

void MainPanel::updateColor(int previous, int next) {
    /* Remove color from previous menu entry (0: no previous entry) */
    if (previous != 0) {
        mvprintw(previous, 8, "*");
    }

    /* Set color for new menu entry (0: no new entry) */
    if (next != 0) {
        attron(COLOR_PAIR(2));
        mvprintw(next, 8, "*");
        attroff(COLOR_PAIR(2));
    }

    refresh();
}

void MainPanel::doRequest(int entry) {
}
