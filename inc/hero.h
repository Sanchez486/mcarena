#pragma once

#include <list>

#include "herotemplate.h"

class Effect;

class Hero
{
private:
    HeroTemplate *heroTemplate;
    Stats *stats;
    std::list<Effect*> effectList;
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

    void add(Effect *effect);
    bool onTurnEffects();
    void removeAllEffects();

    bool isAlive() const;
    bool updateDead();  // return true, if just dieds

private:
    void remove(Effect *effect);
};

#include "stats.h"
