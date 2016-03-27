#include "DeckPanelCLI.hpp"

DeckPanelCLI::DeckPanelCLI(CLI* cli) : CLIPanel(cli) {
    /* We create mainWindow where player can select what to do */
    window = newwin(MAIN_HEIGTH, MAIN_WIDTH, 0, 0);
    keypad(window, TRUE);
    box(window, 0, 0);

    /* Attach a panel to window */
    panel = new_panel(window);

    /* Update the stacking order */
    update_panels();
    doupdate();
    
    wattron(window, COLOR_PAIR(2));
    mvwprintw(window, 1, 2, "DECK");
    wattroff(window, COLOR_PAIR(2));
    wattron(window, COLOR_PAIR(3));
    mvwprintw(window, 1, 8, "[WIP]");
    wattroff(window, COLOR_PAIR(3));
    
    refresh();
}

void DeckPanelCLI::updatePanel() {
    std::vector<std::string> deckList = Player::getPlayer()->getDecks();
    for (int i = 0 ; i < deckList.size() ; ++i) {
        char* toPrint = (char*) malloc(sizeof(char)*60);
        snprintf(toPrint, 60, "* %d : %s", i+1, deckList[i].c_str()); //TODO deck contents
        mvwprintw(window, i+3, 2, toPrint);
        free(toPrint);
    }
    
    wrefresh(window);
}

void DeckPanelCLI::show() {
    show_panel(panel);
    update_panels();
    doupdate();
    
    /* Update content */
    updatePanel();
}

void DeckPanelCLI::hide() {
    hide_panel(panel);
    update_panels();
    doupdate();
}

void DeckPanelCLI::focus() {
    /* Set focus to MainPanelCLI */
    top_panel(panel);
    update_panels();
    doupdate();

    int input; //TODO add/remove deck
    while((input = wgetch(window)) != KEY_F(10)) {
        switch(input) {
            case KEY_F(1):
                _cli->focusTchat();
                break;
            default:
                beep();
                break;
        }
    }
}
