#include "Console.hpp"
//#include <LoginPanel.hpp>

void Console::init() {
    /* Start curses mode */
    initscr();
    
    /* We block default behavior for special key like CTRL-Z
     * So we must implement our method
     * But like this, we are certain to shutdown ncurse terminal specification
     */
    raw();
    
    /* Initialize the usage of navigation key and FX key */
    keypad(stdscr, TRUE);
    
    /* Dont print why user input directly, we manage it */
    noecho();
    
    /* Creates the main windows of the program */
    WINDOW *mainWindow = newwin(LINES, COLLONNES, 0, 0);
    
    /* We create a bordure on the windows */
    box(mainWindow, 0, 0);
    
    /* At startup, we display the login panel */
    PANEL *loginPanel = new_panel(mainWindow);
    
    /* Updates panel and displays window */
    update_panels();
    doupdate();
    
    getch();//TODO
}

void Console::close() {
    /* End curses mode */
    endwin();
}
