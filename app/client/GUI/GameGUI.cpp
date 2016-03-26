#include "GameGUI.hpp"


/**
 * Constructor
 *
 * @param pseudo from the adverse player
 */
GameGUI::GameGUI() : QMainWindow(), _inHandSelect(nullptr),
    _timeSpell(nullptr), _timeAdvSpell(nullptr) {

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
        addEmplacement(i, true);
        addEmplacement(i, false);

    }

    // Emplacement Carte sort
    _spellCardWidget = new CardWidget(true, false);
    _gridlayout->addWidget(_spellCardWidget, 6, 2);

    _advSpellCardWidget = new CardWidget(true, false);
    _gridlayout->addWidget(_advSpellCardWidget, 2, 2);


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
    connect(this, SIGNAL(mustPlaceAdvSpell(Card*, Card*)), this, SLOT(placeAdvSpell(Card*,Card*)));
    connect(this, SIGNAL(mustDeadCard(Card*, bool)), this, SLOT(deadCard(Card*, bool)));

    // pop-up to choose deck
    new DeckChooseGUI(this);
}



/**
 * Add an emplacement to the board
 *
 * @param index number of the emplacement (left = 0)
 * @param adverse True if adverse emplacement
 */
void GameGUI::addEmplacement(int index, bool adverse) {
    CardWidget* cardWidget = new CardWidget(true, !adverse);
    _gridlayout->addWidget(cardWidget, adverse ? 3 : 5, 3+index);

    if(adverse) {
        _advCardBoard[index] = cardWidget;
    } else {
        _cardBoard[index] = cardWidget;
        connect(cardWidget, SIGNAL(selected(CardWidget*)), this, SLOT(selectEmplacement(CardWidget*)));
    }
}

/**
 * Place the selected card on the board
 *
 * @param emplacement of the card who must be placed
 */
void GameGUI::placeMonsterCardOnBoard(CardWidget* emplacement) {
    if(_inHandSelect != nullptr) {
        // Remove card from hand
        removeInHandCard();

        // Get emplacement
        int nbrEmplacement = 0;
        while(nbrEmplacement < MAX_POSED_CARD &&
              emplacement != _cardBoard[nbrEmplacement]) {
            ++nbrEmplacement;
        }
        // Get coordonnee
        int index = _gridlayout->indexOf(emplacement);
        emplacement->close(); // delete emplacement
        if(index != -1) { // get position and place card
            int row, col, col_span, row_span;
            _gridlayout->getItemPosition(index, &row, &col, &col_span, &row_span);
            _gridlayout->addWidget(_inHandSelect, row, col, col_span, row_span);
        }

        _cardBoard[nbrEmplacement] = _inHandSelect;
        _inHandSelect->setSelect(false);
        _inHandSelect = nullptr;

    } else {
        WizardLogger::warning("Aucune carte sélectionnée");
    }
}

void GameGUI::placeSpellCardOnBoard() {
    if(_inHandSelect != nullptr) {
        // Remove card from hand
        removeInHandCard();

        if(_timeSpell != nullptr) {
            _timeSpell->stop();
            removeSpell();
        }

        _spellCardWidget->hide();
        _spellCard = _inHandSelect;
        _gridlayout->addWidget(_spellCard, 6, 2);

        _timeSpell = new QTimer(this);
        connect(_timeSpell, SIGNAL(timeout()), this, SLOT(removeSpell()));
        _timeSpell->start(2000);
        _timeSpell->setSingleShot(true);

        _inHandSelect->setSelect(false);
        _inHandSelect = nullptr;
    }
}

void GameGUI::placeAdvSpellOnBoard(CardWidget* cardWidget) {
    if(cardWidget != nullptr) {
        removeAdvInHandCard();

        if(_timeAdvSpell != nullptr) {
            _timeAdvSpell->stop();
            removeAdvSpell();
        }

        _advSpellCardWidget->hide();
        _advSpellCard = cardWidget;
        _gridlayout->addWidget(_advSpellCard, 2, 2);

        _timeAdvSpell = new QTimer(this);
        connect(_timeAdvSpell, SIGNAL(timeout()), this, SLOT(removeAdvSpell()));
        _timeAdvSpell->start(2000);
        _timeAdvSpell->setSingleShot(true);
    }
}


