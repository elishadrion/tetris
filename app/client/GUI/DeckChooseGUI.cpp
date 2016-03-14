#include "DeckChooseGUI.hpp"

DeckChooseGUI::DeckChooseGUI(GameGUI* parent) : QMainWindow(parent) {
    _gameGui = parent;

    // QListWidget;
    _centralWidget = new QWidget(this);
    setCentralWidget(_centralWidget);

    _gridlayout = new QGridLayout(_centralWidget);

    QLabel* desc = new QLabel("Choisissez votre Deck");
    _gridlayout->addWidget(desc, 0, 1, 1, 2);

    _listDeck = new QListWidget;
    Player* player = Player::getPlayer();
    for(unsigned i = 0; i < player->getDeckSize(); ++i) {
        _listDeck->addItem("Deck: " + player->getDeck()[i]);
    }

    _gridlayout->addWidget(_listDeck, 1, 1, 1, 2);

    QPushButton* okButton = new QPushButton("Valider");
    _gridlayout->addWidget(okButton, 2, 1);

    QPushButton* cancelButton = new QPushButton("Annuler (et quitter la partie)");
    _gridlayout->addWidget(cancelButton, 2, 2);

    _gridlayout->setRowStretch(0, 1);
    _gridlayout->setRowStretch(1, 2);
    _gridlayout->setRowStretch(2, 2);
    _gridlayout->setRowStretch(3, 1);

    _gridlayout->setColumnStretch(0, 1);
    _gridlayout->setColumnStretch(1, 3);
    _gridlayout->setColumnStretch(2, 2);
    _gridlayout->setColumnStretch(3, 1);



    show();
}
