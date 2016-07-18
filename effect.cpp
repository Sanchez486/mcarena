#include "inc/effect.h"

Effect::Effect(int _duration, bool _removeOnTurn)
    : duration(_duration),
      removeOnTurn(_removeOnTurn)
{

}

int Effect::updateDuration()
{
    return --duration;
}

bool Effect::isRemoveOnTurn() const
{
    return removeOnTurn;
}

void Effect::onAdd(Hero *hero)
{

}

void Effect::onRemove(Hero *hero)
{

}

bool Effect::onTurn(Hero *hero)
{
    return false;
}
