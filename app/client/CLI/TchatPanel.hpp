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
#define TCHAT_HEIGHT 21
#define TCHAT_WIDTH 30
#define INPUT_HEIGHT 7
#define INPUT_WIDTH TCHAT_WIDTH

class TchatPanel : CLIPanel {
    WINDOW *windows[2];
    PANEL  *panels[2];
    
    pthread_t _tchatThread;
    pthread_mutex_t _mutex;
    struct threadData {
        pthread_mutex_t *mutex;
        WINDOW *win;
    };
    
    static std::vector<std::string> _messageBuffer;
    static std::string _consoleBuffer[TCHAT_HEIGHT];
    
    static void *updateTchat(void*);
public:
    TchatPanel();
    ~TchatPanel();
    
    void addMessage(std::string);
    void listenInput();
    
    void show();
    void hide();
    void focus();
};

#endif	/* TCHATPANEL_HPP */
