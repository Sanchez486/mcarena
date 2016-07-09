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

void SelectionModel::clickedHero(HeroTemplate *)
{
    cerr << "SelectionModel::clickedHero(Hero *)" << endl;
}

void SelectionModel::clickedPlace(HeroPosition)
{
    cerr << "SelectionModel::clickedPlace()" << endl;
}

void SelectionModel::clickedCross(Hero *)
{
    cerr << "SelectionModel::clickedCross(Hero *)" << endl;
}

void SelectionModel::clickedDiscard()
{
    cerr << "SelectionModel::clickedDiscard()" << endl;
}

void SelectionModel::clickedStart()
{
    cerr << "SelectionModel::clickedStart()" << endl;
    emit clickedStartSignal();
}

void SelectionModel::clickedMenu()
{
    cerr << "SelectionModel::clickedMenu()" << endl;
    emit clickedMenuSignal();
}

void SelectionModel::clickedPlayer1()
{
    cerr << "SelectionModel::clickedPlayer1()" << endl;
}

void SelectionModel::clickedPlayer2()
{
    cerr << "SelectionModel::clickedPlayer2()" << endl;
}

void SelectionModel::closed()
{
    cerr << "SelectionModel::closed()" << endl;
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

    if(player2 != nullptr)
    {
        delete player2;
    }
    player2 = new Player();

    activePlayer = player1;
    activeHero = nullptr;

    emit show();
    emit setHeroVector(heroes);
    emit setActiveHero(activeHero);
    emit setHeroGroup( &(activePlayer->getHeroGroup()) );
}

void SelectionModel::beginPlayOnline(HeroVector *_heroes)
{
    emit show();
}

void SelectionModel::beginPlayCPU(HeroVector *_heroes)
{
    emit show();
}

void SelectionModel::hideGUI()
{
    emit hide();
}
