#include "inc/hero.h"

Hero::Hero(HeroTemplate *_templ) : heroTemplate(_templ)
{
    if(heroTemplate != nullptr)
    {
        stats = new Stats(heroTemplate->getStats());
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
