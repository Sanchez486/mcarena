#include "inc/menumodel.h"
#include <iostream>

using namespace std;

MenuModel::MenuModel(QObject *parent)
    : QObject(parent)
{

}


void MenuModel::clickedPlay()
{
    cerr << "MenuModel::clickedPlay()" << endl;
}

void MenuModel::clickedPlayOnline()
{
    cerr << "MenuModel::clickedPlayOnline()" << endl;
}

void MenuModel::clickedPlayCPU()
{
    cerr << "MenuModel::clickedPlayCPU()" << endl;
}

void MenuModel::clickedExit()
{
    cerr << "MenuModel::clickedExit()" << endl;
}

void MenuModel::clickedSound()
{
    cerr << "MenuModel::clickedSound()" << endl;
}

void MenuModel::clickedMusic()
{
    cerr << "MenuModel::clickedMusic()" << endl;
}
