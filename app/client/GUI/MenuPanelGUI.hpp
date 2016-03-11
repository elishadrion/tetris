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


class MenuPanelGUI : public QMainWindow {
    Q_OBJECT

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


public:
    MenuPanelGUI();

public slots:
    void quitApp();
    void makeBeginGame();
    void makeCancelWait();
    void makeOpenGame();
    void makeOpen();


};

#endif // MENUPANEL_HPP
