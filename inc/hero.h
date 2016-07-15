#pragma once

#include "herotemplate.h"

class Hero
{
private:
    HeroTemplate *heroTemplate;
    Stats *stats;
    bool showedDead;  // true, if showed as dead

public:
    Hero(HeroTemplate *_templ = nullptr);
    ~Hero();

    Stats& getStats();  // return stats
    Stats& getTemplateStats();  // return heroTemplate->getStats
    Resources& getResources();
    HeroTemplate* getTemplate() const;

    Action* getAttack() const;
    Action* getSkill() const;

    bool isAlive() const;
    bool updateDead();  // return true, if just dieds
};

#include "stats.h"
