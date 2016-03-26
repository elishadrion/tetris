#include "MenuPanelGUI.hpp"


/**
 * Constructor
 */
MenuPanelGUI::MenuPanelGUI(GUI* parent) : QMainWindow() {
    _gui = parent;

    setStyleSheet("QMainWindow { background-image: url(:/Images/bg.png) 0 0 0 0 stretch stretch; "
                  "background-repeat: no-repeat; background-position: center center; } "
                  "QPushButton { background-color: white; }");

    setWindowTitle("Menu principal");
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);


    _gameStart = new QPushButton(" Lancer une partie ");
    _gameStart->setMaximumHeight(50);
    _gameStart->setMaximumWidth(200);
    QObject::connect(_gameStart, SIGNAL(clicked()), this, SLOT(makeReqToPlayGame()));

    _checkCollection = new QPushButton(" Ouvrir la collection ");
    _checkCollection->setMaximumHeight(50);
    _checkCollection->setMaximumWidth(200);

    _friendsList = new QPushButton(" Liste des amis ");
    _friendsList->setMaximumHeight(50);
    _friendsList->setMaximumWidth(200);

    _ranking = new QPushButton(" Classement ");
    _ranking->setMaximumHeight(50);
    _ranking->setMaximumWidth(200);
    QObject::connect(_ranking, SIGNAL(clicked()), this, SLOT(makeOpenClassement()));

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


    _layoutOfLayout = new QGridLayout(centralWidget);
    _layoutOfLayout->addLayout(_layout,2,1);
    _layoutOfLayout->addWidget(new ChatManagerGUI(0), 1, 3, 2, 1); // Tchat


    _layoutOfLayout->setRowStretch(0, 1);
    _layoutOfLayout->setRowStretch(1, 1);
    _layoutOfLayout->setRowStretch(2, 3);
    _layoutOfLayout->setRowStretch(3, 1);

    _layoutOfLayout->setColumnStretch(0, 5);
    _layoutOfLayout->setColumnStretch(1, 9);
    _layoutOfLayout->setColumnStretch(2, 2);
    _layoutOfLayout->setColumnStretch(3, 3);


    showMaximized();

}


/**
 * Call the mustInitGame (emit)
 */
void MenuPanelGUI::callInitGame() {
    emit mustInitGame();
}


/**
 * Slot to quit application
 */
void MenuPanelGUI::quitApp() {
    PacketManager::sendDisconnection();
    qApp->quit();
}


/**
 * Slot to call when the player will play
 */
void MenuPanelGUI::makeReqToPlayGame() {
    connect(this, SIGNAL(mustInitGame()), this, SLOT(makeOpenGame()));

    _msgBox = new QMessageBox(this);
    _msgBox->setWindowTitle("Attente de Partie");
    _msgBox->setText("En attente d'une partie");
    _msgBox->setStandardButtons(QMessageBox::Cancel);

    _msgBox->connect(_msgBox->button(QMessageBox::Cancel), SIGNAL(clicked()), this, SLOT(makeCancelWait()));
    _msgBox->show();
    WizardLogger::info("ouverture de l'attente");

    PacketManager::makeGameRequest();
}


/**
 * Slot to call when the player no longer wants play
 */
void MenuPanelGUI::makeCancelWait() {
    WizardLogger::info("Cancel wait game");
    PacketManager::makeGameCancelRequest();
}


/**
 * Slot to open the game
 */
void MenuPanelGUI::makeOpenGame() {
    WizardLogger::info("Une partie a été trouvée, ouverture du menu");
    this->hide();
    QTimer::singleShot(500,_msgBox,SLOT(close())); // Close after
    _gui->setGameMenu(new GameGUI());
}

/**
 * Slot to open the Classement
 */
void MenuPanelGUI::makeOpenClassement() {
    WizardLogger::info("Ouverture du classement");
    new RankingGui(this);
    this->hide();
}


/**
 * Slot to open the MainMenu
 */
void MenuPanelGUI::makeOpen() {
    this->show();
    showMaximized();
}

