#include "GameGUI.hpp"


void GameGUI::chooseDeck() {
    _choosDeck = new DeckChooseGUI(this);
}


/**
 * Constructor
 *
 * @param pseudo from the adverse player
 */
GameGUI::GameGUI() : QMainWindow() {

    _centralWidget = new QWidget(this);
    setCentralWidget(_centralWidget);

    setWindowTitle("Jeux");

    _gridlayout = new QGridLayout(_centralWidget);

    QString strLabel;
    QLabel* label;

    // Cartes en main adverses face cachée
    for(unsigned i = 0; i < 7; ++i) {
        QHBoxLayout* carteAdv= new QHBoxLayout;
        strLabel = ("test: " + i);
        label = new QLabel(strLabel);
        label->setStyleSheet("background-color: red");
        carteAdv->addWidget(label);
        _gridlayout->addLayout(carteAdv, 0, 3+i);
        _gridlayout->setColumnStretch(3+i, 2);
    }


    // Cartes posée adverse
    for(unsigned i = 0; i < 7; ++i) {
        QHBoxLayout* advPlaceCarte = new QHBoxLayout;
        strLabel = ("test2: " + i);
        label = new QLabel(strLabel);
        label->setStyleSheet("background-color: lightblue");
        advPlaceCarte->addWidget(label);
        _gridlayout->addLayout(advPlaceCarte, 2, 3+i);
    }

    // Deck Adverse
    QHBoxLayout* advDeckAdv = new QHBoxLayout;
    strLabel = ("Deck A");
    label = new QLabel(strLabel);
    label->setStyleSheet("background-color: gray");
    advDeckAdv->addWidget(label);
    _gridlayout->addLayout(advDeckAdv, 2, 1);


    // Deck
    QHBoxLayout* advDeck = new QHBoxLayout;
    strLabel = ("Deck");
    label = new QLabel(strLabel);
    label->setStyleSheet("background-color: gray");
    advDeck->addWidget(label);
    _gridlayout->addLayout(advDeck, 4, 1);


    // Cartes en main
    for(unsigned i = 0; i < 7; ++i) {
        QHBoxLayout* carteInHand;
        carteInHand= new QHBoxLayout;
        strLabel = ("test2: " + i);
        label = new QLabel(strLabel);
        label->setStyleSheet("background-color: green");
        carteInHand->addWidget(label);
        _gridlayout->addLayout(carteInHand, 6, 3+i);
    }


    // Cartes posée
    for(unsigned i = 0; i < 7; ++i) {
        QHBoxLayout* placeCarte;
        placeCarte = new QHBoxLayout;
        strLabel = ("test2: " + i);
        label = new QLabel(strLabel);
        label->setStyleSheet("background-color: blue");
        placeCarte->addWidget(label);
        _gridlayout->addLayout(placeCarte, 4, 3+i);
    }


    // Passer
    _nextTurnBouton = new QPushButton("Passer\nson tour");
    _gridlayout->addWidget(_nextTurnBouton, 3, 11);
    _nextTurnBouton->hide();


    _infoTour = new QLabel("Ce n'est pas\nvotre tour", this);
    _gridlayout->addWidget(_infoTour, 3, 11);



    // Tchat
    ChatManagerGUI* tchat = new ChatManagerGUI(0);

    _gridlayout->addWidget(tchat, 0, 13, 6, 3);

    // PUB
    QHBoxLayout* pub = new QHBoxLayout;
    strLabel = ("PUB");
    label = new QLabel(strLabel);
    label->setStyleSheet("background-color: black; color: white;");
    pub->addWidget(label);
    _gridlayout->addLayout(pub, 6, 13, 1, 3);


    // colonne de gauche
    _gridlayout->setColumnStretch(0, 1);
    _gridlayout->setColumnStretch(1, 1);
    _gridlayout->setColumnStretch(2, 1);

    // colonne de droite
    _gridlayout->setColumnStretch(10, 1);
    _gridlayout->setColumnStretch(11, 1);
    _gridlayout->setColumnStretch(12, 1);

    _gridlayout->setColumnStretch(13, 2); // tchat
    _gridlayout->setColumnStretch(14, 2); // tchat
    _gridlayout->setColumnStretch(15, 2); // tchat


    // Ligne des cartes 1
    _gridlayout->setRowStretch(0, 3);
    _gridlayout->setRowStretch(1, 1);
    _gridlayout->setRowStretch(2, 3);
    _gridlayout->setRowStretch(3, 2); // bouton passer
    _gridlayout->setRowStretch(4, 3);
    _gridlayout->setRowStretch(5, 1);
    _gridlayout->setRowStretch(6, 3);


    show();
    this->showMaximized(); // set full screen

    connect(this, SIGNAL(nextPlayer(bool)), this, SLOT(viewPassButton(bool)));
    connect(this, SIGNAL(mustUpdateTurn(int)), this, SLOT(updateTurn(int)));


    chooseDeck();

}


void GameGUI::callChangeTurn(int nbrTurn, bool isTurn) {
    emit nextPlayer(isTurn);
    emit mustUpdateTurn(nbrTurn);
}

void GameGUI::viewPassButton(bool value) {
    if(value) {
        _nextTurnBouton->show();
        _infoTour->hide();
    } else {
        _nextTurnBouton->hide();
        _infoTour->show();
    }
}

void GameGUI::updateTurn(int nbrTurn) {
    // TO DO
}
