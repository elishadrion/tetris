#include "CardWidget.hpp"

/*
 * Actualize peut etre remplacé par un paintevent ou une autre fonctionnalité
 * plus adapté.
*/

CardWidget::CardWidget(Card* card) :
    QWidget(), _card(card),
    _energy(QString::fromStdString(UnsignedToString(card->getEnergyCost()))){

    if(card->isMonster()) {
        _attack = QString::fromStdString(UnsignedToString(card->getAttack()));
        _life = QString::fromStdString(UnsignedToString(card->getHP()));
    }

    _label = new QLabel(this);
    _label->setScaledContents(true);
    _label->setFixedSize(0,0);
    actualize();

}

void CardWidget::resizeEvent(QResizeEvent* event){

    QWidget::resizeEvent(event);
    QSize picSize = _label->pixmap()->size();
    picSize.scale(size(),Qt::KeepAspectRatio);
    _label->setFixedSize(picSize);

}

std::string CardWidget::UnsignedToString(unsigned value) {
    std::ostringstream temp;
    temp<<value;
    return temp.str();
}

void CardWidget::actualize(){
    _energy = QString::fromStdString(UnsignedToString(_card->getEnergyCost()));
    if(_card->isMonster()) {
        _attack = QString::fromStdString(UnsignedToString(_card->getAttack()));
        _life = QString::fromStdString(UnsignedToString(_card->getHP()));
    }

    QPixmap pic(":/Images/CardToon.png");
    QPainter paint(&pic);

    QFont font;
    font.setPixelSize(15);
    paint.setFont(font);

    paint.drawText(24,228,_energy);
    paint.drawText(77,228,_attack);
    paint.drawText(121,228,_life);

    _label->setPixmap(pic);

}

