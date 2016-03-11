#include "MenuPanelGUI.hpp"

MenuPanelGUI::MenuPanelGUI() : QMainWindow() {

    setStyleSheet("QMainWindow { background-image: url(:/Images/bg.png); } "
                  "QPushButton { background-color: white; }");

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

//    _nameGame = new QLabel(" ");
//    _nameGame->setFont(QFont("FOLKARD",75));
//    _nameGame->setAlignment(Qt::AlignHCenter);
//    _nameGame->setFixedHeight(110);


    _gameStart = new QPushButton(" Lancer une partie ");
    _gameStart->setMaximumHeight(50);
    _gameStart->setMaximumWidth(200);
    QObject::connect(_gameStart, SIGNAL(clicked()), this, SLOT(makeBeginGame()));

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
    QObject::connect(_quitter, SIGNAL(clicked()), this, SLOT(quitApp()));


    _layout = new QGridLayout;
    _layout->addWidget(_gameStart);
    _layout->addWidget(_checkCollection);
    _layout->addWidget(_friendsList);
    _layout->addWidget(_ranking);
    _layout->addWidget(_quitter);
    _layout->setSpacing(18);

    //_layoutLabel = new QHBoxLayout;
    //_layoutLabel->addWidget(_nameGame);


    _layoutOfLayout = new QGridLayout(centralWidget);
    //_layoutOfLayout->addLayout(_layoutLabel,0,1);
    _layoutOfLayout->addLayout(_layout,1,1);


    _layoutOfLayout->setRowStretch(0, 2);
    _layoutOfLayout->setRowStretch(1, 3);
    _layoutOfLayout->setRowStretch(2, 1);
    _layoutOfLayout->setColumnStretch(0, 1);
    _layoutOfLayout->setColumnStretch(1, 2);
    _layoutOfLayout->setColumnStretch(2, 1);


    showMaximized();

}

void MenuPanelGUI::makeBeginGame() {
    PacketManager::registerAsPlayer();
    QMessageBox sb;
    sb.setWindowTitle("Attente de Partie");
    sb.setText("En attente d'une partie");
    sb.setStandardButtons(QMessageBox::Cancel);
    sb.connect(sb.button(QMessageBox::Cancel), SIGNAL(clicked()), this, SLOT(makeCancelWait()));
    sb.exec();
}

void MenuPanelGUI::makeCancelWait() {
    WizardLogger::info("Cancel wait game");
    PacketManager::cancelWaiting();
}

void MenuPanelGUI::quitApp() {
    PacketManager::sendDisconnection();
    qApp->quit();
}
