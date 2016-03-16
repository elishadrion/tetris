#ifndef RANKINGGUI_HPP
#define RANKINGGUI_HPP

#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QFont>

class RankingGui : public QWidget{
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
    RankingGui();
};

#endif // RANKINGGUI_HPP
