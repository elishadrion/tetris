#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QTextEdit>
#include <QTabWidget>
#include <QTabBar>
#include <QGroupBox>
#include <QMainWindow>

#include <vector>

#include "DeckChooseGUI.hpp"
#include "ChatManagerGUI.hpp"
#include "GameManager.hpp"
#include "CardWidget.hpp"

#include "common/Constants.hpp"



class GameGUI : public QMainWindow {
    Q_OBJECT

    QWidget *_centralWidget;
    QGridLayout *_gridlayout;
    DeckChooseGUI *_choosDeck;

    QPushButton *_nextTurnBouton;
    QLabel *_nextTurnOff;
    // Game Information
    QVBoxLayout *_infoGame;
    QLabel* _nbrTurn;

    void chooseDeck();


public:
    GameGUI();
    void callChangeTurn(int, bool);
    void callDrawCard(Card*);

signals:
    void nextPlayer(bool);
    void mustUpdateTurn(int);
    void cardDraw(Card*);

private slots:
    void viewPassButton(bool);
    void updateTurn(int);
    void addCardHand(Card*);


};

#endif // GAME_H
