#include "inc/herotemplate.h"

HeroTemplate::HeroTemplate()
    : stats(nullptr), resources(nullptr)
{

}

HeroTemplate::~HeroTemplate()
{
    if(stats != nullptr)
    {
        delete stats;
    }

    if(resources != nullptr)
    {
        delete resources;
    }
}

Stats& HeroTemplate::getStats()
{
    return *stats;
}

Resources& HeroTemplate::getResources()
{
    return *resources;
}

void HeroTemplate::setStats(const Stats &_stats)
{
    if(stats != nullptr)
    {
        delete stats;
    }

    stats = new Stats(_stats);
}

void HeroTemplate::setResources(const Resources &_resources)
{
    if(resources != nullptr)
    {
        delete resources;
    }

    resources = new Resources(_resources);
}
