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
#include <QMenu>

#include "Card.hpp"


class CardWidget : public QWidget{
    Q_OBJECT

    Card* _card;
    QLabel* _label;
    bool _selected;
    bool _emplacement;
    bool _interact;

    void toggleSelect();

public:
    CardWidget(bool = true, bool = true);
    CardWidget(Card*);
    void resizeEvent(QResizeEvent*);
    void actualize();
    bool isSelect();
    void setSelect(bool);

signals:
    void selected(CardWidget*);
    void unSelected(CardWidget*);


protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;


};

#endif // CARDWIDGET_HPP
