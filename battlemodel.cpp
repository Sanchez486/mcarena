#include "inc/battlemodel.h"
#include <iostream>

using namespace std;

BattleModel::BattleModel(QObject *parent)
    : QObject(parent),
      heroQueue()
{

}

void BattleModel::selectedAction(Action *_action)
{
    action = _action;
    emit showTargets(action);
}

void BattleModel::selectedTarget(Hero *target)
{
    action->setTarget(target);
    action->doAction();
    emit playAction(action);

    heroQueue.rotate();
    emit setQueue(&heroQueue);
    emit setActiveHero(heroQueue.first());
}

void BattleModel::closed()
{
    emit closedSignal();
}

void BattleModel::beginBattle(Player *_player1, Player *_player2)
{
    player1 = _player1;
    player2 = _player2;

    heroQueue.setHeroes(player1->getHeroGroup(), player2->getHeroGroup());

    emit show();
    emit setPlayers(player1, player2);
    emit setQueue(&heroQueue);
    emit setActiveHero(heroQueue.first());
}

void BattleModel::hideGUI()
{
    emit hide();
}
