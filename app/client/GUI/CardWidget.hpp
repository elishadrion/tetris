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
#include "GameManager.hpp"

enum TypeCardWidget {
    EMPLACEMENT,
    PLAYER,
    MASK_CARD,
    CARD
};


class CardWidget : public QWidget{
    Q_OBJECT

    Card* _card;
    QLabel* _label;
    bool _selected;
    TypeCardWidget _typeCard;
    bool _interact;

    void toggleSelect();

public:
    CardWidget(TypeCardWidget type = CARD, bool = true);
    CardWidget(Card*);
    void resizeEvent(QResizeEvent*);
    void actualize();
    bool isSelect();
    void setSelect(bool);
    bool isEmplacement() {return _typeCard == TypeCardWidget::EMPLACEMENT;}
    unsigned getId() { return _card->getID(); }
    unsigned getPosition() { return _card->getPosition(); }
    void setPosition(unsigned pos) { _card->setPosition(pos); }
    bool isMonster() { return _card->isMonster(); }
    bool isCard(Card* card) { return card == _card; }
    bool isOnPosition(unsigned pos) { return _card->getPosition() == pos; }

signals:
    void selected(CardWidget*);
    void unSelected(CardWidget*);


protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;


};

#endif // CARDWIDGET_HPP
