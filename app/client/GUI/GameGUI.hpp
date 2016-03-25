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

    CardWidget* _cardInHand[MAX_HAND];
    CardWidget* _advCardInHand[MAX_HAND];
    CardWidget* _cardBoard[MAX_POSED_CARD];
    CardWidget* _advCardBoard[MAX_POSED_CARD];

    CardWidget* _inHandSelect;


    void chooseDeck();

public:
    GameGUI();
    void callChangeTurn(int, bool);
    void callDrawCard(Card*);
    void callAdvDrawCard();

signals:
    void nextPlayer(bool);
    void mustUpdateTurn(int);
    void cardDraw(Card*);
    void advCardDraw();

private slots:
    void viewPassButton(bool);
    void updateTurn(int);
    void placeInHandCard(Card*);
    void placeAdvCard();
    void selectInHand(CardWidget*);
    void unSelectInHand();
    void selectEmplacement(CardWidget*);


};

#endif // GAME_H
