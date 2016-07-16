#pragma once
#include <QObject>

#include "hero.h"
#include "heroqueue.h"
#include "action.h"
#include "player.h"

class BattleModel : public QObject
{
Q_OBJECT
private:
    Player *player1;
    Player *player2;
    HeroQueue heroQueue;
    Action *action;  // Last chosen Action

signals:
    // BattleModel -> BattleGUI
    void show();  // Show GUI window
    void hide();  // Hide GUI window
    void setPlayers(Player*, Player*);
    void setActiveHero(Hero*);  // Change current hero
    void setQueue(HeroQueue*);  // Change queue
    void showTargets(Action*);  // Highlight avaliable targets
    void playAction(Action*);  // Play animation/sounds, show numbers
    void showDead(Hero*);  // Show death animation
    void winPlayer1();  // Show final window
    void winPlayer2();  // Show final window

    // BattleModel -> Game
    void finishedSignal();
    void closedSignal();

public slots:
    void selectedAction(Action *_action);  // After attack or skill clicked
    void selectedTarget(Hero *target);  // After Hero clicked
    void beginTurn(); // on each new turn
    void finished();
    void closed();

public:
    BattleModel(QObject *parent = nullptr);

    void beginBattle(Player *_player1, Player *_player2);
    void hideGUI();

private:
    void updateDead();  // check if any hero died and send showDead();
    void updateDead(Player *player, HeroPosition pos);
};
