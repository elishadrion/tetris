#ifndef FRIENDSPANELGUI_H
#define FRIENDSPANELGUI_H


#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QFont>
#include <QInputDialog>
#include <QDir>


#include "client/CacheManager.hpp"

class FriendsPanelGUI;
#include "MenuPanelGUI.hpp"
#include "PacketManager.hpp"
#include "client/WizardDisplay.hpp"

extern WizardDisplay *wizardDisplay;

class FriendsPanelGUI : public QMainWindow {
    Q_OBJECT

    MenuPanelGUI* _menu;

    int friendPos = 0;
    QLabel *_people;
    QVBoxLayout *_layoutPeople;

    QPushButton *_back;
    QPushButton *_addFriend;
    QPushButton *_removeFriend;

public:
    FriendsPanelGUI(MenuPanelGUI*);

private slots:
    void showFriends(QGridLayout*);
    void addFriend();
    void makeClose();
};


#endif /* FRIENDSPANELGUI_H */
