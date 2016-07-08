#pragma once

#include <QObject>

#include "menugui.h"
#include "menumodel.h"
#include "selectiongui.h"
#include "selectionmodel.h"
#include "battlegui.h"
#include "battlemodel.h"

class Game : public QObject
{
    Q_OBJECT
private:
    MenuGUI *menuGUI;
    MenuModel *menuModel;
    SelectionGUI *selectionGUI;
    SelectionModel *selectionModel;
    BattleGUI *battleGUI;
    BattleModel *battleModel;

public slots:
    // MenuModel -> Game
    void clickedPlay();
    void clickedPlayOnline();
    void clickedPlayCPU();
    void clickedExit();
    void closedMenu();

    // SelectionModel -> Game
    void clickedReady();
    void clickedMenu();
    void closedSelection();

    // BattleModel -> Game
    void finished();
    void closedBattle();

public:
    Game();

    void start();
};
