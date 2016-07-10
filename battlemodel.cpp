#include "inc/battlemodel.h"
#include <iostream>

using namespace std;

BattleModel::BattleModel(QObject *parent)
    : QObject(parent)
{

}

void BattleModel::selectedAction(Action *)
{
    cerr << "BattleModel::selectedAction(Action *)" << endl;
}

void BattleModel::selectedTarget(Hero *)
{
    cerr << "BattleModel::selectedTarget(Hero *)" << endl;
}

void BattleModel::closed()
{
    cerr << "BattleModel::closed()" << endl;
    emit closedSignal();
}

void BattleModel::beginBattle(Player *_player1, Player *_player2)
{
    player1 = _player1;
    player2 = _player2;

    emit show();
}

void BattleModel::hideGUI()
{
    emit hide();
}
