#pragma once
#include "inc/hp.h"
#include "inc/damage.h"
#include "inc/kind.h"
#include "inc/element.h"
#include "inc/initiative.h"
#include "inc/actions.h"

struct Stats
{
    HP hp;
    Damage damage;
    Kind kind;
    Element element;
    Initiative initiative;
    Actions actions;
    int cost;

    Stats();
};
