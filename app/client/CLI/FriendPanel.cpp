#include "FriendPanel.hpp"

FriendPanel::FriendPanel() {
    /* We create mainWindow where player can select what to do */
    windows[0] = newwin(FRIEND_HEIGHT, FRIEND_WIDTH, 0, 0);
    box(windows[0], 0, 0);
    keypad(windows[0], TRUE);

    /* Attach a panel to window */
    panel = new_panel(windows[0]);

    /* Update the stacking order */
    update_panels();
    doupdate();
    
    /* Field to ask pseudo */
    field[0] = new_field(1, 23, 1, 2, 0, 0);
    set_field_buffer(field[0], 0, "Pseudo (F9 : Valider) :");
    field[1] = new_field(1, 31, 1, 24, 0, 0);
    set_field_back(field[1], A_UNDERLINE);
    
    /* Create the form and calculate size needed */
    int rows, cols;
    form = new_form(field);
    scale_form(form, &rows, &cols);

    /* Create the window to be associated with the form */
    windows[1] = newwin(rows+5, cols+5, 4, 4);
    keypad(windows[1], TRUE);

    /* Set main window and sub window */
    set_form_win(form, windows[1]);
    set_form_sub(form, derwin(windows[1], rows, cols, 2, 2));

    /* Print a border, post form and hide all */
    box(windows[1], 0, 0);
    post_form(form);

    /* Display menu entry */
    mvwprintw(windows[0], 2, 2, "Commandes du tchat : ");
    mvwprintw(windows[0], 4, 4, "* Commencez une conversation avec un ami : /msg <pseudo>");
    mvwprintw(windows[0], 6, 4, "* Quitter une conversation : /quit");
    mvwprintw(windows[0], 8, 2, "!> une seul conversation à la fois en mode console");
    refresh();
}

FriendPanel::~FriendPanel() {
    unpost_form(form);
    free_form(form);
    free_field(field[0]);
    free_field(field[1]);
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

    /* Loop through to get user requests with F1 to valide */
    int input;
    while((input = wgetch(windows[0])) != KEY_F(10)) {
        switch(input) {
            case KEY_F(1):
                display->focusTchat();
                break;
            case KEY_F(3):
                manageFriend();
                return;
            case KEY_F(4):
                manageFriend(true);
                return;
            default:
                beep();
                break;
        }
        
        /* Don't forget to refresh */
        wrefresh(windows[0]);
    }
}

//================================PRIVATE=======================================

void FriendPanel::updateList() {
    PacketManager::askFriendsList();
    //TODO get friends list from Player and display pseudo
    refresh();
}

void FriendPanel::manageFriend(bool remove) {
    /* Give focus, clear buffer and refresh */
    mvwin(windows[1], 10, 4);
    set_current_field(form, field[1]);
    form_driver(form, REQ_CLR_FIELD);
    form_driver(form, REQ_END_LINE);
    wrefresh(windows[1]);
    
    /* Loop through to get user requests */
    int index = 0;
    int size = 0;
    char *pseudo;
    int input;
    while((input = wgetch(windows[1])) != KEY_F(10)) {
        switch(input) {
            case KEY_LEFT:
                /* Go to the previous character (if available) */
                if (index == 0 || size == 0) {
                    beep();
                    form_driver(form, REQ_BEG_LINE);
                } else {
                    form_driver(form, REQ_LEFT_CHAR);
                    index -= 1;
                }
                break;
            case KEY_RIGHT:
                /* Go to the next character (if available) */
                if (index == size || size == 0) {
                    beep();
                    form_driver(form, REQ_END_LINE);
                } else {
                    form_driver(form, REQ_RIGHT_CHAR);
                    index += 1;
                }
                break;
            case KEY_BACKSPACE:
                /* Remove previous character (if available) */
                if (index == 0 || size == 0) {
                    beep();
                    form_driver(form, REQ_BEG_LINE);
                } else {
                    form_driver(form, REQ_LEFT_CHAR);
                    form_driver(form, REQ_DEL_CHAR);
                    index -= 1;
                    size -= 1;
                }
                break;
            case KEY_F(9):
                /* Sync buffer */
                form_driver(form, REQ_VALIDATION);
                
                /* Get the pseudo from the first field */
                pseudo = field_buffer(field[1], 0);
                
                /* Send it to the server */
                PacketManager::manageFriend(pseudo, remove);
                
                return;
            default:
                /* If it's the SPACEBAR, we beep */
                if (input == ' ') {
                    beep();
                    form_driver(form, REQ_END_LINE);
                } else if (size == 30) {
                    beep();
                    form_driver(form, REQ_END_LINE);
                } else {
                    form_driver(form, input);
                    index += 1;
                    size += 1;
                }
                break;
        }
        
        /* Don't forget to refresh */
        wrefresh(windows[1]);
    }
}
