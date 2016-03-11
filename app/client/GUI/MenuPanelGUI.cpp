#include "MenuPanelGUI.hpp"

/**
 * Constructor
 */
MenuPanelGUI::MenuPanelGUI() : QMainWindow() {

    setStyleSheet("QMainWindow { background-image: url(:/Images/bg.png); } "
                  "QPushButton { background-color: white; }");

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);


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


    _layoutOfLayout = new QGridLayout(centralWidget);
    _layoutOfLayout->addLayout(_layout,1,1);


    _layoutOfLayout->setRowStretch(0, 2);
    _layoutOfLayout->setRowStretch(1, 3);
    _layoutOfLayout->setRowStretch(2, 1);
    _layoutOfLayout->setColumnStretch(0, 1);
    _layoutOfLayout->setColumnStretch(1, 2);
    _layoutOfLayout->setColumnStretch(2, 1);


    showMaximized();

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
void MenuPanelGUI::makeBeginGame() {
    PacketManager::registerAsPlayer();
    QMessageBox sb;
    sb.setWindowTitle("Attente de Partie");
    sb.setText("En attente d'une partie");
    sb.setStandardButtons(QMessageBox::Cancel);

    // DEBUG
    sb.addButton(QMessageBox::Ignore);

    sb.connect(sb.button(QMessageBox::Cancel), SIGNAL(clicked()), this, SLOT(makeCancelWait()));
    // DEBUG
    sb.connect(sb.button(QMessageBox::Ignore), SIGNAL(clicked()), this, SLOT(makeOpenGame()));

    sb.exec();
}


/**
 * Slot to call when the player no longer wants play
 */
void MenuPanelGUI::makeCancelWait() {
    WizardLogger::info("Cancel wait game");
    PacketManager::cancelWaiting();
}


/**
 * Slot to open the game
 */
void MenuPanelGUI::makeOpenGame() {
    this->hide();
    new GameGUI();
}


/**
 * Slot to open the MainMenu
 */
void MenuPanelGUI::makeOpen() {
    this->show();
}

