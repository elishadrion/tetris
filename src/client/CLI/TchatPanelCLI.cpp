#include "TchatPanelCLI.hpp"

/* Define static member to can use it */
std::vector<std::string> TchatPanelCLI::_messageBuffer;
std::string TchatPanelCLI::_consoleBuffer[TCHAT_HEIGHT-2];

TchatPanelCLI::TchatPanelCLI(CLI* cli) : CLIPanel(cli) {
    /* We create the tchatBox/consoleBox */
    windows[0] = newwin(TCHAT_HEIGHT, TCHAT_WIDTH, 0, 65+2);
    box(windows[0], 0, 0);
    
    /* We create inputBox for tchat/console with form and field */
    int rows, cols;
    for (int i = 0 ; i < INPUT_HEIGHT-2 ; ++i) field[i] = new_field(1, INPUT_WIDTH-3, i, 0, 0, 0);
    field_opts_off(field[INPUT_HEIGHT-3], O_AUTOSKIP); /* Last field don't pass to first field */
    form = new_form(field);
    scale_form(form, &rows, &cols);
    
    /* Create window for input box */
    windows[1] = newwin(rows+2, cols+3, TCHAT_HEIGHT, 65+2);
    box(windows[1], 0, 0);
    keypad(windows[1], TRUE);

	/* Set main window and sub window */
    set_form_win(form, windows[1]);
    set_form_sub(form, derwin(windows[1], rows, cols, 1, 1));
    
    /* Attach a panel to tchat window */
    panel = new_panel(windows[0]);
    hide_panel(panel);

    /* Update the stacking order */
    update_panels();
    
    /* Launch thread for tchat/console completion (throw error if failed) */
    try {
        _mutex = PTHREAD_MUTEX_INITIALIZER;
        threadData data;
        data.mutex = &_mutex;
        data.win = windows[0];
        if (pthread_create(&_tchatThread, NULL, updateTchat, (void*) &data) == -1) {
            std::string error = "Impossible d'initialiser le tchat : ";
            error += strerror(errno);
            throw std::runtime_error(error);
        }
    } catch (const std::runtime_error &error) {
        throw;
    }
    
    doupdate();
    refresh();
}

TchatPanelCLI::~TchatPanelCLI() {
    /* We must stop the thread before exiting */
    if (_tchatThread != NULL)
        pthread_cancel(_tchatThread);
    pthread_mutex_destroy(&_mutex);
}

/* Add a message in the tchat/console buffer
 * Message will be printed by the tchatThread
 * If buffer is full, calling thread must wait to have some place
 * @param message : what to print
 */
void TchatPanelCLI::addMessage(std::string message) {
    /* Block buffer access */
    pthread_mutex_lock(&_mutex);
    
    /* We complete string and add it in waiting list */
    for (int i = message.size() ; i < TCHAT_WIDTH-3 ; ++i) message += " ";
    _messageBuffer.insert(_messageBuffer.begin(), message);
        
    /* Unblock buffer access */
    pthread_mutex_unlock(&_mutex);
}

void TchatPanelCLI::show() {
    show_panel(panel);
    update_panels();
    doupdate();
    /* Post form */
    post_form(form);
    wrefresh(windows[1]);
}

void TchatPanelCLI::focus() {
    /* Set focus on the field and move cursor to it */
    form_driver(form, REQ_FIRST_FIELD);
    form_driver(form, REQ_END_LINE);
    _index = 0;
    _size = 0;
    wrefresh(windows[1]);

    /* Loop through to get user requests */
    int input;
    while((input = wgetch(windows[1])) != KEY_F(1)) {
        switch(input) {
            case KEY_LEFT:
                /* Go to the previous character */
                if (_index == 0 || _size == 0) {
                    beep();
                } else if (_index%(INPUT_WIDTH-3) == 0) {
                    form_driver(form, REQ_PREV_FIELD);
                    form_driver(form, REQ_END_LINE);
                    _index -= 1;
                } else {
                    form_driver(form, REQ_LEFT_CHAR);
                    _index -= 1;
                }
                break;
            case KEY_RIGHT:
                /* Go to the next character (or empty area) */
                if (_index == _size || _size == 0) {
                    beep();
                } else if (_index%(INPUT_WIDTH-3) == (INPUT_WIDTH-4)) {
                    form_driver(form, REQ_NEXT_FIELD);
                    form_driver(form, REQ_BEG_LINE);
                    _index += 1;
                } else {
                    form_driver(form, REQ_RIGHT_CHAR);
                    _index += 1;
                }
                break;
            case KEY_BACKSPACE:
                /* Remove previous character (if available) */
                if (_index == 0 || _size == 0) {
                    beep();
                } else if (_index%(INPUT_WIDTH-3) == 0) {
                    form_driver(form, REQ_PREV_FIELD);
                    form_driver(form, REQ_END_LINE);
                    form_driver(form, REQ_LEFT_CHAR);
                    form_driver(form, REQ_DEL_CHAR);
                    _index -= 1;
                    _size -= 1;
                } else {
                    form_driver(form, REQ_LEFT_CHAR);
                    form_driver(form, REQ_DEL_CHAR);
                    _index -= 1;
                    _size -= 1;
                }
                break;
            case KEY_F(2):
                //TODO get fields text and call proceed() to check if it's a command
                beep();
            default:
                form_driver(form, input);
                _size += 1;
                _index += 1;
                break;
        }
        
        /* Don't forget to refresh */
        wrefresh(windows[1]);
    }
}

//===============================PRIVATE=============================================

void *TchatPanelCLI::updateTchat(void* data) {
    /* Enable asynchronous cancel (thread can be canceled at any time) from deferred */
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, (int*) PTHREAD_CANCEL_DEFERRED);
    
    /* Get pointer to the mutex and the window */
    struct threadData *arg = (threadData*) data;
    pthread_mutex_t *mutex = arg->mutex;
    WINDOW *win = arg->win;
    
    while(1) {
        if (!_messageBuffer.empty()) {
            /* Block buffer access */
            pthread_mutex_lock(mutex);
            
            /* Write all buffer content */
            int size = _messageBuffer.size();
            for (int i = 0 ; i < size ; ++i) {
                /* We move all text up and write new text in bottom */
                for (int j = TCHAT_HEIGHT-3 ; j > 0 ; --j) _consoleBuffer[j] = _consoleBuffer[j-1];
                _consoleBuffer[0] = _messageBuffer.back();
                _messageBuffer.pop_back();
            }
        
            /* Unblock buffer access */
            pthread_mutex_unlock(mutex);
        
            /* Write in panel */
            for (int i = 0 ; i < TCHAT_HEIGHT-2 ; ++i) mvwprintw(win, TCHAT_HEIGHT-i-2, 2, (char*)_consoleBuffer[i].c_str());
            wrefresh(win);
        }
        
        /* Sleep for 1 milliseconde */
        usleep(1000);
    }
}
