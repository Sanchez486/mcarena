#pragma once

#include "stats.h"
#include "resources.h"

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
