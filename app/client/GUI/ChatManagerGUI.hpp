#ifndef CHATMANAGERGUI_H
#define CHATMANAGERGUI_H

#include <QApplication>
#include <QWidget>
#include <string>
#include <QTabWidget>
#include <QTabBar>
#include <QListWidget>
#include "ChatWidget.hpp"

class ChatManagerGUI : public QWidget{
Q_OBJECT
public:
    ChatManagerGUI();
private:
    QTabWidget *_tab;
    QListWidget *_friends;

private slots:
    void closeTab(int);
    void newTab(QListWidgetItem*);

};

#endif // CHATMANAGERGUI_H
