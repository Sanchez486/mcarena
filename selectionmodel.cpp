#include "inc/selectionmodel.h"
#include <iostream>

using namespace std;

SelectionModel::SelectionModel(QObject *parent)
    : QObject(parent),
      heroes(nullptr),
      player1(nullptr),
      player2(nullptr),
      activeHero(nullptr),
      activePlayer(nullptr)
{

}

void SelectionModel::clickedHero(HeroTemplate *_hero)
{
    activeHero = _hero;
    emit setActiveHero(activeHero);
}

void SelectionModel::clickedPlace(HeroPosition pos)
{
    if(activeHero == nullptr)
        return;

    updateHero(pos, activeHero);
    emit setHeroGroup( &(activePlayer->getHeroGroup()) );

    activePlayer->updateCost();
    emit setCost( &(activePlayer->getCost()) );
}

void SelectionModel::clickedCross(HeroPosition pos)
{
    updateHero(pos, nullptr);
    emit setHeroGroup( &(activePlayer->getHeroGroup()) );

    activePlayer->updateCost();
    emit setCost( &(activePlayer->getCost()) );
}

void SelectionModel::clickedDiscard()
{
    updateHero(HeroPosition::front1, nullptr);
    updateHero(HeroPosition::front2, nullptr);
    updateHero(HeroPosition::front3, nullptr);
    updateHero(HeroPosition::back1, nullptr);
    updateHero(HeroPosition::back2, nullptr);
    updateHero(HeroPosition::back3, nullptr);
    emit setHeroGroup( &(activePlayer->getHeroGroup()) );

    activePlayer->updateCost();
    emit setCost( &(activePlayer->getCost()) );
}

void SelectionModel::updateHero(HeroPosition pos, HeroTemplate *templ)
{
    Hero* oldHero = activePlayer->getHeroGroup().at(pos);
    if(oldHero != nullptr)
        delete oldHero;

    if(templ == nullptr)
    {
        activePlayer->getHeroGroup().set(pos, nullptr);
    }
    else
    {
        activePlayer->getHeroGroup().set(pos, new Hero(templ));
    }
}

// TODO
void SelectionModel::clickedStart()
{
    cerr << "SelectionModel::clickedStart()" << endl;
    emit clickedStartSignal();
}

void SelectionModel::clickedMenu()
{
    emit clickedMenuSignal();
}

void SelectionModel::clickedPlayer1()
{
    activePlayer = player1;
    emit setHeroGroup( &(activePlayer->getHeroGroup()) );
}

void SelectionModel::clickedPlayer2()
{
    activePlayer = player2;
    emit setHeroGroup( &(activePlayer->getHeroGroup()) );
}

void SelectionModel::closed()
{
    emit closedSignal();
}

void SelectionModel::beginPlay(HeroVector *_heroes)
{
    heroes = _heroes;

    if(player1 != nullptr)
    {
        delete player1;
    }
    player1 = new Player();
    player1->setMaxCost(99);

    if(player2 != nullptr)
    {
        delete player2;
    }
    player2 = new Player();
    player2->setMaxCost(99);

    activePlayer = player1;
    activeHero = nullptr;

    emit show();
    emit setHeroVector(heroes);
    emit setActiveHero(activeHero);
    emit setHeroGroup( &(activePlayer->getHeroGroup()) );
}

// TODO
void SelectionModel::beginPlayOnline(HeroVector *_heroes)
{
    emit show();
}

// TODO
void SelectionModel::beginPlayCPU(HeroVector *_heroes)
{
    heroes = _heroes;

    if(player1 != nullptr)
    {
        delete player1;
    }
    player1 = new Player();
    player1->setMaxCost(99);

    if(player2 != nullptr)
    {
        delete player2;
    }
    player2 = new Player();
    player2->setMaxCost(99);

    activePlayer = player1;
    activeHero = nullptr;

    emit show();
    emit setHeroVector(heroes);
    emit setActiveHero(activeHero);
    emit setHeroGroup( &(activePlayer->getHeroGroup()) );
}

void SelectionModel::hideGUI()
{
    emit hide();
}
