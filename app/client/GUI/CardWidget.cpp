#include "CardWidget.hpp"

/*
 * Actualize peut etre remplacé par un paintevent ou une autre fonctionnalité
 * plus adapté.
*/

CardWidget::CardWidget(bool emplacement, bool interact):
    QWidget(), _emplacement(emplacement), _card(nullptr),
    _interact(interact) {

    _label = new QLabel(this);
    _label->setScaledContents(true);
    _label->setFixedSize(0,0);
    actualize();
}


CardWidget::CardWidget(Card* card): QWidget(), _card(card),
    _emplacement(false), _interact(true) {

    _label = new QLabel(this);
    _label->setScaledContents(true);
    _label->setFixedSize(0,0);
    actualize();
}

/**
 * Change card selection (select if unselect and vice versa
 */
void CardWidget::toggleSelect() {
    setSelect(!_selected);
    if(_selected) {
        WizardLogger::info("toggle: new = true");
        emit selected(this);
    } else {
        WizardLogger::info("toggle: new = false");
        emit unSelected(this);
    }
}

/**
 * Call when the widget is resize
 *
 * @param event
 */
void CardWidget::resizeEvent(QResizeEvent* event){
    QWidget::resizeEvent(event);
    if(!_emplacement) {
        QSize picSize = _label->pixmap()->size();
        picSize.scale(size(),Qt::KeepAspectRatio);
        _label->setFixedSize(picSize);
    } else {
        QSize size = this->size();
        _label->setFixedSize(size);
    }
}


void CardWidget::actualize(){
    if(_card != nullptr) { // Define card
        QString energy = QString::fromStdString(std::to_string(_card->getEnergyCost()));
        QString attack = "";
        QString life = "";
        QString nom = QString::fromStdString(_card->getName());
        if(_card->isMonster()) {
            attack = QString::fromStdString(std::to_string(_card->getAttack()));
            life = QString::fromStdString(std::to_string(_card->getHP()));
        }

        QPixmap pic(":/Images/CardToon.png");
        QPainter paint(&pic);

        QFont font;
        font.setPixelSize(15);
        paint.setFont(font);

        paint.drawText(24,228,energy);
        paint.drawText(77,228,attack);
        paint.drawText(121,228,life);
        paint.drawText(24,170,nom);

        _label->setPixmap(pic);

    } else if(_emplacement) { // emplacement
        _label->setStyleSheet("background-color: rgba(109, 109, 109, 0.37)");

    } else { // masked card
        QPixmap pic(":/Images/CardMasked.png");
        _label->setPixmap(pic);

    }
}

/**
 * View if this card is select
 * @return True if select
 */
bool CardWidget::isSelect() {
    return _selected;
}

/**
 * Select or not a card
 *
 * @param value True to select
 */
void CardWidget::setSelect(bool value) {
    _selected = value;
    if(value) {
        this->setStyleSheet("border: 2px solid red;");
    } else {
        this->setStyleSheet("border: 0px solid black;");
    }
}

void CardWidget::mousePressEvent(QMouseEvent *event) {
    if(_interact) {
        toggleSelect();
    }
}


////// Right clic open menu //////
//void CardWidget::showContextMenu(const QPoint& pos) {
//    QPoint globalPos = this->mapToGlobal(pos);
//    QMenu myMenu;
//    myMenu.addAction("Défausser");
//    myMenu.addAction("Attaquer");
//    // ...

//    QAction* selectedItem = myMenu.exec(globalPos);
//    if (selectedItem) {
//        // something was chosen, do stuff
//    } else {
//        // nothing was chosen
//    }
//}


