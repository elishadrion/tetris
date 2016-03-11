#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QTextEdit>
#include <QTabWidget>
#include <QTabBar>
#include <QGroupBox>
#include <QMainWindow>


class GameGUI : public QMainWindow {
    Q_OBJECT

    QWidget *centralWidget;
    QGridLayout *gridlayout;

public:
    GameGUI();

};

#endif // GAME_H
