#include "CardWidget.h"

/*
 * Actualize peut etre remplacé par un paintevent ou une autre fonctionnalité
 * plus adapté.
*/

CardWidget::CardWidget(unsigned energy,unsigned attack, unsigned hp) :
    QWidget(),
    _energy(QString::fromStdString(UnsignedToString(energy))),
    _attack(QString::fromStdString(UnsignedToString(attack))),
    _life(QString::fromStdString(UnsignedToString(hp))){

    _palette	= new QPalette();
    _pixmap		= new QPixmap("/home/dewit/Bureau/CardToon.png");
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

};

void CardWidget::setAttack(unsigned attack){
    _attack = QString::fromStdString(UnsignedToString(attack));
    actualize();
};

void CardWidget::setLife(unsigned hp){
    _life = QString::fromStdString(UnsignedToString(hp));
    actualize();
};

std::string CardWidget::UnsignedToString(unsigned value)
{
    std::ostringstream temp;
    temp<<value;
    return temp.str();
}

void CardWidget::actualize(){
    _pixmap		= new QPixmap("/home/dewit/Bureau/CardToon.png");
    _paint = new QPainter(_pixmap);
    _paint->drawText(24,228,_energy);
    _paint->drawText(74,228,_attack);
    _paint->drawText(118,228,_life);

}
