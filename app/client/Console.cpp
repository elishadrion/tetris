#include "Console.hpp"
//#include <LoginPanel.hpp>

Console::Console() {
    /* Start curses mode */
    initscr();
    
    /* Use default behavior for special key like CTRL-Z */
    cbreak();
    
    /* Initialize the usage of navigation key and FX key */
    keypad(stdscr, TRUE);
    
    /* Dont print why user input directly, we manage it */
    noecho();
    
    /* Create the main panel of the program */
    mainPanel = new NCursesPanel();
    
    /* We create a bordure on the windows */
    mainPanel->box();
    
    /* At startup, we display the login panel */
    loginPanel = new NCursesPanel(LINES, COLLONNES, 8, 8); //TODO
    
    /* Update panel and display window */
    mainPanel->refresh();
}

Console::~Console() {
    /* End curses mode */
    endwin();
}
