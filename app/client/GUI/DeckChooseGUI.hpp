#ifndef DECKCHOOSEGUI_H
#define DECKCHOOSEGUI_H

#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QGridLayout>
#include <QButtonGroup>
#include <QPushButton>

#include "client/Player.hpp"


class DeckChooseGUI;
class GameGUI;
#include "GameGUI.hpp"


class DeckChooseGUI : public QMainWindow {

    GameGUI* _gameGui;
    QWidget *_centralWidget;
    QListWidget* _listDeck;
    QGridLayout* _gridlayout;

public:
    DeckChooseGUI(GameGUI*);

};




#endif // DECKCHOOSEGUI_H
