#include "inc/heroqueue.h"

HeroQueue::HeroQueue(const HeroGroup &group1, const HeroGroup &group2)
{
    setHeroes(group1, group2);
}

// TODO: randomize order of heroes with same initiative
void HeroQueue::setHeroes(const HeroGroup &group1, const HeroGroup &group2)
{
    Hero* arr[12];
    arr[0] = group1.front1;
    arr[1] = group1.front2;
    arr[2] = group1.front3;
    arr[3] = group1.back1;
    arr[4] = group1.back2;
    arr[5] = group1.back3;

    arr[6] = group2.front1;
    arr[7] = group2.front2;
    arr[8] = group2.front3;
    arr[9] = group2.back1;
    arr[10] = group2.back2;
    arr[11] = group2.back3;

    std::sort(arr, arr + 12, [](Hero *left, Hero *right){
        return left->getStats().initiative.val < right->getStats().initiative.val;
    });

    for(int i=0; i < 12; ++i)
    {
        heroList.push_back(arr[i]);
    }
}

std::list<Hero*>::iterator HeroQueue::begin()
{
    return heroList.begin();
}

std::list<Hero*>::iterator HeroQueue::end()
{
    return heroList.end();
}

Hero* HeroQueue::first() const
{
    if(heroList.size() <= 0)
        return nullptr;
    else
        return heroList.front();
}

// TODO: use accumulated initiative
void HeroQueue::rotate()
{
    Hero *front = heroList.pop_front();
    heroList.push_back(front);
}
