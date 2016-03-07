#include "WaitPanelCLI.hpp"

WaitPanelCLI::WaitPanelCLI() : _inGame(false) {
    /* We create mainWindow where player can select what to do */
    window = newwin(MAIN_HEIGTH, MAIN_WIDTH, 0, 0);
    box(window, 0, 0);
    keypad(window, TRUE);

    /* Attach a panel to window */
    panel = new_panel(window);

    /* Update the stacking order */
    update_panels();
    doupdate();

    /* Display menu entry */
    wattron(window, COLOR_PAIR(6));
    mvwprintw(window, 4, 8, "EN ATTENTE D'UN ADVERSAIRE...");
    wattroff(window, COLOR_PAIR(6));
    refresh();
}
    
void WaitPanelCLI::show() {
    show_panel(panel);
    update_panels();
    doupdate();
}

void WaitPanelCLI::hide() {
    hide_panel(panel);
    update_panels();
    doupdate();
}

void WaitPanelCLI::focus() {
    /* Set focus to mainPanel */
    top_panel(panel);
    update_panels();
    doupdate();
    
    PacketManager::registerAsPlayer();

    /* Loop through to get user requests with F1 to valide */
    int input;
    while((input = wgetch(window)) != KEY_F(10) && !_inGame) {
        if (input == KEY_F(1))
            wizardDisplay->focusTchat();
        else
            beep();
        wrefresh(window);
    }
    
    /* If we are in game mode, display gamePanel. Else we send cancel packet to server
    if (_inGame)
        wizardDisplay->displayGame();
    //else
        //TODO send cancel packet PacketManager::sendDisconnection();*/
}
