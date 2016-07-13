#pragma once

#include <string>

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
    virtual ~Action();

    virtual Action* clone() const;  // return new Action(*this);

    void setPlayers(Player *_player1, Player *_player2);
    void setSender(Hero *_sender);
    void setTarget(Hero *_target);

    Hero* getSender() const;
    virtual Targets getAvaliableTargetsPlayer1() const;  // After setSender()
    virtual Targets getAvaliableTargetsPlayer2() const;  // After setSender()
    virtual Targets getTargetsPlayer1() const;  // After setTarget()
    virtual Targets getTargetsPlayer2() const;  // After setTarget()

    virtual const std::string& getName() const;
    virtual const std::string& getDescription() const;

    virtual void doAction();
};
