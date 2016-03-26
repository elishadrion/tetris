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
#include <QTimer>

#include "PacketManager.hpp"
#include "GUI/GameGUI.hpp"
#include "common/WizardLogger.hpp"
class RankingGUI;
class MenuPanelGUI;
#include "RankingGUI.hpp"

#include <string>


class GUI;
class MenuPanelGUI;
#include "GUI.hpp"


class MenuPanelGUI : public QMainWindow {
    Q_OBJECT

    GUI* _gui;

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

private slots:
    void quitApp();
    void makeReqToPlayGame();
    void makeCancelWait();
    void makeOpenGame();
    void makeOpenClassement();

public slots:
    void makeOpen();


};

#endif // MENUPANEL_HPP
