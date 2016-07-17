#pragma once

#include "action.h"

class TransferHealth : public Action
{
private:
    Damage damage;

public:
    TransferHealth(const Damage &_damage);

    virtual Action* clone() const;

    virtual Targets getAvaliableTargetsPlayer1() const;  // After setSender()
    virtual Targets getAvaliableTargetsPlayer2() const;  // After setSender()
    virtual Targets getTargetsPlayer1() const;  // After setTarget()
    virtual Targets getTargetsPlayer2() const;  // After setTarget()

    virtual std::string getName() const;
    virtual std::string getDescription() const;

    virtual void doAction();
};
