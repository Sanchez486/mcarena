#pragma once

#include "action.h"

class Actions
{
private:
    Action *attack;
    Action *skill;

public:
    Actions();
    Actions(const Actions &actions);

    void setAttack(Action *action);
    void setSkill(Action *action);
    Action* getAttack();
    Action* getSkill();
};
