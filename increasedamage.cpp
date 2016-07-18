#include "inc/increasedamage.h"
#include "inc/hero.h"

IncreaseDamage::IncreaseDamage(int _duration, double _rate)
    : Effect(_duration, false), rate(_rate)
{

}

void IncreaseDamage::onAdd(Hero *hero)
{
    Damage &templateDamage = hero->getTemplateStats().damage;
    Damage &heroDamage = hero->getStats().damage;

    heroDamage.min += round(templateDamage.min * rate);
    heroDamage.max += round(templateDamage.max * rate);
}

void IncreaseDamage::onRemove(Hero *hero)
{
    Damage &templateDamage = hero->getTemplateStats().damage;
    Damage &heroDamage = hero->getStats().damage;

    heroDamage.min -= round(templateDamage.min * rate);
    heroDamage.max -= round(templateDamage.max * rate);
}
