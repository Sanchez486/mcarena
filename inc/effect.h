#pragma once

class Hero;

class Effect
{
protected:
    int duration;

public:
    Effect(int _duration = 1);

    int updateDuration();  // return duration--;

    virtual void onAdd(Hero *hero);
    virtual void onRemove(Hero *hero);
    virtual bool onTurn(Hero *hero);  //return true, if skips turn
};
