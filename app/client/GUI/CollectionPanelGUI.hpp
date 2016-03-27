#ifndef COLLECTIONPANELGUI_HPP
#define COLLECTIONPANELGUI_HPP

#include <string>
#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QTextBrowser>
#include <QLabel>
#include <QCloseEvent>
#include <vector>
#include <QString>

#include "CollectionWidget.hpp"
#include "DeckWidget.hpp"
#include "client/Player.hpp"

class CollectionPanelGUI;
#include "MenuPanelGUI.hpp"

class CollectionPanelGUI : public QMainWindow{
    Q_OBJECT

    QGridLayout *_grid;
    CollectionWidget *_collectionWidget;
    QTabWidget *_tab;
    QTextBrowser *_newDeck;
    QLabel *_labelNewDeck;
    QLabel *_nCardsAdd;
    QPushButton *_addDeck;

    std::vector<std::string> _decks;
    unsigned _nCards;
    MenuPanelGUI *_menu;

    void closeEvent(QCloseEvent*);

public:
    CollectionPanelGUI(MenuPanelGUI*);

private slots:
    void addDeck();
};


#endif // COLLECTIONPANELGUI_HPP
