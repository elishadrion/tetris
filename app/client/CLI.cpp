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
    _panelList[0] = new MainPanel();
    _panelList[1] = new CollectionPanel();
}

CLI::~CLI() {
    /* End curses mode */
    WizardLogger::info("Désactivation du mode ncurses");
    for (int i = 0 ; i < PANEL_TOTAL_NUMBER ; ++i) delete _panelList[i];
    if (loginDisplay) {
        delete loginPanel;
        loginDisplay = false;
    }
    endwin();
}

void CLI::displayFatalError(std::string error) {
    /* Clean screen and display error and force quit */
    endwin();
    std::cout << "\n\n========================" << std::endl;
    std::cout << error << "\n========================\n\n" << std::endl;
    exit(-1);
}

void CLI::displayLoginPrompt() {
    /* Display login panel (special type of panel) */
    loginPanel =  new LoginPanel();
    loginDisplay = true;
    loginPanel->askLogin();
}

void CLI::displayLoginResult(std::string errorMessage) {
    loginPanel->printError(errorMessage);
}

void CLI::valideLogin() {
    loginPanel->valideLogin();
}

void CLI::displayMainWindow() {
    /* If we are from loginPanel, we remove it */
    if (loginDisplay) {
        delete loginPanel;
        loginDisplay = false;
    }
    
    /* We display MainMenu after hidding all other panel */
    for (int i = 0 ; i < PANEL_TOTAL_NUMBER ; ++i) _panelList[i]->hide();
    _panelList[0]->show();
    _panelList[0]->focus();
}

void CLI::displayCollectionWindow() {
    /* We display CollectionPanel after hidding all other panel */
    for (int i = 0 ; i < PANEL_TOTAL_NUMBER ; ++i) _panelList[i]->hide();
    _panelList[1]->show();
    _panelList[1]->focus();
}

void CLI::updateCollection(int number, int* cardList) {
    ((CollectionPanel*)_panelList[1])->addCardToCollection(number, cardList);
}

void CLI::displayWait() {
    clear();
    mvprintw(2, 10, "EN ATTENTE D'ADVERSAIRE....");
}
