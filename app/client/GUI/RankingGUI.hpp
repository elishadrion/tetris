#ifndef RANKINGGUI_HPP
#define RANKINGGUI_HPP

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QFont>

class RankingGui;
#include "MenuPanelGUI.hpp"

#include "PacketManager.hpp"
#include "client/WizardDisplay.hpp"
extern WizardDisplay *wizardDisplay;



class RankingGui : public QMainWindow {
    Q_OBJECT

    MenuPanelGUI* _menu;

    QLabel *_namePlayer;
    QLabel *_victories;
    QLabel *_defeats;
    QLabel *_ratio;

    QPushButton *_back;
    QVBoxLayout *_layoutNames;
    QVBoxLayout *_layoutVictory;
    QVBoxLayout *_layoutDefeat;
    QVBoxLayout *_layoutRatio;

    QGridLayout *_layoutTitles;
    QGridLayout *_layoutButton;
    QGridLayout *_layoutOfLayout;

public:
    RankingGui(MenuPanelGUI*);

private slots:
    void makeClose();

};

#endif // RANKINGGUI_HPP
