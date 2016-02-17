#include "CLI.hpp"

CLI::CLI() {
    /* Start curses mode */
    WizardLogger::info("Activation et configuration du mode ncurses");
    initscr();
    
    /* We use default behavior for special key like CTRL-C */
    cbreak();
    
    /* Initialize the usage of navigation key and FX key */
    keypad(stdscr, TRUE);
    
    /* Dont print why user input directly, we manage it */
    noecho();
    
    /* Start color system */
    if (has_colors()) {
        start_color();
	    init_pair(1, COLOR_RED, COLOR_BLACK);
	    init_pair(2, COLOR_GREEN, COLOR_BLACK);
	    init_pair(3, COLOR_BLUE, COLOR_BLACK);
	    init_pair(4, COLOR_CYAN, COLOR_BLACK);
        refresh();
    }
    
    /* Create panel and form view */
    loginPanel = new LoginPanel();
    
    /* Updates panel and displays window */
    update_panels();
    doupdate();
}

CLI::~CLI() {
    /* End curses mode */
    WizardLogger::info("Désactivation du mode ncurses");
    endwin();
}

void CLI::displayLoginPrompt() {
    /* We create all panel now (hidden by default except loginPanel) */
    loginPanel->askLogin();
}
