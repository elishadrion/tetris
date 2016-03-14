#ifndef DECKCHOOSEGUI_H
#define DECKCHOOSEGUI_H

#include <QMainWindow>
#include <QListWidget>

class DeckChooseGUI;
class GameGUI;
#include "GameGUI.hpp"


class DeckChooseGUI : public QMainWindow {
    GameGUI* _gameGui;

public:
    DeckChooseGUI(GameGUI*);

};




#endif // DECKCHOOSEGUI_H
