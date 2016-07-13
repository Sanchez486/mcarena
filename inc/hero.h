#pragma once

#include "herotemplate.h"

class Hero
{
private:
    HeroTemplate *heroTemplate;
    Stats *stats;

public:
    Hero(HeroTemplate *_templ = nullptr);
    ~Hero();

    Stats& getStats();  // return stats
    Stats& getTemplateStats();  // return heroTemplate->getStats
    Resources& getResources();

    Action* getAttack();
    Action* getSkill();
};

#include "stats.h"
