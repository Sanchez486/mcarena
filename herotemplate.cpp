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
