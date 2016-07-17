#include "inc/mainwindow.h"

MainWindow::MainWindow() : RenderWindow()
{
    create(sf::VideoMode(XSIZE,YSIZE), "McArena", sf::Style::Titlebar | sf::Style::Close);
    timer = new QTimer();
    theme.openFromFile("res/sfx/theme.wav");
    theme.setLoop(true);
    ToggleMusic();
    setSound(true);
    if (buttonBuffer.loadFromFile("res/sfx/button.wav")) buttonSound.setBuffer(buttonBuffer);
    setImages();
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

void MainWindow::setImages()
{
    iconImage[0].loadFromFile("res/img/icons/near.png");
    iconImage[1].loadFromFile("res/img/icons/further.png");
    iconImage[2].loadFromFile("res/img/icons/element.png");
    iconImage[3].loadFromFile("res/img/icons/hp.png");
    iconImage[4].loadFromFile("res/img/icons/attack.png");
    iconImage[5].loadFromFile("res/img/icons/init.png");
}

sf::Image& MainWindow::getImage(int i)
{
        return iconImage[i];
}

sf::Image& MainWindow::getImageForBattle(int i)
{
    switch(i)
    {
        case 0:
            return iconImage[3];
        case 1:
            return iconImage[4];
        case 2:
            return iconImage[0];
        case 3:
            return iconImage[5];
        case 4:
            return iconImage[2];
        default:
            return iconImage[0];
    }
}
