#include "WaitPanelCLI.hpp"

WaitPanelCLI::WaitPanelCLI(CLI* cli) : CLIPanel(cli), _inGame(false) {
    /* We create mainWindow where player can select what to do */
    windows[0] = newwin(MAIN_HEIGTH, MAIN_WIDTH, 0, 0);
    box(windows[0], 0, 0);
    keypad(windows[0], TRUE);

    /* Attach a panel to window */
    panel = new_panel(windows[0]);

    /* Update the stacking order */
    update_panels();
    doupdate();
    
    /* Field to ask pseudo */
    field[0] = new_field(1, 23, 1, 2, 0, 0);
    set_field_buffer(field[0], 0, "Deck (F9 : Valider) :");
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
    wattron(windows[0], COLOR_PAIR(6));
    mvwprintw(windows[0], 4, 8, "EN ATTENTE D'UN ADVERSAIRE...");
    wattroff(windows[0], COLOR_PAIR(6));
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
    
    PacketManager::makeGameRequest();

    /* Loop through to get user requests with F1 to valide */
    int input;
    while(!_inGame) {
        input = wgetch(windows[0]);
        if (input == KEY_F(1)) {
            _cli->focusTchat();
        } else if (input == KEY_F(10)) {
            PacketManager::makeGameCancelRequest();
            break;
        } else {
            beep();
        }
        wrefresh(windows[0]);
    }
    
    if (_inGame)
        askDeck();
}

void WaitPanelCLI::startGame() {
    _inGame = true;
    
    wattron(windows[0], COLOR_PAIR(3));
    mvwprintw(windows[0], 4, 8, "APPUYER SUR UNE TOUCHE POUR CHOISIR LE DECK");
    wattroff(windows[0], COLOR_PAIR(3));
    wrefresh(windows[0]);
}

void WaitPanelCLI::askDeck() {
    /* Give focus, clear buffer and refresh */
    set_current_field(form, field[1]);
    form_driver(form, REQ_CLR_FIELD);
    form_driver(form, REQ_END_LINE);
    wrefresh(windows[1]);
    
    /* Loop through to get user requests */
    int index = 0;
    int size = 0;
    int input;
    while(input = wgetch(windows[1])) {
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
                
                /* Get the name from the first field */
                if (checkDeck(field_buffer(field[1], 0))) {
                    _cli->displayGame();
                    return;
                }
                
                beep();
                break;
            default:
                /* If it's the SPACEBAR, we beep */
                if (size == MAX_DECK_NAME) {
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

bool WaitPanelCLI::checkDeck(char* name) {
    std::vector<std::string> deckList = Player::getPlayer()->getDecks();
    std::string deckName(name);
    deckName.erase(remove_if(deckName.begin(), deckName.end(), isspace), deckName.end());
    
    /* check if deck is valide */
    if (find(deckList.begin(), deckList.end(), deckName) != deckList.end()) {
        GameManager::getInstance()->setDeck(deckName);
        return true;
    }
    return false;
}
