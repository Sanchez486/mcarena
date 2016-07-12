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

    //Info
    sfg::Window::Ptr infoWindow;
    sfg::Box::Ptr infoBox;
    sfg::Table::Ptr infoTable;
    sfg::Window::Ptr pointsWindow;
    sfg::Box::Ptr pointsBox;
    sfg::Label::Ptr pointsLabel;
    sfg::Window::Ptr infoLabelWindow;
    sfg::Label::Ptr label;

    sfg::Image::Ptr infoPic;
    sfg::Image::Ptr pendingImage, pendingImage2;

    sfg::Label::Ptr infoLabels[7];
    sfg::Image::Ptr infoPics[5];

    HeroGroup heroesGroup;
    int activeHeroNumber;

    //Left heroes list
    sfg::Window::Ptr scrollwin;
    sfg::Box::Ptr scrollwinbox;
    sfg::ScrolledWindow::Ptr scroll;
    sfg::Table::Ptr table;
    sfg::Box::Ptr tablebox;

    //Central heroes pick list
    sfg::Window::Ptr fieldWindow;
    sfg::Box::Ptr fieldBox;
    sfg::Table::Ptr fieldTable;

    HeroVector* heroesList;

    sf::Image plusImg;
    sfg::Image::Ptr imageArray[6];
    sf::Image crossImg;
    sfg::Image::Ptr crossImageArray[6];

    //Buttons
    sfg::Window::Ptr buttonsWindow;
    sfg::Box::Ptr buttonsBox;
    sfg::Button::Ptr menuButton;
    sfg::Button::Ptr discardButton;
    sfg::Button::Ptr startButton;

    sfg::Window::Ptr playerWindow;
    sfg::Box::Ptr playerBox;
    sfg::Button::Ptr player1Button, player2Button;

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

    enum Image
    {
        DEFAULT,
        NORMAL
    };

    Image imageType[6];

    //Additional functions
    void setHeroImage(Hero* hero, Hero *myhero, int pos);
    void connectSignals(int pos);

    //sfgui widget signals
    void _clickedHero(int i);
    void _clickedPlace(HeroPosition pos, int i);
    void _clickedCross(HeroPosition pos, int i);
    void clickedButton(ButtonPressed Button);
    void mouseEvent(Mouse mouse, int i);

signals:
    void clickedHero(HeroTemplate *hero);  // After hero clicked (on the left)
    void clickedPlace(HeroPosition pos);  // After empty seat clicked
    void clickedCross(HeroPosition pos);  // After cross clicked on seat
    void clickedDiscard();
    void clickedStart();
    void clickedMenu();
    void clickedPlayer1();
    void clickedPlayer2();
    void closed();  // After closing window

private slots:
    void update();

public slots:
    void show();  // Show this window
    void hide();  // Hide this window
    void setHeroVector(HeroVector *heroVector);  // Change current list of heroes
    void setActiveHero(HeroTemplate *hero);  // Change current hero
    void setHeroGroup(HeroGroup *heroGroup);  // Change current group
    void setCost(Cost *cost); // Change cost amount: 'curr/max'
};
