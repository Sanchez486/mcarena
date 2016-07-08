#include "inc/stats.h"

Stats::Stats()
    : hp(), damage(), kind(), element(),
      initiative(), actions(), cost(0)
{

}

Stats::Stats(const HP &_hp,
             const Damage &_damage,
             Kind _kind,
             Element _element,
             const Initiative &_initiative,
             const Actions &_actions,
             int _cost)
    : hp(_hp),
      damage(_damage),
      kind(_kind),
      element(_element),
      initiative(_initiative),
      actions(_actions),
      cost(_cost)
{

}
