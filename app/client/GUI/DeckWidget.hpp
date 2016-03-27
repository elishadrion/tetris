#ifndef DECKWIDGET_HPP
#define DECKWIDGET_HPP

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTabWidget>
#include <QTabBar>
#include <string>

#include "PageWidget.hpp"
#include "CardWidget.hpp"

class DeckWidget : public QWidget{
    Q_OBJECT

    QTabWidget *_pages;
    QGridLayout *_grid;
    QLabel *_pageLabel;
    QPushButton *_next;
    QPushButton *_previous;

    PageWidget *tempPage;
    unsigned page;
    unsigned currentPage;

public:
    DeckWidget();

private slots:
    void nextPage();
    void previousPage();

};

#endif // DECKWIDGET_HPP
