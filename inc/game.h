#pragma once

#include <QObject>
#include <vector>

#include "mainwindow.h"
#include "menugui.h"
#include "menumodel.h"
#include "selectiongui.h"
#include "selectionmodel.h"
#include "battlegui.h"
#include "battlemodel.h"
#include "herotemplate.h"

class Game : public QObject
{
    Q_OBJECT
private:
    MainWindow *mainWindow;
    MenuGUI *menuGUI;
    MenuModel *menuModel;
    SelectionGUI *selectionGUI;
    SelectionModel *selectionModel;
    BattleGUI *battleGUI;
    BattleModel *battleModel;

    std::vector<HeroTemplate*> heroes;

public slots:
    // MenuModel -> Game
    void clickedPlay();
    void clickedPlayOnline();
    void clickedPlayCPU();
    void clickedExit();
    void closedMenu();

    // SelectionModel -> Game
    void clickedStart();
    void clickedMenu();
    void closedSelection();

    // BattleModel -> Game
    void finished();
    void closedBattle();

public:
    Game();

    void start();
    void loadHeroes();
};
