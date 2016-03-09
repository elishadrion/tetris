#include "MenuPanelGUI.hpp"

MenuPanelGUI::MenuPanelGUI() : QWidget() {

    _nameGame = new QLabel(" Wizard Poker ");
    _nameGame->setFont(QFont("FOLKARD",75));
    _nameGame->setAlignment(Qt::AlignHCenter);
    _nameGame->setFixedHeight(110);

    _gameStart = new QPushButton(" Lancer une partie ");
    _gameStart->setMaximumHeight(50);
    _gameStart->setMaximumWidth(200);

    _checkCollection = new QPushButton(" Ouvrir la collection ");
    _checkCollection->setMaximumHeight(50);
    _checkCollection->setMaximumWidth(200);

    _friendsList = new QPushButton(" Liste des amis ");
    _friendsList->setMaximumHeight(50);
    _friendsList->setMaximumWidth(200);

    _ranking = new QPushButton(" Classement ");
    _ranking->setMaximumHeight(50);
    _ranking->setMaximumWidth(200);

    _quitter = new QPushButton(" Quitter ");
    _quitter->setMaximumHeight(50);
    _quitter->setMaximumWidth(200);
    //QObject::connect(_quitter, SIGNAL(clicked()), qApp, SLOT(quit()));


    _layout = new QGridLayout;
    _layout->addWidget(_gameStart);
    _layout->addWidget(_checkCollection);
    _layout->addWidget(_friendsList);
    _layout->addWidget(_ranking);
    _layout->addWidget(_quitter);
    _layout->setSpacing(18);

    _layoutLabel = new QHBoxLayout;
    _layoutLabel->addWidget(_nameGame);


    _layoutOfLayout = new QGridLayout;
    _layoutOfLayout->addLayout(_layoutLabel,0,1);
    _layoutOfLayout->addLayout(_layout,1,1);

    setLayout(_layoutOfLayout);
    //setStyleSheet("QWidget{background-image: url(/Users/Amean/Desktop/bg.jpg);}");
    showMaximized();

}
