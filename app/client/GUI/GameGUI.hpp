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

#include "client/GUI/DeckChooseGUI.hpp"

#include "common/Constants.hpp"



class GameGUI : public QMainWindow {
    Q_OBJECT

    QWidget *_centralWidget;
    QGridLayout *_gridlayout;
    DeckChooseGUI *_choosDeck;

    QPushButton *_nextTurnBouton;
    QLabel *_infoTour;

//    bool _turn;
//    unsigned _life;
//    unsigned _trash[DECK_SIZE];
//    unsigned _hand[MAX_HAND];
//    unsigned _deck[DECK_SIZE];
//    unsigned _posed[MAX_POSED_CARD];
//    unsigned _posedLife[MAX_POSED_CARD];
//    unsigned _ennemyLife;
//    unsigned _ennemyTrash;
//    unsigned _ennemyHand;
//    unsigned _ennemyDeck;
//    unsigned _ennemyPosed[MAX_POSED_CARD];
//    unsigned _ennemyPosedLife[MAX_POSED_CARD];

    void chooseDeck();


public:
    GameGUI();
    void callStartGame(std::string);

signals:
    void mustStartGame(std::string);

public slots:
    void makeStartGame(std::string);


};

#endif // GAME_H
