#include "CollectionPanelCLI.hpp"

CollectionPanelCLI::CollectionPanelCLI(CLI* cli) : CLIPanel(cli), currentLine(0) {
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
    mvwprintw(window, 1, 2, "COLLECTION");
    wattroff(window, COLOR_PAIR(2));
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, 1, 14, "[NOT WORKING]");
    wattroff(window, COLOR_PAIR(1));
    
    refresh();
}

void CollectionPanelCLI::updatePanel() {
    unsigned *collection = Player::getPlayer()->getCollection();
    unsigned j = currentLine;
    for (int i = 0 ; i < MAIN_HEIGTH-4 ; ++i) {
        while (j < MAX_CARDS-MAIN_HEIGTH-4 && collection[j] == 0) ++j;
        /* If we have card to put, we put it */
        if (j < MAX_CARDS-MAIN_HEIGTH-4 && collection[j] > 0) {
            char* toPrint = (char*) malloc(sizeof(char)*60);
            Card *card = CacheManager::getCard(j+1);
            snprintf(toPrint, 60, "* (%dx) %s : %s", collection[j], card->getName().c_str(), card->getDescription().c_str());
            mvwprintw(window, i+3, 2, toPrint);
            free(toPrint);
            ++j;
        }
    }
    
    wrefresh(window);
}

void CollectionPanelCLI::show() {
    show_panel(panel);
    update_panels();
    doupdate();
    
    /* Update content */
    updatePanel();
}

void CollectionPanelCLI::hide() {
    hide_panel(panel);
    update_panels();
    doupdate();
}

void CollectionPanelCLI::focus() {
    /* Set focus to MainPanelCLI */
    top_panel(panel);
    update_panels();
    doupdate();

    int input;
    while((input = wgetch(window)) != KEY_F(10)) {
        switch(input) {
            case KEY_DOWN:
                if (currentLine == MAX_CARDS-MAIN_HEIGTH-4) {
                    beep();
                } else {
                    currentLine -= 1;
                    updatePanel();
                }
                break;
            case KEY_UP:
                if (currentLine == 0) {
                    beep();
                } else {
                    currentLine += 1;
                    updatePanel();
                }
                break;
            case KEY_F(3):
                _cli->displayDeckWindow();
                break;
            case KEY_F(1):
                _cli->focusTchat();
                break;
            default:
                beep();
                break;
        }
    }
}