/**
 * Remove card which is select from hand
 */
void GameGUI::removeInHandCard() {
    int nbrHand = 0;
    while(nbrHand < MAX_HAND &&
          _inHandSelect != _cardInHand[nbrHand]) {
        ++nbrHand;
    }
    _gridlayout->removeWidget(_cardInHand[nbrHand]); // remove widget
    _cardInHand[nbrHand] = nullptr; // remove from hand
}

/**
 * Remove one card from the adverse hand
 */
void GameGUI::removeAdvInHandCard() {
    int nbrHand = 0;
    CardWidget* select = nullptr;
    while(nbrHand < MAX_HAND && select == nullptr) {
        if(_advCardInHand[nbrHand] != nullptr) {
            select = _advCardInHand[nbrHand];
        } else {
            ++nbrHand;
        }
    }
    if(select != nullptr) {
        select->hide();
        select->close();
        _advCardInHand[nbrHand] = nullptr;
    } else {
        WizardLogger::warning("Impossible de supprimer une carte dans la main adverse");
    }
}


void GameGUI::displayError(int errorId) {
    displayError(ErrorAPI::errorToStr(errorId));
}

void GameGUI::displayError(std::string msg) {
    QMessageBox messageBox;
    messageBox.critical(this, QString::fromStdString("Erreur"),
                        QString::fromStdString(msg));
}



/**
 * Call when the turn change (2 emit)
 *
 * @param nbrTurn number of turn
 * @param isTurn is the player turn
 */
