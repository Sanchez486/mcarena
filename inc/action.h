#pragma once

#include <string>

#include "player.h"
#include "targets.h"

class Action
{
protected:
    Player *player1;
    Player *player2;
    Hero *sender;
    Hero *target;

public:
    Action();
    virtual ~Action();

    virtual Action* clone() const = 0;  // return new Action(*this);

    void setPlayers(Player *_player1, Player *_player2);
    void setSender(Hero *_sender);
    void setTarget(Hero *_target);

    Hero* getSender() const;
    virtual Targets getAvaliableTargetsPlayer1() const = 0;  // After setSender()
    virtual Targets getAvaliableTargetsPlayer2() const = 0;  // After setSender()
    virtual Targets getTargetsPlayer1() const = 0;  // After setTarget()
    virtual Targets getTargetsPlayer2() const = 0;  // After setTarget()

    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;

    virtual void doAction() = 0;

protected:
    Targets getAliveTargets(Player *player) const;
    Targets getAliveTargetsFrontLine(Player *player) const;
    Targets getAliveTargetsBackLine(Player *player) const;
    Targets getAliveAttackTargets(Player *owner, Player *enemy) const;
    Targets getRandomAliveTargets(Player *player, int num = 1) const;
    int countAlive(Player *player) const;

    bool isBlocked(Hero *hero, Player *player) const;

    int countDamageWithElement(int realDamage, Hero *_sender, Hero *_target) const;

    int getRandom(int from, int to) const;  // random int from range [from, to]
    int getRandom(const Damage &damage) const;  // random int from range [min, max]
    bool rollChance(double chance);  // returns true with a probability of [chance]

    void attack(Hero *hero, const Damage &damage);
    void attackAllTargets(Player *player, const Targets &targets, const Damage &damage);
};
