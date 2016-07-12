#include "inc/herotemplate.h"

HeroTemplate::HeroTemplate()
    : stats(nullptr), resources(nullptr), name()
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

const std::string &HeroTemplate::getName() const
{
    return name;
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

void HeroTemplate::setName(const std::string &_name)
{
    name = _name;
}
