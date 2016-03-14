#ifndef MENUPANELGUI_HPP
#define MENUPANELGUI_HPP

#include "GUIDefine.hpp" /* MUST BE FIRST */

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QMainWindow>
#include <QMessageBox>

#include "PacketManager.hpp"
#include "GUI/GameGUI.hpp"
#include "common/WizardLogger.hpp"

#include <string>


class GUI;
class MenuPanelGUI;
#include "GUI.hpp"


class MenuPanelGUI : public QMainWindow {
    Q_OBJECT

    GUI* _gui;

    QWidget *centralWidget;

    QLabel *_nameGame;
    QPushButton *_gameStart;
    QPushButton *_checkCollection;
    QPushButton *_friendsList;
    QPushButton *_ranking;
    QPushButton *_quitter;

    QGridLayout *_layout;
    QHBoxLayout *_layoutLabel;
    QGridLayout *_layoutOfLayout;

    QMessageBox *_msgBox;


public:
    MenuPanelGUI(GUI*);
    void callInitGame();

signals:
    void mustInitGame();

public slots:
    void quitApp();
    void makeReqToPlayGame();
    void makeCancelWait();
    void makeOpenGame();
    void makeOpen();


};

#endif // MENUPANEL_HPP
