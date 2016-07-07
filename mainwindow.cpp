#include "inc/mainwindow.h"

MainWindow::MainWindow() : RenderWindow()
{
    create(sf::VideoMode(XSIZE,YSIZE), "McArena", sf::Style::Titlebar | sf::Style::Close);
}

int MainWindow::getX()
{
    return XSIZE;
}

int MainWindow::getY()
{
    return YSIZE;
}


