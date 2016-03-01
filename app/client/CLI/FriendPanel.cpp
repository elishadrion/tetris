#include "FriendPanel.hpp"

FriendPanel::FriendPanel() {
    /* We create mainWindow where player can select what to do */
    window = newwin(FRIEND_HEIGHT, FRIEND_WIDTH, 0, 0);
    box(window, 0, 0);
    keypad(window, TRUE);

    /* Attach a panel to window */
    panel = new_panel(window);

    /* Update the stacking order */
    update_panels();
    doupdate();

    /* Display menu entry */
    mvwprintw(window, 2, 8, "Tapez l'une de ses commandes dans le tchat");
    mvwprintw(window, 4, 8, "* Ajouter un ami : /add <pseudo>");
    mvwprintw(window, 6, 8, "* Supprimer un ami : /remove <pseudo>");
    mvwprintw(window, 8, 8, "* Commencer une conversation : /connect <pseudo>");
    mvwprintw(window, 10, 8, "!> une seul conversation à la fois en console");
    mvwprintw(window, 12, 8, "(utiliser F2 pour accéder au Tchat)");
    mvwprintw(window, 14, 8, "F10: retour");
    refresh();
}

void FriendPanel::show() {
    /* Update friends list from server before display it */
    updateList();
    show_panel(panel);
    update_panels();
    doupdate();
}

void FriendPanel::hide() {
    hide_panel(panel);
    update_panels();
    doupdate();
}

void FriendPanel::focus() {
    /* Set focus to mainPanel */
    top_panel(panel);
    update_panels();
    doupdate();

    /* Loop through to wait user return input */
    int input;
    while((input = wgetch(window)) != KEY_F(10)) {
        display->focusTchat();
        updateList();
    }
}

//================================PRIVATE=======================================

void FriendPanel::updateList() {
    //TODO get list from server and draw on panel
    refresh();
}
