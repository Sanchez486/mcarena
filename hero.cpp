#include "inc/hero.h"

Hero::Hero(HeroTemplate *_templ) : heroTemplate(_templ)
{
    if(heroTemplate != nullptr)
    {
        stats = new Stats(heroTemplate->getStats());
        stats->actions.setSender(this);
    }
    else
    {
        stats = nullptr;
    }
}

Hero::~Hero()
{
    if(stats != nullptr)
    {
        delete stats;
    }
}

Stats& Hero::getStats()
{
    return *stats;
}

Stats& Hero::getTemplateStats()
{
    return heroTemplate->getStats();
}

Resources& Hero::getResources()
{
    return heroTemplate->getResources();
}

HeroTemplate *Hero::getTemplate() const
{
    return heroTemplate;
}

Action* Hero::getAttack() const
{
    return stats->actions.getAttack();
}

Action* Hero::getSkill() const
{
    return stats->actions.getSkill();
}

bool Hero::isAlive() const
{
    return stats->hp.curr > 0;
}

bool Hero::updateDead()
{
    if(showedDead == true)
    {
        return false;
    }

    return showedDead = !isAlive();
}
