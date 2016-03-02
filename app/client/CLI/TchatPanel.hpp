#ifndef TCHATPANEL_HPP
#define	TCHATPANEL_HPP

#include <panel.h>
#include <form.h>

/* For sleep() */
#include <unistd.h>

#include <pthread.h>
#include <string>
#include <vector>

#include "common/WizardLogger.hpp"

#include "CLIPanel.hpp"

/* define size for panel */
#define TCHAT_HEIGHT 23
#define TCHAT_WIDTH 30
#define INPUT_HEIGHT 7
#define INPUT_WIDTH TCHAT_WIDTH

class TchatPanel : public CLIPanel {
    WINDOW *windows[2];
    PANEL  *panel;
    FORM  *form;
    FIELD *field[INPUT_HEIGHT-2];
    
    /* LOCK, tchatPanel never hide after loggin */
    bool _isDisplay;
    
    /* Thread to add message into the console */
    pthread_t _tchatThread;
    pthread_mutex_t _mutex;
    struct threadData {
        pthread_mutex_t *mutex;
        WINDOW *win;
    };
    static void *updateTchat(void*);
    
    /* Console/tchat buffer and wait list vector */
    static std::vector<std::string> _messageBuffer;
    static std::string _consoleBuffer[TCHAT_HEIGHT-2];
public:
    TchatPanel();
    ~TchatPanel();
    
    void addMessage(std::string);
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* TCHATPANEL_HPP */
