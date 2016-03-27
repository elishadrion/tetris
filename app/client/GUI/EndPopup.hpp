#ifndef ENDPOPUP_H
#define ENDPOPUP_H

#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QGridLayout>
#include <QButtonGroup>
#include <QPushButton>

#include "client/Player.hpp"
#include "GameManager.hpp"


class EndPopup;
class GameGUI;
#include "GameGUI.hpp"


class EndPopup : public QMainWindow {
    Q_OBJECT

    GameGUI* _gameGui;
    QWidget *_centralWidget;
    QListWidget* _listDeck;
    QGridLayout* _gridlayout;

public:
    EndPopup(QString, GameGUI*);

private slots:
    void valideQuit();


};




#endif // ENDPOPUP_H
