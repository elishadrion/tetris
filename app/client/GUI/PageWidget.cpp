#include "pageWidget.hpp"

PageWidget::PageWidget() : QWidget(){

    line = 0;
    column = 0;

    _grid = new QGridLayout(this);

}

//Ajoute une carte de maniere a ce qu'il y en ait que 5 par ligne
void PageWidget::addCard(CardWidget *card){
    if (column == 5){line+=1;column=0;}
    _grid->addWidget(card,line,column);
    column+=1;
}
