#include "CardWidget.hpp"

/*
 * Actualize peut etre remplacé par un paintevent ou une autre fonctionnalité
 * plus adapté.
*/

CardWidget::CardWidget(TypeCardWidget type, bool interact):
    QWidget(), _card(nullptr), _interact(interact), _typeCard(type),
    _selected(false){

    _label = new QLabel(this);
    _label->setScaledContents(true);
    _label->setFixedSize(0,0);
    actualize();
}


CardWidget::CardWidget(Card* card): QWidget(), _card(card),
    _typeCard(TypeCardWidget::CARD), _interact(true), _selected(false) {

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
    if(_typeCard != TypeCardWidget::EMPLACEMENT) {
        QSize picSize = _label->pixmap()->size();
        picSize.scale(size(),Qt::KeepAspectRatio);
        _label->setFixedSize(picSize);
    } else {
        QSize size = this->size();
        _label->setFixedSize(size);
    }
}

void CardWidget::actualize() {
    if(_card != nullptr && _typeCard == TypeCardWidget::CARD) { // Define card

        QString energy = QString::fromStdString(std::to_string(_card->getEnergyCost()));
        QString attack = "";
        QString life = "";
        if(_card->isMonster()) {
            attack = QString::fromStdString(std::to_string(_card->getAttack()));
            life = QString::fromStdString(std::to_string(_card->getHP()));
        }

        std::string nomImage = "./client/Images/Cards/";
        nomImage += std::to_string(_card->getID());
        nomImage += ".png";
        QPixmap pic(nomImage.c_str());
        QPainter paint(&pic);

        QFont font;
        font.setPixelSize(50);
        paint.setFont(font);
        paint.setPen(QColor(255, 255, 255));
        // x, y
        paint.drawText(50,70,energy);
        paint.drawText(50,500,attack);
        paint.drawText(340,500,life);

        _label->setPixmap(pic);

    } else if(_typeCard == TypeCardWidget::PLAYER) {
        QPixmap pic(":/Images/adverse.png");
        _label->setPixmap(pic);

    } else if(_typeCard == TypeCardWidget::EMPLACEMENT) { // emplacement
        _label->setStyleSheet("background-color: rgba(109, 109, 109, 0.25);"
                              "border-radius: 15px;");

    } else { // masked card
        QPixmap pic(":/Images/CardMasked.png");

        // View nomber Card if deck
        if(_typeCard == TypeCardWidget::DECK ||
                _typeCard == TypeCardWidget::ADV_DECK) {

            QPainter paint(&pic);
            QFont font;
            font.setPixelSize(50);
            paint.setFont(font);
            paint.setPen(QColor(255, 255, 255));

            QString nbrCard;
            if(_typeCard == TypeCardWidget::DECK) {
                nbrCard = QString::fromStdString(
                        std::to_string(GameManager::getInstance()->getNbrDeck()));
            } else {
                nbrCard = QString::fromStdString(
                        std::to_string(GameManager::getInstance()->getNbrAdvDeck()));
            }
            paint.drawText(50,500,nbrCard);
        }

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
    if(_interact && GameManager::getInstance()->isTurn()) {
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


