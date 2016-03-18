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

    /* Create panel and form view (if failed, client must quit) */
    try {
        _panelList[LOGIN] = new LoginPanelCLI();
        _panelList[MAIN] = new MainPanelCLI();
        _panelList[TCHAT] = new TchatPanelCLI();
        _panelList[FRIEND] = new FriendPanelCLI();
        _panelList[COLL] = new CollectionPanelCLI();
        _panelList[DECK] = new DeckPanelCLI();
        _panelList[WAIT] = new WaitPanelCLI();
        _panelList[GAME] = new GamePanelCLI();
    } catch (const std::runtime_error &error) {
        WizardLogger::fatal("Impossible de créer les panels de la CLI : ", error.what());
        endwin(); /* Ensure ncurses is desactivate */
        throw;
    }

    /* Hide all panel after login one */
    for (int i = 1 ; i < PANEL_TOTAL_NUMBER ; ++i) _panelList[i]->hide();
    refresh();
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
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(6, 4, "ERREUR FATAL, LE PROGRAMME VA DEVOIR SE COUPER");
    mvprintw(8, 4, (char*)error.c_str());
    attroff(COLOR_PAIR(1));
    mvprintw(10, 4, "Appuyer sur une touche pour quitter le programme");
    mvprintw(11, 4, " (il se peut que vous deviez appuyer deux fois)");
    refresh();

    /* Wait for input and force kill programme (after cleaning ncurse) */
    getch();
    endwin();
    exit(-1);
}

void CLI::displayLoginPrompt() {
    /* Display login panel */
    _panelList[LOGIN]->focus();
    displayMainWindow();
}

void CLI::displayLoginResult(std::string errorMessage) {
    static_cast<LoginPanelCLI*>(_panelList[LOGIN])->printError(errorMessage);
}

void CLI::valideLogin() {
    static_cast<LoginPanelCLI*>(_panelList[LOGIN])->valideLogin();
}

void CLI::displayMainWindow() {
    /* Display general HELP */
    attron(COLOR_PAIR(6));
    mvprintw(LINES-2, 2, MAIN_LABEL);
    attron(COLOR_PAIR(6));

    /* We display MainMenu */
    _panelList[LOGIN]->hide();
    _panelList[MAIN]->show();
    _panelList[TCHAT]->show();
    _panelList[MAIN]->focus();
}

void CLI::displayFriendsWindow() {
    /* Display HELP for friends */
    attron(COLOR_PAIR(6));
    mvprintw(LINES-2, 2, AMIS_LABEL);
    attron(COLOR_PAIR(6));

    /* We display FriendList */
    _panelList[FRIEND]->show();
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

    /* We display CollectionPanel */
    _panelList[COLL]->show();
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

    /* We display CollectionPanel */
    _panelList[DECK]->show();
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

    /* We display CollectionPanel */
    _panelList[WAIT]->show();
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

    /* We display CollectionPanel */
    _panelList[GAME]->show();
    _panelList[GAME]->focus();

    /* After that, we hide and return to wait (returning to main) */
    _panelList[GAME]->hide();
}

//TODO
void CLI::displayClassement() {}

void CLI::focusTchat() {
    _panelList[TCHAT]->focus();
}

//TODO
void CLI::diaplayError(std::string message) {}
