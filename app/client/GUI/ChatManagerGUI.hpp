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

#include "common/WizardLogger.hpp"

class ChatManagerGUI : public QWidget {
    Q_OBJECT

    QGridLayout *_layout;
    QTabWidget *_tab;
    QListWidget *_friends;

public:
    ChatManagerGUI(QWidget*);

private slots:
    void closeTab(int);
    void newTab(QListWidgetItem*);

};

#endif // CHATMANAGERGUI_H
