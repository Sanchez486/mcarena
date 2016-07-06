#pragma once

#include <QObject>

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
    MenuGUI *menuGUI;
    MenuModel *menuModel;
    SelectionGUI *selectionGUI;
    SelectionModel *selectionModel;
    BattleGUI *battleGUI;
    BattleModel *battleModel;

public:
    Game();

    void start();
};
