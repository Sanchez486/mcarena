#include "inc/3x3randattack.h"

Action *threeAttack::clone() const
{
    return new threeAttack(*this);
}

Targets threeAttack::getAvaliableTargetsPlayer1() const
{
    return getAliveTargets(player1);
}

Targets threeAttack::getAvaliableTargetsPlayer2() const
{
    return getAliveTargets(player2);
}

Targets threeAttack::getTargetsPlayer1() const
{
    HeroPosition pos = player1->getHeroGroup().find(target);
    Targets targets;
    targets.set(pos);

    return targets;
}

Targets threeAttack::getTargetsPlayer2() const
{
    HeroPosition pos = player2->getHeroGroup().find(target);
    Targets targets;
    targets.set(pos);

    return targets;
}

const std::string &threeAttack::getName() const
{
    return "3 random Attack";
}

const std::string &threeAttack::getDescription() const
{
    return "Attack of 3 random opposite heroes with damage of 3";
}

void threeAttack::doAction()
{
    int realDamage = 3;
    bool _player1;
    
    if(player1->getHeroGroup().find(target)!=NONE) _player1 = TRUE;
    else _player1 = FALSE;
        
    if(sender->getStats().element > target->getStats().element)
        realDamage *= 1.25;

    if(sender->getStats().element < target->getStats().element)
        realDamage *= 0.8;
    
    
    if(_player1)
    {
        Targets targets = getRandomAliveTargets(3);
        if(targets.is(front1)) 
            player1->getHeroGroup.at(front1)->getStats().hp.curr -= realDamage;
        if(targets.is(front2)) 
            player1->getHeroGroup.at(front2)->getStats().hp.curr -= realDamage;
        if(targets.is(front3)) 
            player1->getHeroGroup.at(front3)->getStats().hp.curr -= realDamage;
        if(targets.is(back1)) 
            player1->getHeroGroup.at(back1)->getStats().hp.curr -= realDamage;
        if(targets.is(back2)) 
            player1->getHeroGroup.at(back2)->getStats().hp.curr -= realDamage;
        if(targets.is(back3)) 
            player1->getHeroGroup.at(back3)->getStats().hp.curr -= realDamage;
    }
    
    else
    {
        Targets targets = getRandomAliveTargets(3);
        if(targets.is(front1)) 
            player2->getHeroGroup.at(front1)->getStats().hp.curr -= realDamage;
        if(targets.is(front2)) 
            player2->getHeroGroup.at(front2)->getStats().hp.curr -= realDamage;
        if(targets.is(front3)) 
            player2->getHeroGroup.at(front3)->getStats().hp.curr -= realDamage;
        if(targets.is(back1)) 
            player2->getHeroGroup.at(back1)->getStats().hp.curr -= realDamage;
        if(targets.is(back2)) 
            player2->getHeroGroup.at(back2)->getStats().hp.curr -= realDamage;
        if(targets.is(back3)) 
            player2->getHeroGroup.at(back3)->getStats().hp.curr -= realDamage;
    }
}
