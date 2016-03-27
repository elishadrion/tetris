#include "GameGUI.hpp"


/**
 * Constructor
 *
 * @param pseudo from the adverse player
 */
GameGUI::GameGUI() : QMainWindow(), _inHandSelect(nullptr),
    _onBoardSelect(nullptr), _timeSpell(nullptr),
    _timeAdvSpell(nullptr) {

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
    _spellCardWidget = new CardWidget(true, true);
    connect(_spellCardWidget, SIGNAL(selected(CardWidget*)),
            this, SLOT(selectSpellEmplacement(CardWidget*)));
    _gridlayout->addWidget(_spellCardWidget, 6, 2);

    _advSpellCardWidget = new CardWidget(true, true);
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


    //////// INFO PLAYER ////////
    QHBoxLayout* layoutInfoEnergy = new QHBoxLayout;
    QLabel *labelEnergy = new QLabel(QString::fromStdString("Energie: "));
    layoutInfoEnergy->addWidget(labelEnergy);
    _infoEnergy = new QLabel(QString(
                    std::to_string(GameManager::getInstance()->getEnergy()).c_str()));
    layoutInfoEnergy->addWidget(_infoEnergy);
    _gridlayout->addLayout(layoutInfoEnergy, 8, 5);

    QHBoxLayout* layoutInfoHeal = new QHBoxLayout;
    QLabel *labelHeal = new QLabel(QString::fromStdString("Vie: "));
    layoutInfoHeal->addWidget(labelHeal);
    _infoHeal = new QLabel(QString(
                    std::to_string(GameManager::getInstance()->getHeal()).c_str()));
    layoutInfoHeal->addWidget(_infoHeal);
    _gridlayout->addLayout(layoutInfoHeal, 8, 7);

    //////// ADV INFO PLAYER ////////
    QHBoxLayout* layoutAdvInfoEnergy = new QHBoxLayout;
    QLabel *labelAdvEnergy = new QLabel(QString::fromStdString("Energie: "));
    layoutAdvInfoEnergy->addWidget(labelAdvEnergy);
    _infoAdvEnergy = new QLabel(QString(
                        std::to_string(GameManager::getInstance()->getAdverseEnergy()).c_str()));
    layoutAdvInfoEnergy->addWidget(_infoAdvEnergy);
    _gridlayout->addLayout(layoutAdvInfoEnergy, 0, 5);

    QHBoxLayout* layoutAdvInfoHeal = new QHBoxLayout;
    QLabel *labelAdvHeal = new QLabel(QString::fromStdString("Vie: "));
    layoutAdvInfoHeal->addWidget(labelAdvHeal);
    _infoAdvHeal = new QLabel(QString(
                        std::to_string(GameManager::getInstance()->getAdverseHeal()).c_str()));
    layoutAdvInfoHeal->addWidget(_infoAdvHeal);
    _gridlayout->addLayout(layoutAdvInfoHeal, 0, 7);



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
    _gridlayout->setColumnStretch(1, 4); // Deck
    _gridlayout->setColumnStretch(2, 4); // Sort

    _gridlayout->setColumnStretch(3, 4); // Card 1
    _gridlayout->setColumnStretch(4, 4); // Card 2
    _gridlayout->setColumnStretch(5, 4); // Card 3
    _gridlayout->setColumnStretch(6, 4); // Card 4
    _gridlayout->setColumnStretch(7, 4); // Card 5
    _gridlayout->setColumnStretch(8, 4); // Card 6
    _gridlayout->setColumnStretch(9, 4); // Card 7

    // colonne de droite
    _gridlayout->setColumnStretch(10, 1); // Espace
    _gridlayout->setColumnStretch(11, 3); // Next Turn
    _gridlayout->setColumnStretch(12, 1); // Espace

    _gridlayout->setColumnStretch(13, 12); // tchat


    // Ligne des cartes 1
    _gridlayout->setRowStretch(0, 2); // adverse player
    _gridlayout->setRowStretch(1, 4); // adverse hand
    _gridlayout->setRowStretch(2, 4); // adverse sort
    _gridlayout->setRowStretch(3, 5); // adverse place
    _gridlayout->setRowStretch(4, 1); // bouton passer
    _gridlayout->setRowStretch(5, 5); // Card placed
    _gridlayout->setRowStretch(6, 4); // Sort + espace
    _gridlayout->setRowStretch(7, 5); // In Hand
    _gridlayout->setRowStretch(8, 1); // Infos player


    show();
    this->showMaximized(); // set full screen

    connect(this, SIGNAL(nextPlayer()), this, SLOT(viewPassButton()));
    connect(this, SIGNAL(mustUpdateTurn()), this, SLOT(updateTurn()));
    connect(this, SIGNAL(cardDraw(Card*)), this, SLOT(placeInHandCard(Card*)));
    connect(this, SIGNAL(advCardDraw()), this, SLOT(drawAdvCard()));
    connect(_nextTurnBouton, SIGNAL(clicked()), this, SLOT(nextTurn()));
    connect(this, SIGNAL(mustPlaceAdvCard(Card*)), this, SLOT(placeAdvCard(Card*)));
    connect(this, SIGNAL(mustPlaceAdvSpell(Card*, Card*)), this, SLOT(placeAdvSpell(Card*,Card*)));
    connect(this, SIGNAL(mustPlaceAdvCardAttack(Card*, Card*)),
            this, SLOT(placeAdvCardAttack(Card*, Card*)));
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
        updatePlayerInfo();

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

        updateAdvPlayerInfo();
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

void GameGUI::updatePlayerInfo() {
    _infoHeal->setText(QString(
        std::to_string(GameManager::getInstance()->getHeal()).c_str()));
    _infoEnergy->setText(QString(
        std::to_string(GameManager::getInstance()->getEnergy()).c_str()));
}

void GameGUI::updateAdvPlayerInfo() {
    _infoAdvHeal->setText(QString(
        std::to_string(GameManager::getInstance()->getAdverseHeal()).c_str()));
    _infoAdvEnergy->setText(QString(
        std::to_string(GameManager::getInstance()->getAdverseEnergy()).c_str()));
}


void GameGUI::displayError(int errorId) {
    displayError(ErrorAPI::errorToStr(errorId));
}

void GameGUI::displayError(std::string msg) {
    QMessageBox messageBox;
    messageBox.critical(this, QString::fromStdString("Erreur"),
                        QString::fromStdString(msg));
}


// ===================== UTILS ============================

/**
 * Get the index of an CardWidget in the vector Hand
 *
 * @param card which is search
 * @return -1 if not found, index else
 */
int GameGUI::getIndexHand(CardWidget* card) {
    int i = 0;
    while(i < MAX_HAND && _cardInHand[i] != card) {
        ++i;
    }

    if(_cardInHand[i] != card) {
        i = -1;
    }
    return i;
}

/**
 * Get the index of an CardWidget in the vector Board
 *
 * @param card which is search
 * @return -1 if not found, index else
 */
int GameGUI::getIndexBoard(CardWidget* card) {
    int i = 0;
    while(i < MAX_POSED_CARD && _cardBoard[i] != card) {
        ++i;
    }

    if(_cardBoard[i] != card) {
        i = -1;
    }
    return i;

}


// ==================== ACTION ============================
/**
 * Call when the inHandSelect is a spell and attack
 *
 * @param cardWidget which card is attack
 */
void GameGUI::placeAndAttack(CardWidget* cardWidget) {
    /* Lock */
    pthread_mutex_lock(&wizardDisplay->packetStackMutex);

    // Packet manager
    WizardLogger::info("Placement & attack: "+ std::to_string(_inHandSelect->getId()));
    PacketManager::sendPlaceCardAttack(_inHandSelect->getId(), cardWidget->getPosition());

    /* Wait for result */
    pthread_cond_wait(&wizardDisplay->packetStackCond, &wizardDisplay->packetStackMutex);

    /* Check result */
    if (wizardDisplay->packetErrorStack.empty()) {
        WizardLogger::info("Pose la carte & attack");

        if(_inHandSelect->isMonster()) {

            int i = 0;
            while(i < MAX_POSED_CARD && !_cardBoard[i]->isEmplacement()) {
                ++i;
            }

            if(i != MAX_POSED_CARD) {
                _cardBoard[i]->close();
                _cardBoard[i] = _inHandSelect;
                _gridlayout->addWidget(_inHandSelect, 5, 3+i);
            } else {
                WizardLogger::warning(
                            "Impossible de placer la carte & attaquer (plus de place)");
            }


        } else {
            placeSpellCardOnBoard();
        }
        updatePlayerInfo();      // update player info
        cardWidget->actualize(); // update info of this card

    } else {
        int error = reinterpret_cast<int>(wizardDisplay->packetErrorStack.back());
        wizardDisplay->packetErrorStack.pop_back();
        displayError(error);
    }

    /* Unlock */
    pthread_mutex_unlock(&wizardDisplay->packetStackMutex);
}

/**
 * Call when the onBoardSelect attack
 *
 * @param cardWidget wich is attack
 */
void GameGUI::attack(CardWidget* cardWidget) {

    if(_onBoardSelect != nullptr) {
        /* Lock */
        pthread_mutex_lock(&wizardDisplay->packetStackMutex);

        // Packet manager
        PacketManager::sendAttack(_onBoardSelect->getPosition(), cardWidget->getPosition());

        /* Wait for result */
        pthread_cond_wait(&wizardDisplay->packetStackCond, &wizardDisplay->packetStackMutex);

        /* Check result */
        if (wizardDisplay->packetErrorStack.empty()) {
            WizardLogger::info("Card Attack");

            // actualise player informations
            if(cardWidget != nullptr) {
                cardWidget->actualize(); // update heal of this card
            }
            updatePlayerInfo();

        } else {
            int error = reinterpret_cast<int>(wizardDisplay->packetErrorStack.back());
            wizardDisplay->packetErrorStack.pop_back();
            displayError(error);
        }

        /* Unlock */
        pthread_mutex_unlock(&wizardDisplay->packetStackMutex);

    } else {
        displayError("Vous devez sélectionner une carte qui va attaquer");
    }
}



// ================== PUBLIC CALL =========================

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

    if(_onBoardSelect != nullptr) {
        _onBoardSelect->setSelect(false);
        _onBoardSelect = nullptr;
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

void GameGUI::callPlaceAdvCardAttack(Card* card, Card* target) {
    emit mustPlaceAdvCardAttack(card, target);
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
    updatePlayerInfo();
    updateAdvPlayerInfo();
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
        connect(cardWidget, SIGNAL(selected(CardWidget*)), this, SLOT(selectCard(CardWidget*)));
        connect(cardWidget, SIGNAL(unSelected(CardWidget*)), this, SLOT(unSelectCard(CardWidget*)));
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
void GameGUI::selectCard(CardWidget* cardWidget) {
    if(getIndexBoard(cardWidget) != -1) {
        if(_inHandSelect != nullptr) {
            placeAndAttack(cardWidget);

            _inHandSelect->setSelect(false);
            _inHandSelect = nullptr;
            cardWidget->setSelect(false);
            return;
        }

        if(_onBoardSelect != nullptr) {
            _onBoardSelect->setSelect(false);
        }
        _onBoardSelect = cardWidget;

    } else if(getIndexHand(cardWidget) != -1) {
        if(_onBoardSelect != nullptr) {
            _onBoardSelect->setSelect(false);
            _onBoardSelect = nullptr;
        }

        if(_inHandSelect != nullptr) {
            _inHandSelect->setSelect(false);
        }
        _inHandSelect = cardWidget;
    } else {
        WizardLogger::info("Carte non trouvé ni dans la main ni sur le plateau");
    }
    WizardLogger::info("Selection de la carte: " + std::to_string(cardWidget->getId()));
}

/**
 * Call when player unselect card
 */
void GameGUI::unSelectCard(CardWidget* cardWidget) {
    if(getIndexBoard(cardWidget) != -1) {
        if(_onBoardSelect != nullptr) {
            _onBoardSelect->setSelect(false);
        }
        _onBoardSelect = cardWidget;

    } else if(getIndexHand(cardWidget) != -1) {
        if(_inHandSelect != nullptr) {
            _inHandSelect->setSelect(false);
        }
        _inHandSelect = cardWidget;
    }
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
        }
    }
}

void GameGUI::selectAdvCard(CardWidget* cardWidget) {
    cardWidget->setSelect(false);

    // If card in hand select
    if(_inHandSelect != nullptr) {
        placeAndAttack(cardWidget);
        _inHandSelect->setSelect(false);
        _inHandSelect = nullptr;


    } else if(_onBoardSelect != nullptr) {
        attack(cardWidget);
        _onBoardSelect->setSelect(false);
        _onBoardSelect = nullptr;
    }
}

void GameGUI::selectSpellEmplacement(CardWidget* cardWidget) {
    cardWidget->setSelect(false);
    if(_inHandSelect != nullptr) {
        // TO DO
        // place spell without target
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
    updateAdvPlayerInfo();

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
    CardWidget** listCardBoard;
    if(adv) {
        listCardBoard = _advCardBoard;
    } else {
        listCardBoard = _cardBoard;
    }

    int i = 0;
    WizardLogger::info("[Debug] position search: " + std::to_string(card->getPosition()));
    while(i < MAX_POSED_CARD &&
          (listCardBoard[i]->isEmplacement() ||
          !listCardBoard[i]->isOnPosition(card->getPosition()))) {

        WizardLogger::info("[Debug] i: " + std::to_string(i));
        if(listCardBoard[i]->isEmplacement()) {
            WizardLogger::info("[Debug] isEmplacement");
        } else {
            WizardLogger::info("[Debug] current position: " +
                               std::to_string(listCardBoard[i]->getPosition()));
        }

        ++i;
    }

    if(i < MAX_POSED_CARD) {

        listCardBoard[i]->close();
        addEmplacement(i, adv);
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
        if(!_cardBoard[nbrTarget]->isEmplacement() &&
                _cardBoard[nbrTarget]->isOnPosition(target->getPosition())) {
            targetWidget = _cardBoard[nbrTarget];
        }
        ++nbrTarget;
    }

    if(targetWidget != nullptr) {
        targetWidget->actualize();
    } else {
        WizardLogger::warning("Carte visée non trouvé");
    }

}


void GameGUI::placeAdvCardAttack(Card* card, Card* target) {
    placeAdvCard(card);

    int position = 0;
    CardWidget* elem = nullptr;
    while(position < MAX_POSED_CARD && elem == nullptr) {
        if(!_cardBoard[position]->isEmplacement() &&
                _cardBoard[position]->isOnPosition(target->getPosition())) {
            elem = _cardBoard[position];

        } else if(!_advCardBoard[position]->isEmplacement() &&
                  _advCardBoard[position]->isOnPosition(target->getPosition())) {
            elem = _advCardBoard[position];

        }
        ++position;
    }

    if(elem != nullptr) {
        elem->actualize();
    } else {
        WizardLogger::warning("Carte attaqué introuvable");
    }

}
