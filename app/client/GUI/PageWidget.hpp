#ifndef PAGEWIDGET_HPP
#define PAGEWIDGET_HPP

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include "CardWidget.hpp"

//Simple layout pour faire une page de carte
class PageWidget : public QWidget{
    Q_OBJECT

    QGridLayout *_grid;

    int line;
    int column;

public:
    PageWidget();
    void addCard(CardWidget*);
};



#endif // PAGEWIDGET_HPP
