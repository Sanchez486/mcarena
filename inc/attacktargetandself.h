#pragma once

#include "action.h"

class AttackTargetAndSelf : public Action
{
private:
    Damage damageTarget;
    Damage damageSelf;

public:
    AttackTargetAndSelf(const Damage &_damageTarget, const Damage &_damageSelf);

    virtual Action* clone() const;

    virtual Targets getAvaliableTargetsPlayer1() const;  // After setSender()
    virtual Targets getAvaliableTargetsPlayer2() const;  // After setSender()
    virtual Targets getTargetsPlayer1() const;  // After setTarget()
    virtual Targets getTargetsPlayer2() const;  // After setTarget()

    virtual const std::string& getName() const;
    virtual const std::string& getDescription() const;

    virtual void doAction();
};
