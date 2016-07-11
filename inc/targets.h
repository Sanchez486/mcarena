#pragma once

#include "heroposition.h"

struct Targets
{
    bool front1;
    bool front2;
    bool front3;
    bool back1;
    bool back2;
    bool back3;

    Targets(bool val = false);

    bool is(HeroPosition pos) const;
    void set(HeroPosition pos, bool val = true);
    void setAll(bool val);
};
