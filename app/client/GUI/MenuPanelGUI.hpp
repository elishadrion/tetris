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

class MenuPanelGUI : public QWidget {
    Q_OBJECT

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
};

#endif // MENUPANEL_HPP
