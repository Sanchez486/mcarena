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
    emit clickedPlaySignal();
}

void MenuModel::clickedPlayOnline()
{
    cerr << "MenuModel::clickedPlayOnline()" << endl;
    emit clickedPlayOnlineSignal();
}

void MenuModel::clickedPlayCPU()
{
    cerr << "MenuModel::clickedPlayCPU()" << endl;
    emit clickedPlayCPUSignal();
}

void MenuModel::clickedExit()
{
    cerr << "MenuModel::clickedExit()" << endl;
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
    cerr << "MenuModel::closed()" << endl;
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
