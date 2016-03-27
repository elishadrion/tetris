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


#include "client/CacheManager.hpp"

class FriendsPanelGUI;
#include "MenuPanelGUI.hpp"
#include "PacketManager.hpp"
#include "client/WizardDisplay.hpp"

extern WizardDisplay *wizardDisplay;

class FriendsPanelGUI : public QMainWindow {
    Q_OBJECT

    MenuPanelGUI* _menu;

    QLabel *_people;

    QPushButton *_back;
    QPushButton *_addFriend;
    QPushButton *_removeFriend;
    QVBoxLayout *_layoutPeople;

public:
    FriendsPanelGUI(MenuPanelGUI*);

private slots:
    void makeClose();

};


#endif /* FRIENDSPANELGUI_H */
