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

    void setStats(const Stats &_stats);
    void setResources(const Resources &_resources);
};
