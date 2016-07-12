#include "inc/action.h"
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

Actions::~Actions()
{
    if(attack != nullptr)
        delete attack;

    if(skill != nullptr)
        delete skill;
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

Action *Actions::getAttack() const
{
    return attack;
}

Action *Actions::getSkill() const
{
    return skill;
}

void Actions::setPlayers(Player *player1, Player *player2)
{
    if(attack != nullptr)
    {
        attack->setPlayers(player1, player2);
    }

    if(skill != nullptr)
    {
        skill->setPlayers(player1, player2);
    }
}

void Actions::setSender(Hero *sender)
{
    if(attack != nullptr)
    {
        attack->setSender(sender);
    }

    if(skill != nullptr)
    {
        skill->setSender(sender);
    }
}
