#include "EndPopup.hpp"


void EndPopup::valideQuit() {
    close();
    _gameGui->close();
}


EndPopup::EndPopup(QString msg, GameGUI* parent): QMainWindow(parent),
    _gameGui(parent) {

    // QListWidget;
    _centralWidget = new QWidget(this);
    setCentralWidget(_centralWidget);

    setWindowTitle("Fin de la partie");

    _gridlayout = new QGridLayout(_centralWidget);

    QLabel* message = new QLabel(msg);
    _gridlayout->addWidget(message, 0, 1);

    QPushButton* okButton = new QPushButton("Continuer");
    _gridlayout->addWidget(okButton, 1, 1);

    _gridlayout->setRowStretch(0, 1);
    _gridlayout->setRowStretch(1, 1);

    _gridlayout->setColumnStretch(0, 1);
    _gridlayout->setColumnStretch(1, 2);
    _gridlayout->setColumnStretch(2, 1);


    QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(valideQuit()));

    show();
}

