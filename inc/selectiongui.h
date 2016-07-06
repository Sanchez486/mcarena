#pragma once
#include <QObject>
#include <QTimer>
#include "hero.h"
#include "herogroup.h"
#include "player.h"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFGUI/Box.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Window.hpp>
#include <SFML/Graphics.hpp>

class SelectionGUI : public QObject
{
Q_OBJECT
public:
    SelectionGUI();
private:
    QTimer *timer;

    sf::RenderWindow app_window;
    sf::Texture backgroundT;
    sf::Sprite background;
    sfg::SFGUI sfgui;
    sfg::Desktop desktop;

    //Boxes
    sfg::Window::Ptr infoWindow;
    sfg::Box::Ptr infoBox;
    sfg::Window::Ptr pointsWindow;
    sfg::Box::Ptr pointsBox;
    sfg::Window::Ptr fieldWindow;
    sfg::Box::Ptr fieldBox;

    //Heroes list
    sfg::Window::Ptr scrollwin;
    sfg::Box::Ptr scrollwinbox;
    sfg::ScrolledWindow::Ptr scroll;
    sfg::Table::Ptr table;
    sfg::Box::Ptr tablebox;

    //For main bar
    sfg::Window::Ptr buttonsWindow;
    sfg::Box::Ptr buttonsBox;
    sfg::Button::Ptr menuButton;
    sfg::Button::Ptr discardButton;
    sfg::Button::Ptr startButton;

    //For players choice
    sfg::Window::Ptr playerWindow;
    sfg::Box::Ptr playerBox;
    sfg::Button::Ptr player1Button;
    sfg::Button::Ptr player2Button;


    //for signals
    enum ButtonPressed
    {
        MENU,
        DISCARD,
        START,
        PLAYER1,
        PLAYER2
    };

    //sfgui button signals

    void clickedButton(ButtonPressed Button);


signals:
    void clickedHero(Hero*);  // After hero clicked (on the left)
    void clickedPlace(/* position */);  // After empty seat clicked
    void clickedCross(Hero*);  // After cross clicked on seat
    void clickedDiscard();
    void clickedReady();
    void clickedMenu();
    void clickedPlayer1();
    void clickedPlayer2();
    void mouseOnSeat(/* position */);  // After mouse moved on hero (show cross)  [this -> this]

public slots:
    void update();
    void show();  // Show this window
    void hide();  // Hide this window
    void setActiveHero(Hero*);  // Change current hero
    void setHeroGroup(HeroGroup*);  // Change current group
    void setCost(/* cost */); // Change cost amount: 'curr/max'
    void setPlayer(Player*);  // Change buttons 'Player1' and 'Player2'
    void showCross(/* position */);  // Show cross on seat  [this -> this]
};
