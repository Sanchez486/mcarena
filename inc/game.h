#pragma once

#include <QObject>

#include "inc/mainwindow.h"
#include "inc/menugui.h"
#include "inc/menumodel.h"
#include "inc/selectiongui.h"
#include "inc/selectionmodel.h"
#include "inc/battlegui.h"
#include "inc/battlemodel.h"

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
