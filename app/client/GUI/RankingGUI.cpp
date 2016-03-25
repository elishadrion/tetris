#include "RankingGUI.hpp"

RankingGui::RankingGui(MenuPanelGUI* menu) : QMainWindow(), _menu(menu) {

    setStyleSheet("QMainWindow { background-image: url(:/Images/ligue_justicie.jpg) 0 0 0 0 stretch stretch; "
                  "background-repeat: no-repeat; background-position: center center; } "
                  "QPushButton { background-color: white; } "
                  "QLabel { background-color: rgba(187, 187, 187, 0.72); }");

    setWindowTitle("Classement");
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    _namePlayer = new QLabel("    Nom du joueur    ");
    _namePlayer->setFixedHeight(30);
    _layoutNames = new QVBoxLayout;
    _layoutNames->addWidget(_namePlayer);


    _victories = new QLabel("    Victoire(s)    ");
    _victories->setFixedHeight(30);
    _layoutVictory = new QVBoxLayout;
    _layoutVictory->addWidget(_victories);


    _defeats = new QLabel("    Défaite(s)    ");
    _defeats->setFixedHeight(30);
    _layoutDefeat = new QVBoxLayout;
    _layoutDefeat->addWidget(_defeats);


    _ratio = new QLabel("    Ratio Victoire(s)/Parties    ");
    _ratio->setFixedHeight(30);
    _layoutRatio = new QVBoxLayout;
    _layoutRatio->addWidget(_ratio);

    _layoutTitles = new QGridLayout;
    _layoutTitles->addLayout(_layoutNames,0,0);
    _layoutTitles->addLayout(_layoutVictory,0,1);
    _layoutTitles->addLayout(_layoutDefeat,0,2);
    _layoutTitles->addLayout(_layoutRatio,0,3);
    _layoutTitles->setAlignment(Qt::AlignCenter);

    // Get Classement

    std::vector<std::string*> listPseudo;
    std::vector<int> listVictories;
    std::vector<int> listDefeats;

    /* Lock */
    pthread_mutex_lock(&wizardDisplay->packetStackMutex);

    WizardLogger::info("Récupération du classement");

    // Packet manager
    PacketManager::askClassement();

    /* Wait for result */
    pthread_cond_wait(&wizardDisplay->packetStackCond, &wizardDisplay->packetStackMutex);

    /* Unlock */
    pthread_mutex_unlock(&wizardDisplay->packetStackMutex);

    QVBoxLayout* colPseudo = new QVBoxLayout;
    QVBoxLayout* colVictories = new QVBoxLayout;
    QVBoxLayout* colDefeats = new QVBoxLayout;
    QVBoxLayout* colRatio = new QVBoxLayout;
    for(int i = 0; i < CacheManager::getRankingSize(); ++i) {
        // TO DO: convertir le pointeur de listPseudo en string
        QLabel* pseudo = new QLabel(QString::fromStdString(*CacheManager::getPseudoRanking(i)));
        colPseudo->addWidget(pseudo);

        int victory = CacheManager::getVictoryRanking(i);
        QLabel* victories = new QLabel(
                    QString::fromStdString(std::to_string(victory)));
        colVictories->addWidget(victories);

        int defeat = CacheManager::getDefeatRanking(i);
        QLabel* defeats = new QLabel(
                    QString::fromStdString(std::to_string(defeat)));
        colDefeats->addWidget(defeats);

        int ration;
        if (defeat + victory > 0)
            ration = victory / (defeat + victory);
        else
            ration = 0;
        QLabel* ratio = new QLabel(
                    QString::fromStdString(std::to_string(ration)));
        colRatio->addWidget(ratio);
    }

    QGridLayout* allInformations = new QGridLayout;
    allInformations->addLayout(colPseudo, 0, 0);
    allInformations->addLayout(colVictories, 0, 1);
    allInformations->addLayout(colDefeats, 0, 2);
    allInformations->addLayout(colRatio, 0, 3);
    allInformations->setAlignment(Qt::AlignCenter);


    _back =  new QPushButton("Retour");
    _back->setMaximumHeight(50);
    _back->setMaximumWidth(200);
    QObject::connect(_back, SIGNAL(clicked()), this, SLOT(makeClose()));

    _layoutButton = new QGridLayout;
    _layoutButton->addWidget(_back);

    _layoutOfLayout = new QGridLayout(centralWidget);
    _layoutOfLayout->addLayout(_layoutTitles,0,1);
    _layoutOfLayout->addLayout(allInformations,0,1,10,1);
    _layoutOfLayout->addLayout(_layoutButton,2,1);

    showMaximized();

}

void RankingGui::makeClose() {
    _menu->makeOpen();
    this->close();
}
