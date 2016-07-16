#pragma once
#include <QObject>
#include <QTimer>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFGUI/Box.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Frame.hpp>
#include <SFGUI/Image.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFGUI/Label.hpp>

#include "mainwindow.h"
#include "hero.h"
#include "heroqueue.h"
#include "action.h"
#include "spritesfield.h"
#include "targets.h"

class SpritesField;

class BattleGUI : public QObject
{
Q_OBJECT
public:
    BattleGUI(MainWindow& , QObject *parent = nullptr);
    ~BattleGUI();

private:
    QTimer *timer;
    
    sfg::SFGUI sfgui;
    sfg::Desktop desktop;


    MainWindow& app_window;
    
    sf::Texture backgroundT;
    sf::Sprite background;

    //Main windows
    sfg::Window::Ptr queueWindow;
    sfg::Window::Ptr buttonWindow;
    sfg::Window::Ptr infoWindow;

    //Queue window
    sfg::Box::Ptr queueSBox;
    sfg::ScrolledWindow::Ptr qScroll;
    sfg::Box::Ptr queueBox;

    sfg::Image::Ptr queueImages[12];

    Hero *activeHero;

    //ButtonWindow
    sfg::Box::Ptr buttonBox;
    sfg::Button::Ptr attackButton;
    sfg::Button::Ptr skillButton;
    sfg::Button::Ptr skipButton;
    sfg::Button::Ptr menuButton;

    //InfoWindow
    sfg::Box::Ptr infoBox;
    sfg::Box::Ptr skillsBox;
    sfg::Box::Ptr picBox;
    sfg::Box::Ptr labelBox;

    sfg::Label::Ptr stats[6];

    sfg::Frame::Ptr frame;
    sfg::Image::Ptr infoImage;

    //Sprite window

    SpritesField* spritesField;

    //Finish window
    sfg::Window::Ptr finishWindow;
    sfg::Box::Ptr finishBox;
    sfg::Button::Ptr menuButton2;
    sfg::Label::Ptr winnerLabel;

    //for signals
    enum ButtonPressed
    {
        ATTACK,
        SKILL
    };

    void clickedButton(ButtonPressed Button);

    //Pop window
    sfg::Window::Ptr popWindow;
    sfg::Box::Ptr popBox;
    sfg::Box::Ptr popSkillsBox;
    sfg::Box::Ptr popPicBox;
    sfg::Box::Ptr popLabelBox;
    sfg::Label::Ptr popStats[6];

    //Additional functions
    void completeStats(sfg::Label::Ptr* array, Hero *hero);
    sf::FloatRect setPopWindowPosition(sf::Vector2i mousePos);

    //For SFGUI signals
public:
    void showInfo(Hero *hero);

signals:
    void selectedAction(Action*);  // After attack or skill clicked
    void selectedTarget(Hero*);  // After Hero clicked
    void beginTurn();
    void finished();
    void closed();

public slots:
    void show();  // Show this window
    void hide();  // Hide this window
    void setPlayers(Player *player1, Player *player2);
    void setActiveHero(Hero *hero);  // Change current hero
    void setQueue(HeroQueue* queue);  // Change queue
    void showTargets(Action*);  // Highlight avaliable targets
    void playAction(Action*);  // Play animation/sounds, show numbers
    void showDead(Hero*);  // Show death animation
    void winPlayer1();  // Show final window
    void winPlayer2();  // Show final window

private slots:
    void update();
};
