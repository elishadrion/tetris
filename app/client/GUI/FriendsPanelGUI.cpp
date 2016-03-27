#include "FriendsPanelGUI.hpp"

FriendsPanelGUI::FriendsPanelGUI(MenuPanelGUI* menu) : QMainWindow(), _menu(menu) {

    setStyleSheet("QMainWindow { background-image: url(:/Images/ligue_justicie.jpg) 0 0 0 0 stretch stretch; "
                  "background-repeat: no-repeat; background-position: center center; } "
                  "QPushButton { background-color: white; } "
                  "QLabel { background-color: rgba(187, 187, 187, 0.72); }");

    setWindowTitle("Mes Amis");
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    _people = new QLabel("Nom du joueur");
    _people->setFixedHeight(30);
    _layoutPeople = new QVBoxLayout;
    _layoutPeople -> addWidget(_people);




    // Get Classement
    std::vector<std::string*> listPseudo;
    std::vector<int> listVictories;
    std::vector<int> listDefeats;

    /* Lock */
    pthread_mutex_lock(&wizardDisplay->packetStackMutex);

    //WizardLogger::info("Récupération du classement");

    /* Clean cache before ask to server */
    CacheManager::clearRankingCache();

    // Packet manager

    // ASK FRIENDS !!

    //PacketManager::askClassement();

    /* Wait for result */
    pthread_cond_wait(&wizardDisplay->packetStackCond, &wizardDisplay->packetStackMutex);

    /* Unlock */
    pthread_mutex_unlock(&wizardDisplay->packetStackMutex);


    _back =  new QPushButton("Retour");
    _back->setMaximumHeight(50);
    _back->setMaximumWidth(200);
    connect(_back, SIGNAL(clicked()), this, SLOT(makeClose()));

    showMaximized();

}

void FriendsPanelGUI::makeClose() {
    _menu -> makeOpen();
    this -> close();
}
