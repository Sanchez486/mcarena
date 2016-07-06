#pragma once

#include <QObject>
#include <QTimer>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFGUI/Box.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Window.hpp>
#include <SFML/Graphics.hpp>

class MenuGUI : public QObject
{
Q_OBJECT
public:
    MenuGUI();

private:
    QTimer *timer;

    sf::RenderWindow app_window;
    sfg::SFGUI sfgui;
    sfg::Desktop desktop;

    //For main window
    sfg::Window::Ptr window;
    sfg::Box::Ptr box;
    sfg::Button::Ptr playButton;
    sfg::Button::Ptr playWithCpuButton;
    sfg::Button::Ptr settingsButton;
    sfg::Button::Ptr exitButton;

    //For settings window
    sfg::Window::Ptr settingsWindow;
    sfg::Box::Ptr sharedBox;
    sfg::Box::Ptr settingsBox;
    sfg::Box::Ptr okBox;
    sfg::Button::Ptr soundButton;
    sfg::Button::Ptr musicButton;
    sfg::Button::Ptr okButton;

    //for signals
    enum ButtonPressed
    {
        PLAY,
        PLAY_WITH_CPU,
        EXIT,
        SOUND,
        MUSIC
    };

    //sfgui button signals
    void clickedSettings();
    void clickedOk();
    void clickedButton(ButtonPressed Button);

private slots:


signals:
    void clickedPlay();
    void clickedPlayOnline();
    void clickedPlayCPU();
    void clickedExit();
    void clickedSound();  // Button sounds on/off
    void clickedMusic();  // Button music on/off

public slots:
    void update();// move to private slot
    void show();  // Show this window
    void hide();  // Hide this window
    void setSounds(bool);  // Change sounds icon on/off
    void setMusic(bool);  // Change music icon on/off
};
