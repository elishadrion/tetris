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
#include <QMessageBox>
#include <QTimer>

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

    QPushButton *_nextTurnBouton;
    QLabel *_nextTurnOff;
    // Game Information
    QVBoxLayout *_infoGame;
    QLabel* _nbrTurn;
    QLabel* _infoEnergy;
    QLabel* _infoHeal;
    QLabel* _infoAdvEnergy;
    QLabel* _infoAdvHeal;

    CardWidget* _cardInHand[MAX_HAND];
    CardWidget* _advCardInHand[MAX_HAND];
    CardWidget* _cardBoard[MAX_POSED_CARD];
    CardWidget* _advCardBoard[MAX_POSED_CARD];
    CardWidget* _spellCardWidget;
    CardWidget* _advSpellCardWidget;

    CardWidget* _inHandSelect;
    CardWidget* _onBoardSelect;
    CardWidget* _spellCard;
    CardWidget* _advSpellCard;
    QTimer* _timeSpell;
    QTimer* _timeAdvSpell;


    void addEmplacement(int, bool);
    void placeMonsterCardOnBoard(CardWidget*);
    void placeSpellCardOnBoard();
    void placeAdvSpellOnBoard(CardWidget*);
    void removeInHandCard();
    void removeAdvInHandCard();
    void updatePlayerInfo();
    void updateAdvPlayerInfo();
    void displayError(int);
    void displayError(std::string);

    // UTILS
    int getIndexHand(CardWidget*);
    int getIndexBoard(CardWidget*);

    // ACTION
    void placeAndAttack(CardWidget*);
    void attack(CardWidget*);

public:
    GameGUI();
    void callChangeTurn();
    void callDrawCard(Card*);
    void callAdvDrawCard();
    void callPlaceCard(Card*);
    void callAdvPlaceCard(Card*);
    void callPlaceAdvSpell(Card*, Card*);
    void callPlaceAdvCardAttack(Card*, Card*);
    void callDeadCard(Card*, bool);

signals:
    void nextPlayer();
    void mustUpdateTurn();
    void cardDraw(Card*);
    void advCardDraw();
    void mustPlaceCard(Card*);
    void mustPlaceAdvCard(Card*);
    void mustPlaceAdvSpell(Card*, Card*);
    void mustPlaceAdvCardAttack(Card*, Card*);
    void mustDeadCard(Card*, bool);

private slots:
    void viewPassButton();
    void updateTurn();
    void placeInHandCard(Card*);
    void drawAdvCard();
    void selectCard(CardWidget*);
    void unSelectCard(CardWidget*);
    void selectEmplacement(CardWidget*);
    void selectAdvCard(CardWidget*);
    void selectSpellEmplacement(CardWidget*);
    void nextTurn();
    void placeAdvCard(Card*);
    void removeSpell();
    void removeAdvSpell();
    void deadCard(Card*, bool);
    void placeAdvSpell(Card*, Card*);
    void placeAdvCardAttack(Card*, Card*);


};

#endif // GAME_H
