#include "CollectionPanelCLI.hpp"

CollectionPanelCLI::CollectionPanelCLI() {
    /* We create mainWindow where player can select what to do */
    window = newwin(MAIN_HEIGTH, MAIN_WIDTH, 0, 0);
    box(window, 0, 0);

    /* Attach a panel to window */
    panel = new_panel(window);

    /* Update the stacking order */
    update_panels();
    doupdate();
    
    attron(COLOR_PAIR(1));
    mvwprintw(window, 1, 2, "[WIP]");
    attroff(COLOR_PAIR(1));
    
    /* Update collection from server */
    //PacketManager::requestCollection();
    
    /* Display */
    updatePanel();
}

void CollectionPanelCLI::updatePanel() {
    for (int i = 0 ; i < MAIN_HEIGTH ; ++i) {
        /* If we have card to put, we put it */
        if (i < _collection.size()) {
            char* ID = (char*) malloc(sizeof(char)*10);
            snprintf(ID, 10, "* ID : %d", _collection[i]);
            mvwprintw(window, i+2, 2, ID);
        }
    }
}

/* Add cards to local cache of collection
 * After that, update panel to display new card
 * TODO save collection cache in a player object ?
 * @param number : number of cards to add
 * @param cardList : array of cardID to add
 */
void CollectionPanelCLI::addCardToCollection(int number, int* cardList) {
    for (int i = 0 ; i < number ; ++i) _collection.push_back(cardList[i]);
    updatePanel();
}

void CollectionPanelCLI::show() {
    show_panel(panel);
    update_panels();
    doupdate();
}

void CollectionPanelCLI::hide() {
    hide_panel(panel);
    update_panels();
    doupdate();
}

void CollectionPanelCLI::focus() {
}
