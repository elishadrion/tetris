#ifndef MENUPANELGUI_H
#define MENUPANELGUI_H

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QFont>
#include <QPalette>

class MenuPanel : public QWidget{
    public:
        MenuPanel();
    private:
        QLabel *_nameGame;
        QPushButton *_gameStart;
        QPushButton *_checkCollection;
        QPushButton *_friendsList;
        QPushButton *_ranking;
        QPushButton *_quitter;

        QGridLayout *_layout;
        QHBoxLayout *_layoutLabel;
        QGridLayout *_layoutOfLayout;
};

#endif // MENUPANEL_H
