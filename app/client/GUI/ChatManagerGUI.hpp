#ifndef CHATMANAGERGUI_H
#define CHATMANAGERGUI_H

#include <QApplication>
#include <QWidget>
#include <string>
#include <QTabWidget>
#include <QTabBar>
#include <QListWidget>
#include <QGridLayout>
#include "ChatWidget.hpp"

#include "Player.hpp"

#include "common/WizardLogger.hpp"

class ChatManagerGUI : public QWidget {
    Q_OBJECT

    static ChatManagerGUI* _instance;
    static std::map<std::string,ChatWidget*>_listTab;

    QGridLayout *_layout;
    QTabWidget *_tab;
    QListWidget *_friends;

public:
    ChatManagerGUI(QWidget* = 0);
    static inline ChatManagerGUI* getInstance(){return _instance;}
    void reqNewMessage(std::string, std::string, std::string);

signals:
    void sigNewMessage(QString, QString, QString);

private slots:
    void closeTab(int);
    void newTab(QListWidgetItem*);
    void newMessage(QString, QString, QString);

private:
    ChatWidget* getChatWidget(std::string);

};

#endif // CHATMANAGERGUI_H
