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

#include "client/Player.hpp"
#include "client/CacheManager.hpp"

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
    unsigned* _collection;


public:
    CollectionWidget();

private slots:
    void nextPage();
    void previousPage();
};

#endif // COLLECTIONWIDGET_HPP
