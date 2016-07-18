#include "inc/menumodel.h"
#include <iostream>

using namespace std;

MenuModel::MenuModel(QObject *parent)
    : QObject(parent)
{

}

void MenuModel::clickedPlay()
{
    emit clickedPlaySignal();
}

void MenuModel::clickedPlayOnline()
{
    emit clickedPlayOnlineSignal();
}

void MenuModel::clickedPlayCPU()
{
    emit clickedPlayCPUSignal();
}

void MenuModel::clickedExit()
{
    emit clickedExitSignal();
}

void MenuModel::clickedSound()
{
    cerr << "MenuModel::clickedSound()" << endl;
}

void MenuModel::clickedMusic()
{
    cerr << "MenuModel::clickedMusic()" << endl;
}

void MenuModel::closed()
{
    emit closedSignal();
}

void MenuModel::showGUI()
{
    emit show();
}

void MenuModel::hideGUI()
{
    emit hide();
}
