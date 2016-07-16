#pragma once
#include <SFML/Window.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <QTimer>
#include <QObject>


class MainWindow: public sf::RenderWindow
{
private:
    QTimer* timer;
    const int XSIZE = 800;
    const int YSIZE = 600;
    sf::Music theme;
    bool soundToggle;
    sf::SoundBuffer buttonBuffer;
    sf::Sound buttonSound;
public:
    MainWindow();
    ~MainWindow();
    QTimer* getTimer();
    int getX();
    int getY();
    bool ToggleMusic();
    bool isSound();
    void setSound(bool);
    void playButtonSound();
};
