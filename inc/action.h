#pragma once

#include "player.h"
#include "targets.h"

class Action
{
private:
    Player *player1;
    Player *player2;
    Hero *sender;
    Hero *target;

public:
    Action();

    virtual Action* clone();  // return new Action(*this);

    void setPlayers(Player *_player1, Player *_player2);
    void setSender(Hero *_sender);
    void setTarget(Hero *_target);

    Hero* getSender();
    virtual Targets getAvaliableTargetsPlayer1();  // After setSender()
    virtual Targets getAvaliableTargetsPlayer2();  // After setSender()
    virtual Targets getTargetsPlayer1();  // After setTarget()
    virtual Targets getTargetsPlayer2();  // After setTarget()

    virtual void doAction();
};
