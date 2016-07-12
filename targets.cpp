#include "inc/targets.h"

Targets::Targets(bool val)
{
    setAll(val);
}

bool Targets::is(HeroPosition pos) const
{
    switch(pos)
    {
    case HeroPosition::front1:
        return front1;
    case HeroPosition::front2:
        return front2;
    case HeroPosition::front3:
        return front3;
    case HeroPosition::back1:
        return back1;
    case HeroPosition::back2:
        return back2;
    case HeroPosition::back3:
        return back3;
    }
}

void Targets::set(HeroPosition pos, bool val)
{
    switch(pos)
    {
    case HeroPosition::front1:
        front1 = val;
    case HeroPosition::front2:
        front2 = val;
    case HeroPosition::front3:
        front3 = val;
    case HeroPosition::back1:
        back1 = val;
    case HeroPosition::back2:
        back2 = val;
    case HeroPosition::back3:
        back3 = val;
    }
}

void Targets::setAll(bool val)
{
    front1 = front2 = front3 = back1 = back2 = back3 = val;
}