void GameGUI::callChangeTurn() {
    if(_inHandSelect != nullptr) {
        _inHandSelect->setSelect(false);
        _inHandSelect = nullptr;
    }

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

/**
 * Call when adverse player place a card
 *
 * @param card new card
 */
void GameGUI::callAdvPlaceCard(Card* card) {
    emit mustPlaceAdvCard(card);
}

void GameGUI::callPlaceAdvSpell(Card* card, Card* target) {
    emit mustPlaceAdvSpell(card, target);
}


void GameGUI::callDeadCard(Card* card, bool adv) {
    emit mustDeadCard(card, adv);
}


// ================ SLOTS =======================

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

/**
 * Call when adverse player draw a new card
 */
void GameGUI::drawAdvCard() {
    int i = 0;
    while(i < MAX_HAND && (_advCardInHand[i] != nullptr)) {
        ++i;
    }

    if(i != MAX_HAND) {
        CardWidget* cardWidget = new CardWidget(false, false);
        _advCardInHand[i] = cardWidget;
        _gridlayout->addWidget(cardWidget, 1, 3+i);
    } else {
        WizardLogger::error("Impossible de posée une carte adverse (plus assez de place)");
    }
}

/**
 * Call when player select card in hand
 *
 * @param cardWidget witch card is select
 */
void GameGUI::selectInHand(CardWidget* cardWidget) {
    if(_inHandSelect != nullptr) {
        _inHandSelect->setSelect(false);
    }
    _inHandSelect = cardWidget;
    WizardLogger::info("Selection de la carte: " + std::to_string(cardWidget->getId()));
}

/**
 * Call when player unselect card
 */
void GameGUI::unSelectInHand() {
    _inHandSelect = nullptr;
}


/**
 * Call when we select an emplacement
 *
 * @param cardWidget emplacement selected
 */
void GameGUI::selectEmplacement(CardWidget* cardWidget) {
    cardWidget->setSelect(false);

    if(_inHandSelect != nullptr) {
        if(_inHandSelect->isMonster()) {
            /* Lock */
            pthread_mutex_lock(&wizardDisplay->packetStackMutex);

            // Packet manager
            WizardLogger::info("Placement de la carte: "+ std::to_string(_inHandSelect->getId()));
            PacketManager::sendPlaceCard(_inHandSelect->getId());

            /* Wait for result */
            pthread_cond_wait(&wizardDisplay->packetStackCond, &wizardDisplay->packetStackMutex);

            /* Check result */
            if (wizardDisplay->packetErrorStack.empty()) {
                WizardLogger::info("Pose la carte");

                placeMonsterCardOnBoard(cardWidget);

            } else {
                int error = reinterpret_cast<int>(wizardDisplay->packetErrorStack.back());
                wizardDisplay->packetErrorStack.pop_back();
                displayError(error);
            }

            /* Unlock */
            pthread_mutex_unlock(&wizardDisplay->packetStackMutex);
        } else {
            displayError("Vous devez sélectionner une cible (carte sort)");
        }
    }
}

void GameGUI::selectAdvCard(CardWidget * cardWidget) {
    cardWidget->setSelect(false);

    // If card in hand select and is a spell card
    if(_inHandSelect != nullptr && !_inHandSelect->isMonster()) {

        /* Lock */
        pthread_mutex_lock(&wizardDisplay->packetStackMutex);

        // Packet manager
        WizardLogger::info("Placement & attack sort: "+ std::to_string(_inHandSelect->getId()));
        PacketManager::sendPlaceCardAttack(_inHandSelect->getId(), cardWidget->getPosition());

        /* Wait for result */
        pthread_cond_wait(&wizardDisplay->packetStackCond, &wizardDisplay->packetStackMutex);

        /* Check result */
        if (wizardDisplay->packetErrorStack.empty()) {
            WizardLogger::info("Pose la carte & attack");

            placeSpellCardOnBoard();
            cardWidget->actualize(); // update heal of this card

        } else {
            int error = reinterpret_cast<int>(wizardDisplay->packetErrorStack.back());
            wizardDisplay->packetErrorStack.pop_back();
            displayError(error);
        }

        /* Unlock */
        pthread_mutex_unlock(&wizardDisplay->packetStackMutex);
    }

}


/**
 * Call when the player will change turn
 */
void GameGUI::nextTurn() {
    PacketManager::endTurn();
}


/**
 * Call when adverse place a card
 *
 * @param card the card which must be placed
 */
void GameGUI::placeAdvCard(Card* card) {
    removeAdvInHandCard();


    int i = 0;
    while(i < MAX_POSED_CARD && !_advCardBoard[i]->isEmplacement()) {
        ++i;
    }

    if(i != MAX_POSED_CARD) {
        _advCardBoard[i]->close();
        CardWidget* cardWidget = new CardWidget(card);
        _advCardBoard[i] = cardWidget;
        _gridlayout->addWidget(cardWidget, 3, 3+i);

        connect(cardWidget, SIGNAL(selected(CardWidget*)), this, SLOT(selectAdvCard(CardWidget*)));

    } else {
        WizardLogger::warning("Impossible de placer la carte adverse (plus de place)");
    }
}

void GameGUI::removeSpell() {
    _timeSpell = nullptr;
    if(_spellCard != nullptr) {
        _spellCard->close();
    }
    _spellCardWidget->show();
}

void GameGUI::removeAdvSpell() {
    _timeAdvSpell = nullptr;
    if(_advSpellCard != nullptr) {
        _advSpellCard->close();
    }
    _advSpellCardWidget->show();
}

void GameGUI::deadCard(Card* card, bool adv) {
    int i = 0;
    CardWidget** listCardBoard;
    if(adv) {
        listCardBoard = _advCardBoard;
    } else {
        listCardBoard = _cardBoard;
    }

    CardWidget* cardWidget = nullptr;
    while(i < MAX_POSED_CARD && cardWidget == nullptr) {
        if(listCardBoard[i]->isCard(card)) {
            cardWidget = listCardBoard[i];
            listCardBoard[i] = nullptr;
        }
        ++i;
    }

    if(cardWidget != nullptr) {
        cardWidget->close();
        // Add to defausse
    } else {
        WizardLogger::warning("Carte morte introuvable");
    }
}

void GameGUI::placeAdvSpell(Card* card, Card* target) {
    // card = adverse card who attack
    // target = card who is attack (us card !)

    placeAdvSpellOnBoard(new CardWidget(card));

    int nbrTarget = 0;
    CardWidget* targetWidget = nullptr;
    while(nbrTarget < MAX_HAND && targetWidget == nullptr) {
        if(_cardBoard[nbrTarget]->isCard(target)) {
            targetWidget = _cardBoard[nbrTarget];
        }
        ++nbrTarget;
    }

    if(targetWidget != nullptr) {
        targetWidget->actualize();
    }

}
