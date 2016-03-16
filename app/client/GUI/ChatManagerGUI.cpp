#include "ChatManagerGUI.h"

ChatManagerGUI::ChatManagerGUI() : QWidget(){

    _tab = new QTabWidget(this);
    _friends= new QListWidget;

    _tab->setFixedSize(250,250);   //A ENLEVER !!!!!!!
    _tab->addTab(_friends,tr("General"));

    _friends->addItem("J-P");   //A ENLEVER !!!!!!!
    _friends->addItem("P-A");   //A ENLEVER !!!!!!!
    _friends->addItem("M-J");   //A ENLEVER !!!!!!!
    _friends->addItem("Popol"); //A ENLEVER !!!!!!!
    _friends->addItem("MM");    //A ENLEVER !!!!!!!

    /*
     * for (int i = 0; i<sizeFriendList; i++){
     *  _friends->addItem(FriendList[i]);
     * }
    */


    _tab->setTabsClosable(true);
    connect(_tab, SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));
    _tab->tabBar()->tabButton(0,QTabBar::RightSide)->resize(0,0);

    connect(_friends, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(newTab(QListWidgetItem*)));
}

void ChatManagerGUI::closeTab(int i){
    _tab->removeTab(i);
}

void ChatManagerGUI::newTab(QListWidgetItem* item){
    std::string pseudo = item->text().toStdString();
    _tab->addTab(new ChatWidget(pseudo),item->text());
}
