#ifndef TchatPanelCLI_HPP
#define	TchatPanelCLI_HPP

#include <panel.h>
#include <form.h>

/* For sleep() */
#include <unistd.h>

/* For error */
#include <iostream>
#include <cstring>

#include <pthread.h>
#include <string>
#include <vector>

class CLI;
#include "client/CLI.hpp"

class CLIPanel;
#include "CLIPanel.hpp"

/* define size for panel */
#define TCHAT_HEIGHT 23
#define TCHAT_WIDTH 30
#define INPUT_HEIGHT 7
#define INPUT_WIDTH TCHAT_WIDTH

class TchatPanelCLI : public CLIPanel {
    WINDOW *windows[2];
    PANEL  *panel;
    FORM  *form;
    FIELD *field[INPUT_HEIGHT-2];
    
    /* To control field position */
    int _index;
    int _size;
    
    
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
    TchatPanelCLI(CLI*);
    ~TchatPanelCLI();
    
    void addMessage(std::string);
    
    void show() override;
    void focus() override;
    
    /* Never used */
    void hide() {};
};

#endif	/* TchatPanelCLI_HPP */
