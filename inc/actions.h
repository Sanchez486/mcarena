#pragma once

class Action;
class Player;
class Hero;

class Actions
{
private:
    Action *attack;
    Action *skill;

public:
    Actions();
    Actions(const Actions &actions);
    ~Actions();

    void setAttack(Action *action);
    void setSkill(Action *action);
    Action* getAttack() const;
    Action* getSkill() const;

    void setPlayers(Player *player1, Player *player2);  // for all actions
    void setSender(Hero *sender);  // for all actions
};
