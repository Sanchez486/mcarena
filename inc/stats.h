#pragma once
#include "hp.h"
#include "damage.h"
#include "kind.h"
#include "element.h"
#include "initiative.h"
#include "actions.h"

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
