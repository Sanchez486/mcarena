#pragma once

#include "hero.h"
#include "heroposition.h"

struct HeroGroup
{
    Hero *front1;
    Hero *front2;
    Hero *front3;
    Hero *back1;
    Hero *back2;
    Hero *back3;

    HeroGroup();
    Hero* at(HeroPosition pos);
    HeroPosition find(Hero *hero);
};
