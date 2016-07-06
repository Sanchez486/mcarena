#pragma once
#include <QObject>
#include "hero.h"
#include "heroqueue.h"
#include "action.h"

class BattleGUI : public QObject
{
Q_OBJECT
public:
    BattleGUI(QObject* parent);

private:

signals:
    void selectedAction(Action*);  // After attack or skill clicked
    void selectedTarget(Hero*);  // After Hero clicked
    void showInfoSignal(Hero*);  // After right-click on Hero  [this -> this]
    void closed();

public slots:
    void show();  // Show this window
    void hide();  // Hide this window
    void setActiveHero(Hero*);  // Change current hero
    void setQueue(HeroQueue*);  // Change queue
    void showInfo(Hero*);  // Show info about Hero  [this -> this]
    void showTargets(Action*);  // Highlight avaliable targets
    void playAction(Action*);  // Play animation/sounds, show numbers

private slots:
    void update();
};
