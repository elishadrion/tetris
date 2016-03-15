#include "DeckChooseGUI.hpp"


void DeckChooseGUI::valideDeck() {
    QList<QListWidgetItem *> listItem = _listDeck->selectedItems();
    if(listItem.size() == 1) {
        std::string select = listItem[0]->text().toStdString();

        WizardLogger::info("Deck choisi: " + select);
        Player::getPlayer()->setDeck(select);
        close();

    } else {
        WizardLogger::warning("Nombre d'élément sélectionné incorrect " + listItem.size());
    }

}


DeckChooseGUI::DeckChooseGUI(GameGUI* parent): QMainWindow(parent) {
    _gameGui = parent;

    // QListWidget;
    _centralWidget = new QWidget(this);
    setCentralWidget(_centralWidget);

    setWindowTitle("Choix du deck");

    _gridlayout = new QGridLayout(_centralWidget);

    QLabel* desc = new QLabel("Choisissez votre Deck");
    _gridlayout->addWidget(desc, 0, 1, 1, 2);

    _listDeck = new QListWidget;
    Player* player = Player::getPlayer();
    std::vector<std::string> listNomDeck = player->getDecks();

    for(unsigned i = 0; i < listNomDeck.size(); ++i) {
        _listDeck->addItem(QString(static_cast<std::string>(listNomDeck[i]).c_str()));
    }
    _listDeck->item(0)->setSelected(true);


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


    QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(valideDeck()));
    //QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelDeck()));

    show();
}

