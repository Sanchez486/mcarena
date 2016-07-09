#pragma once
#include <QObject>
#include <QTimer>

#include "hero.h"
#include "herogroup.h"
#include "herovector.h"
#include "player.h"
#include "mainwindow.h"

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
    SelectionGUI(MainWindow&, QObject *parent = nullptr);
private:
    QTimer *timer;

    MainWindow& app_window;
    sf::Texture backgroundT;
    sf::Sprite background;
    sfg::SFGUI sfgui;
    sfg::Desktop desktop;

    //Boxes
    sfg::Window::Ptr infoWindow;
    sfg::Box::Ptr infoBox;
    sfg::Table::Ptr infoTable;
    sfg::Window::Ptr pointsWindow;
    sfg::Box::Ptr pointsBox;
    sfg::Label::Ptr pointsLabel;
    sfg::Window::Ptr fieldWindow;
    sfg::Box::Ptr fieldBox;
    sfg::Table::Ptr fieldTable;

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
        START,
        DISCARD,
        MENU,
        PLAYER1,
        PLAYER2
    };

    //sfgui button signals

    void clickedButton(ButtonPressed Button);


private:

signals:
    void clickedHero(HeroTemplate*);  // After hero clicked (on the left)
    void clickedPlace(HeroPosition);  // After empty seat clicked
    void clickedCross(HeroPosition);  // After cross clicked on seat
    void clickedDiscard();
    void clickedStart();
    void clickedMenu();
    void clickedPlayer1();
    void clickedPlayer2();
    void closed();  // After closing window
    void mouseOnSeat(HeroPosition);  // After mouse moved on hero (show cross)  [this -> this]

private slots:
    void update();

public slots:
    void show();  // Show this window
    void hide();  // Hide this window
    void setHeroVector(HeroVector*);  // Change current list of heroes
    void setActiveHero(HeroTemplate*);  // Change current hero
    void setHeroGroup(HeroGroup*);  // Change current group
    void setCost(Cost*); // Change cost amount: 'curr/max'
    void showCross(HeroPosition);  // Show cross on seat  [this -> this]
};
