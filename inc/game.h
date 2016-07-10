#pragma once

#include <QCoreApplication>
#include <QObject>

#include "mainwindow.h"
#include "menugui.h"
#include "menumodel.h"
#include "selectiongui.h"
#include "selectionmodel.h"
#include "battlegui.h"
#include "battlemodel.h"
#include "herovector.h"

class Game : public QObject
{
    Q_OBJECT
private:
    QCoreApplication app;

    MainWindow *mainWindow;
    MenuGUI *menuGUI;
    MenuModel *menuModel;
    SelectionGUI *selectionGUI;
    SelectionModel *selectionModel;
    BattleGUI *battleGUI;
    BattleModel *battleModel;

    HeroVector heroes;

public slots:
    // MenuModel -> Game
    void clickedPlay();
    void clickedPlayOnline();
    void clickedPlayCPU();
    void clickedExit();
    void closedMenu();

    // SelectionModel -> Game
    void clickedStart(Player *player1, Player *player2);
    void clickedMenu();
    void closedSelection();

    // BattleModel -> Game
    void finished();
    void closedBattle();

public:
    Game(int argc, char *argv[]);

    int exec();
    void loadHeroes();
};
