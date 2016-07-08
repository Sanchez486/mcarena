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

QTimer* MainWindow::newTimer()
{
    timer = new QTimer();
    return timer;
}

void MainWindow::deleteTimer()
{
    delete timer;
}

