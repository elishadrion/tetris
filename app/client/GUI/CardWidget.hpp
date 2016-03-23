#ifndef CARDWIDGET_HPP
#define CARDWIDGET_HPP

#include <string>
#include <QApplication>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QFont>
#include <QString>
#include <sstream>
#include <QLabel>

#include "Card.hpp"


class CardWidget : public QWidget{
    Q_OBJECT

    QString _energy;
    QString _attack;
    QString _life;

    Card* _card;
    QLabel* _label;

public:
    CardWidget(Card*);
    void resizeEvent(QResizeEvent*);
    std::string UnsignedToString(unsigned);
    void actualize();
};

#endif // CARDWIDGET_HPP
