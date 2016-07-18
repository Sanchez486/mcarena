#pragma once

class Hero;

class Effect
{
protected:
    int duration;
    bool removeOnTurn;  // if true - remove before turn, if false - remove after turn

public:
    Effect(int _duration, bool _removeOnTurn = true);

    int updateDuration();  // return --duration-
    bool isRemoveOnTurn() const;

    virtual void onAdd(Hero *hero);
    virtual void onRemove(Hero *hero);
    virtual bool onTurn(Hero *hero);  //return true, if skips turn
};
