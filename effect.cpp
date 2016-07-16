#include "inc/effect.h"

Effect::Effect(int _duration) : duration(_duration)
{

}

int Effect::updateDuration()
{
    return --duration;
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
