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

const HeroTemplate *Hero::getTemplate() const
{
    return heroTemplate;
}

Action* Hero::getAttack()
{
    return stats->actions.getAttack();
}

Action* Hero::getSkill()
{
    return stats->actions.getSkill();
}
