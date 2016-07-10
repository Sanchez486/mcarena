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
    sfg::Window::Ptr infoLabelWindow;

    //Heroes list
    sfg::Window::Ptr scrollwin;
    sfg::Box::Ptr scrollwinbox;
    sfg::ScrolledWindow::Ptr scroll;
    sfg::Table::Ptr table;
    sfg::Box::Ptr tablebox;

    HeroVector* heroesList;
    int activeHeroNumber;
    sfg::Image::Ptr pendingImage, pendingImage2;

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

    HeroGroup heroesGroup;

    //For info
    sfg::Label::Ptr infoLabels[7];
    sfg::Image::Ptr infoPics[5];
    sfg::Label::Ptr label;
    sfg::Image::Ptr defaultImage[6];
    sfg::Image::Ptr normImage[6];


    //for signals
    enum ButtonPressed
    {
        START,
        DISCARD,
        MENU,
        PLAYER1,
        PLAYER2
    };

    enum Mouse
    {
        ENTER,
        LEAVE
    };

    //sfgui widget signals

    void clickedButton(ButtonPressed Button);
    void heroChosen(int i);
    void clickedPlus(HeroPosition pos);
    void mouseEvent(Mouse mouse);

    //Additional functions
    void setHeroImage(Hero* hero, Hero *myhero, int pos);
    void signalSetting(int i);

signals:
    void clickedHero(HeroTemplate *hero);  // After hero clicked (on the left)
    void clickedPlace(HeroPosition pos);  // After empty seat clicked
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
    void setHeroVector(HeroVector *heroVector);  // Change current list of heroes
    void setActiveHero(HeroTemplate *hero);  // Change current hero
    void setHeroGroup(HeroGroup*);  // Change current group
    void setCost(/* cost */); // Change cost amount: 'curr/max'
    void showCross(HeroPosition);  // Show cross on seat  [this -> this]
};
