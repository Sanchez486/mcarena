#include "inc/mainwindow.h"

MainWindow::MainWindow() : RenderWindow()
{
    create(sf::VideoMode(XSIZE,YSIZE), "McArena", sf::Style::Titlebar | sf::Style::Close);
    timer = new QTimer();
    theme.openFromFile("res/sfx/theme.wav");
    theme.setLoop(true);
    theme.setVolume(40);
    ToggleMusic();
    setSound(true);
    if (buttonBuffer.loadFromFile("res/sfx/button.wav")) buttonSound.setBuffer(buttonBuffer);
}

MainWindow::~MainWindow()
{
    delete timer;
}

int MainWindow::getX()
{
    return XSIZE;
}

int MainWindow::getY()
{
    return YSIZE;
}

QTimer* MainWindow::getTimer()
{
    return timer;
}

bool MainWindow::ToggleMusic()
{
    if (theme.getStatus()==sf::Sound::Playing) theme.pause();
    else theme.play();
    if (theme.getStatus()==sf::Music::Status::Playing) return true;
    else return false;
}


bool MainWindow::isSound()
{
    return soundToggle;
}

void MainWindow::setSound(bool state)
{
    soundToggle = state;
}

void MainWindow::playButtonSound()
{
    if (isSound()) buttonSound.play();
}
