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
}

void BattleModel::finished()
{
    emit finishedSignal();
}

void BattleModel::beginTurn()
{
    if(player1->countAlive() == 0)
    {
        emit winPlayer2();
        return;
    }
    if(player2->countAlive() == 0)
    {
        emit winPlayer1();
        return;
    }

    updateDead();

    heroQueue.rotate();
    emit setQueue(&heroQueue);
    emit setActiveHero(heroQueue.first());
}

void BattleModel::updateDead()
{
    updateDead(player1, HeroPosition::front1);
    updateDead(player1, HeroPosition::front2);
    updateDead(player1, HeroPosition::front3);
    updateDead(player1, HeroPosition::back1);
    updateDead(player1, HeroPosition::back2);
    updateDead(player1, HeroPosition::back3);

    updateDead(player2, HeroPosition::front1);
    updateDead(player2, HeroPosition::front2);
    updateDead(player2, HeroPosition::front3);
    updateDead(player2, HeroPosition::back1);
    updateDead(player2, HeroPosition::back2);
    updateDead(player2, HeroPosition::back3);
}

void BattleModel::updateDead(Player *player, HeroPosition pos)
{
    if(player->at(pos)->updateDead())
        emit showDead(player->at(pos));
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
