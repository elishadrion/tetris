#include "TchatPanel.hpp"

/* Define static member to can use it */
std::vector<std::string> TchatPanel::_messageBuffer;
std::string TchatPanel::_consoleBuffer[TCHAT_HEIGHT];

TchatPanel::TchatPanel() {
    /* We create the tchatBox/consoleBox */
    windows[0] = newwin(TCHAT_HEIGHT, TCHAT_WIDTH, 0, 65+2);
    box(windows[0], 0, 0);
    
    /* We create inputBox for tchat/console */
    windows[1] = newwin(INPUT_HEIGHT, INPUT_WIDTH, TCHAT_HEIGHT, 65+2);
    box(windows[1], 0, 0);
    keypad(windows[1], TRUE);
    
    /* Attach a panel to each window */
    panels[0] = new_panel(windows[0]);
    panels[1] = new_panel(windows[1]);

    /* Update the stacking order */
    update_panels();
    
    /* Launch thread for tchat/console completion */
    _mutex = PTHREAD_MUTEX_INITIALIZER;
    threadData data;
    data.mutex = &_mutex;
    data.win = windows[0];
    if (pthread_create(&_tchatThread, NULL, updateTchat, (void*) &data) == -1) {
        std::string error = "Impossible d'initialiser le tchat : ";
        error += strerror(errno);
        WizardLogger::error(error);
        //TODO throw
    }
    
    doupdate();
}

TchatPanel::~TchatPanel() {
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
void TchatPanel::addMessage(std::string message) {
    /* Block buffer access */
    pthread_mutex_lock(&_mutex);
    
    /* If string is small, we directly add it */
    if (message.size() < TCHAT_WIDTH) {
        _messageBuffer.insert(_messageBuffer.begin(), message);
    } else {
        /* We must divise message in line and add it to the buffer backwards */
        for (int i = 0 ; i < (message.size()/TCHAT_WIDTH) ; ++i) {
            std::string tmp = message.substr(message.size()-(TCHAT_WIDTH*(i+1)), message.size()-(TCHAT_WIDTH*i+1));
            _messageBuffer.insert(_messageBuffer.begin(), tmp);
        }
    }
        
    /* Unblock buffer access */
    pthread_mutex_unlock(&_mutex);
}

void TchatPanel::show() {
    show_panel(panels[0]);
    show_panel(panels[1]);
    update_panels();
    doupdate();
}

void TchatPanel::hide() {
    hide_panel(panels[0]);
    hide_panel(panels[1]);
    update_panels();
    doupdate();
}

void TchatPanel::focus() {
    /* Set focus to input panel */
    top_panel(panels[1]);
    update_panels();
    doupdate();

    /* TODO test */
    int input;
    while((input = wgetch(windows[1])) != KEY_F(10)) {
        addMessage("JE SUIS UN MESSAGE  ~  ");
    }
}

//===============================PRIVATE=============================================

void *TchatPanel::updateTchat(void* data) {
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
                for (int j = 0 ; j < TCHAT_HEIGHT-1 ; ++j) _consoleBuffer[j+1] = _consoleBuffer[j];
                _consoleBuffer[0] = _messageBuffer.back();
                _messageBuffer.pop_back();
            }
        
            /* Unblock buffer access */
            pthread_mutex_unlock(mutex);
        
            /* Write in panel */
            for (int i = 0 ; i < TCHAT_HEIGHT ; ++i) mvwprintw(win, i, 0, (char*)_consoleBuffer[i].c_str());
            refresh();
        }
        
        /* Sleep for 1 sec */
        sleep(1);
    }
}
