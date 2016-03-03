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
	    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	    init_pair(4, COLOR_BLUE, COLOR_BLACK);
	    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	    init_pair(6, COLOR_CYAN, COLOR_BLACK);
	    init_pair(7, COLOR_WHITE, COLOR_BLACK);
        refresh();
    }
    
    /* Create panel and form view */
    _panelList[LOGIN] = new LoginPanel();
    _panelList[MAIN] = new MainPanel();
    _panelList[TCHAT] = new TchatPanel();
    _panelList[FRIEND] = new FriendPanel();
    _panelList[COLL] = new CollectionPanel();
    _panelList[DECK] = new DeckPanel();
    _panelList[WAIT] = new WaitPanel();
    _panelList[GAME] = new GamePanel();
}

CLI::~CLI() {
    /* End curses mode */
    WizardLogger::info("Désactivation du mode ncurses");
    for (int i = 0 ; i < PANEL_TOTAL_NUMBER ; ++i) delete _panelList[i];
    endwin();
}

//=====================================================================================

void CLI::displayFatalError(std::string error) {
    /* Clean screen and display error and force quit */
    for (int i = 0 ; i < PANEL_TOTAL_NUMBER ; ++i) _panelList[i]->hide();
    attron(COLOR_PAIR(1));
    mvprintw(6, 4, "ERREUR FATAL, LE PROGRAMME VA DEVOIR SE COUPER");
    mvprintw(8, 4, (char*)error.c_str());
    attroff(COLOR_PAIR(1));
    mvprintw(10, 4, "Appuyer sur une touche pour quitter le programme...");
    refresh();
    
    /* Wait for input and force kill programme (after cleaning ncurse) */
    getch();
    endwin();
    exit(-1);
}

void CLI::displayLoginPrompt() {
    /* Display login panel after hidding all other panel */
    for (int i = 0 ; i < PANEL_TOTAL_NUMBER ; ++i) _panelList[i]->hide();
    _panelList[LOGIN]->show();
    _panelList[LOGIN]->focus();
    displayMainWindow();
}

void CLI::displayLoginResult(std::string errorMessage) {
    static_cast<LoginPanel*>(_panelList[LOGIN])->printError(errorMessage);
}

void CLI::valideLogin() {
    static_cast<LoginPanel*>(_panelList[LOGIN])->valideLogin();
}

void CLI::displayMainWindow() {
    /* Display general HELP */
    attron(COLOR_PAIR(6));
    mvprintw(LINES-2, 2, MAIN_LABEL);
    attron(COLOR_PAIR(6));
    
    /* We display MainMenu after hidding all other panel */
    for (int i = 0 ; i < PANEL_TOTAL_NUMBER ; ++i) _panelList[i]->hide();
    _panelList[MAIN]->show();
    _panelList[TCHAT]->show();
    _panelList[MAIN]->focus();
}

void CLI::displayFriendsWindow() {
    /* Display HELP for friends */
    attron(COLOR_PAIR(6));
    mvprintw(LINES-2, 2, AMIS_LABEL);
    attron(COLOR_PAIR(6));
    
    /* We display FriendList after hidding all other panel */
    for (int i = 0 ; i < PANEL_TOTAL_NUMBER ; ++i) _panelList[i]->hide();
    _panelList[FRIEND]->show();
    _panelList[TCHAT]->show();
    _panelList[FRIEND]->focus();
    
    /* After that, we hide and show the mainPanel */
    _panelList[FRIEND]->hide();
    _panelList[MAIN]->show();
    
    /* Display general HELP */
    attron(COLOR_PAIR(6));
    mvprintw(LINES-2, 2, MAIN_LABEL);
    attron(COLOR_PAIR(6));
}

void CLI::displayCollectionWindow() {
    /* Display HELP for collection */
    attron(COLOR_PAIR(6));
    mvprintw(LINES-2, 2, COLL_LABEL);
    attron(COLOR_PAIR(6));
    
    /* We display CollectionPanel after hidding all other panel */
    for (int i = 0 ; i < PANEL_TOTAL_NUMBER ; ++i) _panelList[i]->hide();
    _panelList[COLL]->show();
    _panelList[TCHAT]->show();
    _panelList[COLL]->focus();
    
    /* After that, we hide and show the mainPanel */
    _panelList[COLL]->hide();
    _panelList[MAIN]->show();
    
    /* Display general HELP */
    attron(COLOR_PAIR(6));
    mvprintw(LINES-2, 2, MAIN_LABEL);
    attron(COLOR_PAIR(6));
}

void CLI::displayDeckWindow() {
    /* Display HELP */
    attron(COLOR_PAIR(6));
    mvprintw(LINES-2, 2, DECK_LABEL);
    attron(COLOR_PAIR(6));
    
    /* We display CollectionPanel after hidding all other panel */
    for (int i = 0 ; i < PANEL_TOTAL_NUMBER ; ++i) _panelList[i]->hide();
    _panelList[DECK]->show();
    _panelList[TCHAT]->show();
    _panelList[DECK]->focus();
    
    /* After that, we hide and show the collectionPanel */
    _panelList[DECK]->hide();
    _panelList[COLL]->show();
    
    
    /* Display general HELP */
    attron(COLOR_PAIR(6));
    mvprintw(LINES-2, 2, MAIN_LABEL);
    attron(COLOR_PAIR(6));
}

void CLI::displayWait() {
    /* Display HELP */
    attron(COLOR_PAIR(6));
    mvprintw(LINES-2, 2, WAIT_LABEL);
    attron(COLOR_PAIR(6));
    
    /* We display CollectionPanel after hidding all other panel */
    for (int i = 0 ; i < PANEL_TOTAL_NUMBER ; ++i) _panelList[i]->hide();
    _panelList[WAIT]->show();
    _panelList[TCHAT]->show();
    _panelList[WAIT]->focus();
    
    /* After that, we hide and show the mainPanel */
    _panelList[WAIT]->hide();
    _panelList[MAIN]->show();
    
    /* Display general HELP */
    attron(COLOR_PAIR(6));
    mvprintw(LINES-2, 2, MAIN_LABEL);
    attron(COLOR_PAIR(6));
}

void CLI::displayGame() {
    /* Display HELP */
    attron(COLOR_PAIR(6));
    mvprintw(LINES-2, 2, GAME_LABEL);
    attron(COLOR_PAIR(6));
    
    /* We display CollectionPanel after hidding all other panel */
    for (int i = 0 ; i < PANEL_TOTAL_NUMBER ; ++i) _panelList[i]->hide();
    _panelList[GAME]->show();
    _panelList[TCHAT]->show();
    _panelList[GAME]->focus();
    
    /* After that, we hide and return to wait (returning to main) */
    _panelList[GAME]->hide();
}

void CLI::focusTchat() {
    _panelList[TCHAT]->focus();
}

//TODO
void CLI::displayPopup(std::string message) {}
