#pragma once

#include "inc/stats.h"
#include "inc/resources.h"

class HeroTemplate
{
private:
    Stats *stats;
    Resources *resources;

public:
    HeroTemplate();
    ~HeroTemplate();

    Stats& getStats();
    Resources& getResources();
};
