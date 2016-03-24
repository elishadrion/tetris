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

    // Deck Adverse
    QHBoxLayout* advDeckAdv = new QHBoxLayout;
    label = new QLabel("DeckA");
    label->setStyleSheet("background-color: gray");
    advDeckAdv->addWidget(label);
    _gridlayout->addLayout(advDeckAdv, 3, 1);


    // Deck
    QHBoxLayout* advDeck = new QHBoxLayout;
    label = new QLabel("Deck");
    label->setStyleSheet("background-color: gray");
    advDeck->addWidget(label);
    _gridlayout->addLayout(advDeck, 5, 1);


    // Passer
    _nextTurnBouton = new QPushButton("Passer\nson tour");
    _gridlayout->addWidget(_nextTurnBouton, 4, 11);
    _nextTurnBouton->hide();

    _nextTurnOff = new QLabel("Ce n'est pas\nvotre tour", this);
    _gridlayout->addWidget(_nextTurnOff, 4, 11);

    //////// INFO GAME ////////
    _infoGame = new QVBoxLayout;
    // Adverse
    QHBoxLayout* infoAdverse = new QHBoxLayout;
    QLabel *labelAdversePlayer = new QLabel(QString::fromStdString("Joueur adverse: "));
    infoAdverse->addWidget(labelAdversePlayer);
    QLabel *adversePlayer = new QLabel(QString(GameManager::getInstance()->getEnnemy().c_str()));
    infoAdverse->addWidget(adversePlayer);

    _infoGame->addLayout(infoAdverse);

    // Turn
    QHBoxLayout* infoTurn = new QHBoxLayout;
    QLabel* labelNbrTurn = new QLabel("Nombre de tour: ");
    infoTurn->addWidget(labelNbrTurn);
    _nbrTurn = new QLabel(QString(std::to_string(GameManager::getInstance()->getNbrTurn()).c_str()));
    infoTurn->addWidget(_nbrTurn);

    _infoGame->addLayout(infoTurn);

    _gridlayout->addLayout(_infoGame, 0, 13);



    // Tchat
    _gridlayout->addWidget(ChatManagerGUI::getInstance(), 1, 13, 6, 1);


    // PUB
    QHBoxLayout* pub = new QHBoxLayout;
    strLabel = ("PUB");
    label = new QLabel(strLabel);
    label->setStyleSheet("background-color: black; color: white;");
    pub->addWidget(label);
    _gridlayout->addLayout(pub, 7, 13);


    // colonne de gauche
    _gridlayout->setColumnStretch(0, 1); // Espace
    _gridlayout->setColumnStretch(1, 2); // Deck
    _gridlayout->setColumnStretch(2, 2); // Sort

    _gridlayout->setColumnStretch(3, 2); // Card 1
    _gridlayout->setColumnStretch(4, 2); // Card 2
    _gridlayout->setColumnStretch(5, 2); // Card 3
    _gridlayout->setColumnStretch(6, 2); // Card 4
    _gridlayout->setColumnStretch(7, 2); // Card 5
    _gridlayout->setColumnStretch(8, 2); // Card 6
    _gridlayout->setColumnStretch(9, 2); // Card 7

    // colonne de droite
    _gridlayout->setColumnStretch(10, 1); // Espace
    _gridlayout->setColumnStretch(11, 2); // Next Turn
    _gridlayout->setColumnStretch(12, 1); // Espace

    _gridlayout->setColumnStretch(13, 6); // tchat


    // Ligne des cartes 1
    _gridlayout->setRowStretch(0, 2); // adverse player
    _gridlayout->setRowStretch(1, 3); // adverse hand
    _gridlayout->setRowStretch(2, 3); // adverse sort
    _gridlayout->setRowStretch(3, 5); // adverse place
    _gridlayout->setRowStretch(4, 1); // bouton passer
    _gridlayout->setRowStretch(5, 5); // Card placed
    _gridlayout->setRowStretch(6, 4); // Sort + espace
    _gridlayout->setRowStretch(7, 5); // In Hand


    show();
    this->showMaximized(); // set full screen

    connect(this, SIGNAL(nextPlayer(bool)), this, SLOT(viewPassButton(bool)));
    connect(this, SIGNAL(mustUpdateTurn(int)), this, SLOT(updateTurn(int)));
    connect(this, SIGNAL(cardDraw(Card*)), this, SLOT(addCardHand(Card*)));


    chooseDeck();
}


void GameGUI::callChangeTurn(int nbrTurn, bool isTurn) {
    emit nextPlayer(isTurn);
    emit mustUpdateTurn(nbrTurn);
}

void GameGUI::callDrawCard(Card* card) {
    emit cardDraw(card);
}

void GameGUI::viewPassButton(bool value) {
    if(value) {
        _nextTurnBouton->show();
        _nextTurnOff->hide();
    } else {
        _nextTurnBouton->hide();
        _nextTurnOff->show();
    }
}

void GameGUI::updateTurn(int nbrTurn) {
    _nbrTurn->setText(QString(std::to_string(nbrTurn).c_str()));
}

void GameGUI::addCardHand(Card* card) {
    WizardLogger::info("GUI: addCard");
    bool find;
    int i = 0;

    while(i < MAX_HAND && !find) {
        find = (_gridlayout->itemAtPosition(7, 3+i) == 0);
        ++i;
    }

    if(find) {
        _gridlayout->addWidget(new CardWidget(card), 7, 2+i);
    } else {
        WizardLogger::error("Impossible de posée la carte (plus assez de place)");
    }
}
