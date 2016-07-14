#pragma once

#include "action.h"

class AttackWithChance : public Action
{
private:
    Damage damage;
    double chance;

public:
    AttackWithChance(const Damage &_damage, double _chance);

    virtual Action* clone() const;

    virtual Targets getAvaliableTargetsPlayer1() const;  // After setSender()
    virtual Targets getAvaliableTargetsPlayer2() const;  // After setSender()
    virtual Targets getTargetsPlayer1() const;  // After setTarget()
    virtual Targets getTargetsPlayer2() const;  // After setTarget()

    virtual const std::string& getName() const;
    virtual const std::string& getDescription() const;

    virtual void doAction();
};

