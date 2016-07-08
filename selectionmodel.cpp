#include "inc/selectionmodel.h"
#include <iostream>

using namespace std;

SelectionModel::SelectionModel(QObject *parent)
    : QObject(parent)
{

}

void SelectionModel::clickedHero(HeroTemplate *)
{
    cerr << "SelectionModel::clickedHero(Hero *)" << endl;
}

void SelectionModel::clickedPlace()
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

void SelectionModel::clickedReady()
{
    cerr << "SelectionModel::clickedReady()" << endl;
    emit clickedReadySignal();
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
