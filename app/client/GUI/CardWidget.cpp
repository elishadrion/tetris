#include "CardWidget.hpp"

/*
 * Actualize peut etre remplacé par un paintevent ou une autre fonctionnalité
 * plus adapté.
*/

CardWidget::CardWidget(Card* card) :
    QWidget(), _card(card),
    _energy(QString::fromStdString(UnsignedToString(card->getEnergyCost()))),
    _life(QString::fromStdString(UnsignedToString(card->getHP()))) {

    if(card->isMonster()) {
        _attack = QString::fromStdString(UnsignedToString(card->getAttack()));
    }

    _palette	= new QPalette();
    _pixmap		= new QPixmap(":/Images/CardToon.png");
    _paint = new QPainter(_pixmap);

    QFont font;
    font.setPixelSize(15);
    _paint->setFont(font);

    _palette->setBrush(QPalette::Background,QBrush(*_pixmap));
    setPalette(*_palette);

    _paint->drawText(24,228,_energy);
    _paint->drawText(77,228,_attack);
    _paint->drawText(121,228,_life);

}

void CardWidget::resizeEvent(QResizeEvent*){

   _palette->setBrush(QPalette::Background,QBrush(_pixmap->scaled(width(),height())));
   setPalette(*_palette);

}

std::string CardWidget::UnsignedToString(unsigned value) {
    std::ostringstream temp;
    temp<<value;
    return temp.str();
}

void CardWidget::actualize(){
    _energy = QString::fromStdString(UnsignedToString(_card->getEnergyCost()));
    _life = QString::fromStdString(UnsignedToString(_card->getHP()));
    if(_card->isMonster()) {
        _attack = QString::fromStdString(UnsignedToString(_card->getAttack()));
    }

    _pixmap		= new QPixmap(":/Images/CardToon.png");
    _paint = new QPainter(_pixmap);
    _paint->drawText(24,228,_energy);
    _paint->drawText(74,228,_attack);
    _paint->drawText(118,228,_life);

}

