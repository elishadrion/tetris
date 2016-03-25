#include "GameGUI.hpp"


void GameGUI::chooseDeck() {
    _choosDeck = new DeckChooseGUI(this);
}


/**
 * Constructor
 *
 * @param pseudo from the adverse player
 */
GameGUI::GameGUI() : QMainWindow(), _inHandSelect(nullptr) {

    // Init variable
    for(int i = 0; i < MAX_HAND; ++i) {
        _cardInHand[i] = nullptr;
        _advCardInHand[i] = nullptr;
    }

    // Construct interface
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


    // Emplacement
    for(int i = 0; i < MAX_POSED_CARD; ++i) {
        CardWidget* advCardWidget = new CardWidget(true, false);
        _advCardBoard[i] = advCardWidget;
        _gridlayout->addWidget(advCardWidget, 3, 3+i);

        CardWidget* cardWidget = new CardWidget(true);
        _cardBoard[i] = cardWidget;
        _gridlayout->addWidget(cardWidget, 5, 3+i);

        connect(cardWidget, SIGNAL(selected(CardWidget*)), this, SLOT(selectEmplacement(CardWidget*)));

    }

    // Emplacement Carte sort
    CardWidget* spellCardWidget = new CardWidget(true, false);
    _gridlayout->addWidget(spellCardWidget, 6, 2);

    CardWidget* advSpellCardWidget = new CardWidget(true, false);
    _gridlayout->addWidget(advSpellCardWidget, 2, 2);


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
    _gridlayout->setRowStretch(1, 4); // adverse hand
    _gridlayout->setRowStretch(2, 4); // adverse sort
    _gridlayout->setRowStretch(3, 5); // adverse place
    _gridlayout->setRowStretch(4, 1); // bouton passer
    _gridlayout->setRowStretch(5, 5); // Card placed
    _gridlayout->setRowStretch(6, 4); // Sort + espace
    _gridlayout->setRowStretch(7, 5); // In Hand


    show();
    this->showMaximized(); // set full screen

    connect(this, SIGNAL(nextPlayer()), this, SLOT(viewPassButton()));
    connect(this, SIGNAL(mustUpdateTurn()), this, SLOT(updateTurn()));
    connect(this, SIGNAL(cardDraw(Card*)), this, SLOT(placeInHandCard(Card*)));
    connect(this, SIGNAL(advCardDraw()), this, SLOT(drawAdvCard()));
    connect(_nextTurnBouton, SIGNAL(clicked()), this, SLOT(nextTurn()));
    connect(this, SIGNAL(mustPlaceAdvCard(Card*)), this, SLOT(placeAdvCard(Card*)));


    chooseDeck();
}

/**
 * Call when the turn change (2 emit)
 *
 * @param nbrTurn number of turn
 * @param isTurn is the player turn
 */
void GameGUI::callChangeTurn() {
    emit nextPlayer();
    emit mustUpdateTurn();
}

/**
 * Call when a player draw a card (emit)
 *
 * @param card the new card
 */
void GameGUI::callDrawCard(Card* card) {
    emit cardDraw(card);
}

/**
 * Call when adverse player draw a card
 */
void GameGUI::callAdvDrawCard() {
    emit advCardDraw();
}

void GameGUI::callPlaceCard(Card * card) {} // TO DO

/**
 * Call when adverse player place a card
 *
 * @param card new card
 */
void GameGUI::callAdvPlaceCard(Card* card) {
    emit mustPlaceAdvCard(card);
}


/**
 * Change the view of the button "pass"
 *
 * @param value true if visible
 */
void GameGUI::viewPassButton() {
    if(GameManager::getInstance()->isTurn()) {
        _nextTurnBouton->show();
        _nextTurnOff->hide();
    } else {
        _nextTurnBouton->hide();
        _nextTurnOff->show();
    }
}

/**
 * Update the number of turn in the info label
 *
 * @param nbrTurn number of turn
 */
void GameGUI::updateTurn() {
    _nbrTurn->setText(QString(std::to_string(
                    GameManager::getInstance()->getNbrTurn()).c_str()));
}

/**
 * Call when the player reciev a new card in hand
 *
 * @param card the ne card
 */
void GameGUI::placeInHandCard(Card* card) {
    int i = 0;

    while(i < MAX_HAND && (_cardInHand[i] != nullptr)) {
        ++i;
    }

    if(i != MAX_HAND) {
        CardWidget* cardWidget = new CardWidget(card);
        _cardInHand[i] = cardWidget;
        connect(cardWidget, SIGNAL(selected(CardWidget*)), this, SLOT(selectInHand(CardWidget*)));
        connect(cardWidget, SIGNAL(unSelected(CardWidget*)), this, SLOT(unSelectInHand()));
        _gridlayout->addWidget(cardWidget, 7, 3+i);
    } else {
        WizardLogger::error("Impossible de posée la carte (plus assez de place)");
    }
}

void GameGUI::drawAdvCard() {
    int i = 0;
    while(i < MAX_HAND && (_advCardInHand[i] != nullptr)) {
        ++i;
    }

    if(i != MAX_HAND) {
        CardWidget* cardWidget = new CardWidget(false);
        _advCardInHand[i] = cardWidget;
        _gridlayout->addWidget(cardWidget, 1, 3+i);
    } else {
        WizardLogger::error("Impossible de posée une carte adverse (plus assez de place)");
    }
}

void GameGUI::selectInHand(CardWidget* cardWidget) {
    if(_inHandSelect != nullptr) {
        _inHandSelect->setSelect(false);
    }
    _inHandSelect = cardWidget;
}

void GameGUI::unSelectInHand() {
    _inHandSelect = nullptr;
}


void GameGUI::selectEmplacement(CardWidget* cardWidget) {
    if(_inHandSelect != nullptr) {
        PacketManager::sendPlaceCard(_inHandSelect->getId());
        _inHandSelect->setSelect(false);
        _inHandSelect = nullptr;
        cardWidget->setSelect(false);
    } else {
        cardWidget->setSelect(false);
    }
}

void GameGUI::nextTurn() {
    PacketManager::endTurn();
}

void GameGUI::placeCard(Card* card) {
    for(int i = 0; i < MAX_HAND; ++i) {
        //_cardInHand[i]->isEquivalent(card);
    }
}


void GameGUI::placeAdvCard(Card* card) {
    delete _advCardInHand[0];

    int i = 0;
    while(i < MAX_POSED_CARD && !_advCardBoard[i]->isEmplacement()) {
        ++i;
    }

    delete _advCardBoard[i];
    CardWidget* cardWidget = new CardWidget(card);
    _advCardBoard[i] = cardWidget;
    _gridlayout->addWidget(cardWidget, 3, 3+i);
}
