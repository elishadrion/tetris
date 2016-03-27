#ifndef COLLECTIONWIDGET_HPP
#define COLLECTIONWIDGET_HPP

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QTabWidget>
#include <string>
#include <QTabBar>
#include "CardWidget.hpp"
#include "PageWidget.hpp"
#include <QPushButton>
#include <QLabel>

class CollectionWidget : public QWidget{
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
    CollectionWidget();

private slots:
    void nextPage();
    void previousPage();
};

#endif // COLLECTIONWIDGET_HPP
