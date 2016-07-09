#pragma once
#include <QObject>

#include "hero.h"
#include "herogroup.h"
#include "player.h"
#include "herovector.h"

class SelectionModel : public QObject
{
Q_OBJECT
private:
    HeroVector *heroes;
    Player *player1;
    Player *player2;
    HeroTemplate *activeHero;
    Player *activePlayer;

signals:
    // SelectionModel -> SelectionGUI
    void show();  // Show GUI window
    void hide();  // Hide GUI window
    void setHeroVector(HeroVector*);  // Change current list of heroes
    void setActiveHero(HeroTemplate*);  // Change current hero
    void setHeroGroup(HeroGroup*);  // Change current group
    void setCost(/* cost */); // Change cost amount: 'curr/max'
    void setPlayer(Player*);  // Change buttons 'Player1' and 'Player2'

    // SelectionModel -> Game
    void clickedStartSignal();
    void clickedMenuSignal();
    void closedSignal();

public slots:
    void clickedHero(HeroTemplate*);  // After hero clicked (on the left)
    void clickedPlace(HeroPosition);  // After empty seat clicked
    void clickedCross(Hero*);  // After cross clicked on seat
    void clickedDiscard();
    void clickedStart();
    void clickedMenu();
    void clickedPlayer1();
    void clickedPlayer2();
    void closed();

public:
    SelectionModel(QObject *parent = nullptr);

    void beginPlay(HeroVector *_heroes);
    void beginPlayOnline(HeroVector *_heroes);
    void beginPlayCPU(HeroVector *_heroes);
    void hideGUI();
};