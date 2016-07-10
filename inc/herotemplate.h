#pragma once

#include <string>

#include "stats.h"
#include "resources.h"

class HeroTemplate
{
private:
    Stats *stats;
    Resources *resources;
    std::string name;

public:
    HeroTemplate();
    ~HeroTemplate();

    Stats& getStats();
    Resources& getResources();
    const std::string& getName() const;

    void setStats(const Stats &_stats);
    void setResources(const Resources &_resources);
    void setName(const std::string &_name);
};
