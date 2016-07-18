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

    sf::Image iconImage[6];
    /*
     * 0 == melee
     * 1 == range
     * 2 == element
     * 3 == hp
     * 4 == dmg
     * 5 == init
     */
     void setImages();

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
    sf::Image& getImage(int i);
    sf::Image& getImageForBattle(int i);
};
