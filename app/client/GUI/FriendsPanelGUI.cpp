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

    _back =  new QPushButton("Retour");
    _back->setMaximumHeight(50);
    _back->setMaximumWidth(200);
    connect(_back, SIGNAL(clicked()), this, SLOT(makeClose()));

    QGridLayout* layoutOfLayout = new QGridLayout(centralWidget);
    layoutOfLayout->addWidget(_back);

    showMaximized();

}

void FriendsPanelGUI::makeClose() {
    _menu -> makeOpen();
    this -> close();
}
