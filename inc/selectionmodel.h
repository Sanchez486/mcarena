#pragma once
#include <QObject>
#include "hero.h"
#include "herogroup.h"
#include "player.h"

class SelectionModel : public QObject
{
Q_OBJECT
private:

signals:
    // SelectionModel -> SelectionGUI
    void show();  // Show GUI window
    void hide();  // Hide GUI window
    void setHeroVector(const std::vector<HeroTemplate*>&);  // Change current list of heroes
    void setActiveHero(HeroTemplate*);  // Change current hero
    void setHeroGroup(HeroGroup*);  // Change current group
    void setCost(/* cost */); // Change cost amount: 'curr/max'
    void setPlayer(Player*);  // Change buttons 'Player1' and 'Player2'

    // SelectionModel -> Game
    void clickedReadySignal();
    void clickedMenuSignal();
    void closedSignal();

public slots:
    void clickedHero(HeroTemplate*);  // After hero clicked (on the left)
    void clickedPlace(/* position */);  // After empty seat clicked
    void clickedCross(Hero*);  // After cross clicked on seat
    void clickedDiscard();
    void clickedReady();
    void clickedMenu();
    void clickedPlayer1();
    void clickedPlayer2();
    void closed();

public:
    SelectionModel(QObject *parent = nullptr);
};
