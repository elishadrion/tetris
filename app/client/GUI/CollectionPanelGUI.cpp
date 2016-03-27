#include "CollectionPanelGUI.hpp"

CollectionPanelGUI::CollectionPanelGUI(MenuPanelGUI* menu): QMainWindow(),
_menu(menu){

    setWindowTitle("Collection & Decks");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);


    _nCards=0;

    _grid = new QGridLayout(centralWidget);
    _collectionWidget = new CollectionWidget();

    _grid->setColumnStretch(0,15);
    _grid->setColumnStretch(1,3);
    _grid->setColumnStretch(2,3);

    _grid->setRowStretch(0,2);
    _grid->setRowStretch(1,18);
    _grid->setRowStretch(2,5);

    _tab = new QTabWidget();

    _tab->addTab(_collectionWidget,tr("Collection"));

    _decks = Player::getPlayer()->getDecks();
    for (std::size_t i=0;i<_decks.size();i++){
        _tab->addTab(new DeckWidget(_decks[i]),QString::fromStdString(_decks[i]));
    }

    _grid->addWidget(_tab,0,0,3,1);

    _newDeck = new QTextBrowser();

    _labelNewDeck = new QLabel("Création d'un deck:");
    _labelNewDeck->setAlignment(Qt::AlignCenter);

    _nCardsAdd = new QLabel();
    _nCardsAdd->setText(QString::fromStdString(std::to_string(_nCards)) + "/20");
    _nCardsAdd->setAlignment(Qt::AlignCenter);

    _addDeck = new QPushButton("Ajouter Deck");

    _grid->addWidget(_labelNewDeck,0,1);
    _grid->addWidget(_nCardsAdd,0,2);
    _grid->addWidget(_newDeck,1,1,1,2);
    _grid->addWidget(_addDeck,2,1,1,2);

    connect(_addDeck,SIGNAL(clicked()),this,SLOT(addDeck()));

    showMaximized();

}

void CollectionPanelGUI::addDeck(){

}

void CollectionPanelGUI::closeEvent (QCloseEvent *event)
{
    _menu->makeOpen();
	event->accept();
}