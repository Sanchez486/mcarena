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
    Stats(const HP &_hp,
          const Damage &_damage,
          Kind _kind,
          Element _element,
          const Initiative &_initiative,
          const Actions &_actions,
          int _cost);
};
