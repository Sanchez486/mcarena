#include "inc/actions.h"

Actions::Actions() : attack(nullptr), skill(nullptr)
{

}

Actions::Actions(const Actions &actions)
{
    if(actions.getAttack() == nullptr)
    {
        attack = nullptr;
    }
    else
    {
        attack = actions.getAttack()->clone();
    }

    if(actions.getSkill() == nullptr)
    {
        skill = nullptr;
    }
    else
    {
        skill = actions.getSkill()->clone();
    }
}

void Actions::setAttack(Action *action)
{
    if(attack != nullptr)
        delete attack;

    if(action == nullptr)
    {
        attack = nullptr;
    }
    else
    {
        attack = action->clone();
    }
}

void Actions::setSkill(Action *action)
{
    if(skill != nullptr)
        delete skill;

    if(action == nullptr)
    {
        skill = nullptr;
    }
    else
    {
        skill = action->clone();
    }
}

Action *Actions::getAttack()
{
    return attack;
}

Action *Actions::getSkill()
{
    return skill;
}
