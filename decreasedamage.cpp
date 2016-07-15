#include "inc/decreasedamage.h"
#include "inc/hero.h"

DecreaseDamage::DecreaseDamage(int _duration, double _rate)
    : Effect(_duration), rate(_rate)
{

}

void DecreaseDamage::onAdd(Hero *hero)
{
    Damage &templateDamage = hero->getTemplateStats().damage;
    Damage &heroDamage = hero->getStats().damage;

    heroDamage.min -= round(templateDamage.min * rate);
    heroDamage.max -= round(templateDamage.max * rate);
}

void DecreaseDamage::onRemove(Hero *hero)
{
    Damage &templateDamage = hero->getTemplateStats().damage;
    Damage &heroDamage = hero->getStats().damage;

    heroDamage.min += round(templateDamage.min * rate);
    heroDamage.max += round(templateDamage.max * rate);
}
