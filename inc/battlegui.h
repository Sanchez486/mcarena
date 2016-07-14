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
#include <SFGUI/Separator.hpp>
#include <SFGUI/Label.hpp>

#include "mainwindow.h"
#include "hero.h"
#include "heroqueue.h"
#include "action.h"
#include "spritesfield.h"

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

    sfg::Image::Ptr image;

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
    sfg::Separator::Ptr separator;

    //ButtonWindow
    sfg::Box::Ptr buttonBox;
    sfg::Button::Ptr attackButton;
    sfg::Button::Ptr skillButton;

    //InfoWindow
    sfg::Box::Ptr infoBox;
    sfg::Box::Ptr skillsBox;
    sfg::Box::Ptr picBox;
    sfg::Box::Ptr labelBox;

    sfg::Label::Ptr hp;
    sfg::Label::Ptr dmg;
    sfg::Label::Ptr init;
    sfg::Label::Ptr element;

    sfg::Frame::Ptr frame;

    //Sprite window

    SpritesField* spritesField;

    //for signals
    enum ButtonPressed
    {
        ATTACK,
        SKILL
    };

    void clickedButton(ButtonPressed Button);

signals:
    void selectedAction(Action*);  // After attack or skill clicked
    void selectedTarget(Hero*);  // After Hero clicked
    void showInfoSignal(Hero*);  // After right-click on Hero  [this -> this]
    void closed();

public slots:
    void show();  // Show this window
    void hide();  // Hide this window
    void setPlayers(Player *player1, Player *player2);
    void setActiveHero(Hero*);  // Change current hero
    void setQueue(HeroQueue*);  // Change queue
    void showInfo(Hero*);  // Show info about Hero  [this -> this]
    void showTargets(Action*);  // Highlight avaliable targets
    void playAction(Action*);  // Play animation/sounds, show numbers

private slots:
    void update();
};
