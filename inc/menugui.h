#pragma once
#include "inc/mainwindow.h"

#include <QObject>
#include <QTimer>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFGUI/Box.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Label.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>

class MenuGUI : public QObject
{
Q_OBJECT
public:
    MenuGUI(MainWindow&, QObject *parent = nullptr);

private:
    QTimer *timer;

    MainWindow& app_window;
    sf::Texture backgroundT;
    sf::Sprite background;
    sf::Texture mcArenaT;
    sf::Sprite mcArena;


    sfg::SFGUI sfgui;
    sfg::Desktop desktop;

    //For main window
    sfg::Window::Ptr window;
    sfg::Box::Ptr box;
    sfg::Button::Ptr playButton;
    sfg::Button::Ptr rulesButton;
    sfg::Button::Ptr exitButton;
    sfg::Box::Ptr soundBox;
    sf::Image noSoundImage, soundImage,noMusicImage, musicImage;
    sfg::Image::Ptr soundToggle;
    sfg::Image::Ptr musicToggle;

    //How to play window
    sfg::Window::Ptr rulesWindow;
    sfg::Box::Ptr rulesBox;
    sfg::Label::Ptr rules;
    sfg::Button::Ptr okButton;

    sf::String str;

    //for signals
    enum ButtonPressed
    {
        PLAY,
        HOW_TO_PLAY,
        OK,
        EXIT,
        SOUND,
        MUSIC
    };

    //sfgui button signals
    void clickedButton(ButtonPressed Button);

    //Additional function
    void setLabel();

private slots:
    void update();

signals:
    void clickedPlay();
    void clickedPlayOnline();
    void clickedPlayCPU();
    void clickedExit();
    void clickedSound();  // Button sounds on/off
    void clickedMusic();  // Button music on/off
    void closed();  // After closing window

public slots:
    void show();  // Show this window
    void hide();  // Hide this window
    void setSounds(bool);  // Change sounds icon on/off
    void setMusic(bool);  // Change music icon on/off
};
