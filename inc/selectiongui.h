#pragma once
#include <QObject>
#include <vector>

#include "hero.h"
#include "herogroup.h"
#include "player.h"

class SelectionGUI : public QObject
{
Q_OBJECT
public:
    SelectionGUI(QObject *parent = nullptr);

signals:
    void clickedHero(HeroTemplate*);  // After hero clicked (on the left)
    void clickedPlace(/* position */);  // After empty seat clicked
    void clickedCross(Hero*);  // After cross clicked on seat
    void clickedDiscard();
    void clickedReady();
    void clickedMenu();
    void clickedPlayer1();
    void clickedPlayer2();
    void closed();  // After closing window
    void mouseOnSeat(/* position */);  // After mouse moved on hero (show cross)  [this -> this]

public slots:
    void show();  // Show this window
    void hide();  // Hide this window
    void setHeroVector(const std::vector<HeroTemplate*>&);  // Change current list of heroes
    void setActiveHero(HeroTemplate*);  // Change current hero
    void setHeroGroup(HeroGroup*);  // Change current group
    void setCost(/* cost */); // Change cost amount: 'curr/max'
    void setPlayer(Player*);  // Change buttons 'Player1' and 'Player2'
    void showCross(/* position */);  // Show cross on seat  [this -> this]
};
