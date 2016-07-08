#include "inc/game.h"
#include <iostream>

using namespace std;

Game::Game(int argc, char *argv[]) : app(argc, argv), heroes()
{
    mainWindow = new MainWindow();
    menuGUI = new MenuGUI(*mainWindow, this);
    menuModel = new MenuModel(this);
    selectionGUI = new SelectionGUI(*mainWindow, this);
    selectionModel = new SelectionModel(this);
    battleGUI = new BattleGUI(*mainWindow, this);
    battleModel = new BattleModel(this);

    // Signals Menu GUI -> Model
    connect(menuGUI, SIGNAL(clickedPlay()), menuModel, SLOT(clickedPlay()));
    connect(menuGUI, SIGNAL(clickedPlayOnline()), menuModel, SLOT(clickedPlayOnline()));
    connect(menuGUI, SIGNAL(clickedPlayCPU()), menuModel, SLOT(clickedPlayCPU()));
    connect(menuGUI, SIGNAL(clickedExit()), menuModel, SLOT(clickedExit()));
    connect(menuGUI, SIGNAL(clickedSound()), menuModel, SLOT(clickedSound()));
    connect(menuGUI, SIGNAL(clickedMusic()), menuModel, SLOT(clickedMusic()));
    // Signals Menu Model -> GUI
    connect(menuModel, SIGNAL(show()), menuGUI, SLOT(show()));
    connect(menuModel, SIGNAL(hide()), menuGUI, SLOT(hide()));
    connect(menuModel, SIGNAL(setSounds(bool)), menuGUI, SLOT(setSounds(bool)));
    connect(menuModel, SIGNAL(setMusic(bool)), menuGUI, SLOT(setMusic(bool)));

    // Signals Selection GUI -> Model
    connect(selectionGUI, SIGNAL(clickedHero(HeroTemplate*)), selectionModel, SLOT(clickedHero(HeroTemplate*)));
    connect(selectionGUI, SIGNAL(clickedPlace()), selectionModel, SLOT(clickedPlace()));
    connect(selectionGUI, SIGNAL(clickedCross(Hero*)), selectionModel, SLOT(clickedCross(Hero*)));
    connect(selectionGUI, SIGNAL(clickedDiscard()), selectionModel, SLOT(clickedDiscard()));
    connect(selectionGUI, SIGNAL(clickedStart()), selectionModel, SLOT(clickedStart()));
    connect(selectionGUI, SIGNAL(clickedMenu()), selectionModel, SLOT(clickedMenu()));
    connect(selectionGUI, SIGNAL(clickedPlayer1()), selectionModel, SLOT(clickedPlayer1()));
    connect(selectionGUI, SIGNAL(clickedPlayer2()), selectionModel, SLOT(clickedPlayer2()));
    // Signals Selection Model -> GUI
    connect(selectionModel, SIGNAL(show()), selectionGUI, SLOT(show()));
    connect(selectionModel, SIGNAL(hide()), selectionGUI, SLOT(hide()));
    connect(selectionModel, SIGNAL(setHeroVector(const std::vector<HeroTemplate*>&)), selectionGUI, SLOT(setHeroVector(const std::vector<HeroTemplate*>&)));
    connect(selectionModel, SIGNAL(setActiveHero(HeroTemplate*)), selectionGUI, SLOT(setActiveHero(HeroTemplate*)));
    connect(selectionModel, SIGNAL(setHeroGroup(HeroGroup*)), selectionGUI, SLOT(setHeroGroup(HeroGroup*)));
    connect(selectionModel, SIGNAL(setCost()), selectionGUI, SLOT(setCost()));
    connect(selectionModel, SIGNAL(setPlayer(Player*)), selectionGUI, SLOT(setPlayer(Player*)));

    // Signals Battle GUI -> Model
    connect(battleGUI, SIGNAL(selectedAction(Action*)), battleModel, SLOT(selectedAction(Action*)));
    connect(battleGUI, SIGNAL(selectedTarget(Hero*)), battleModel, SLOT(selectedTarget(Hero*)));
    // Signals Battel Model -> GUI
    connect(battleModel, SIGNAL(show()), battleGUI, SLOT(show()));
    connect(battleModel, SIGNAL(hide()), battleGUI, SLOT(hide()));
    connect(battleModel, SIGNAL(setActiveHero(Hero*)), battleGUI, SLOT(setActiveHero(Hero*)));
    connect(battleModel, SIGNAL(setQueue(HeroQueue*)), battleGUI, SLOT(setQueue(HeroQueue*)));
    connect(battleModel, SIGNAL(showTargets(Action*)), battleGUI, SLOT(showTargets(Action*)));
    connect(battleModel, SIGNAL(playAction(Action*)), battleGUI, SLOT(playAction(Action*)));

    // Signals MenuModel -> Game
    connect(menuModel, SIGNAL(clickedPlaySignal()), SLOT(clickedPlay()));
    connect(menuModel, SIGNAL(clickedPlayOnlineSignal()), SLOT(clickedPlayOnline()));
    connect(menuModel, SIGNAL(clickedPlayCPUSignal()), SLOT(clickedPlayCPU()));
    connect(menuModel, SIGNAL(clickedExitSignal()), SLOT(clickedExit()));
    connect(menuModel, SIGNAL(closedSignal()), SLOT(closedMenu()));

    // Signals SelectionModel -> Game
    connect(selectionModel, SIGNAL(clickedStartSignal()), SLOT(clickedStart()));
    connect(selectionModel, SIGNAL(clickedMenuSignal()), SLOT(clickedMenu()));
    connect(selectionModel, SIGNAL(closedSignal()), SLOT(closedSelection()));

    // Signals BattleModel -> Game
    connect(battleModel, SIGNAL(finishedSignal()), SLOT(finished()));
    connect(battleModel, SIGNAL(closedSignal()), SLOT(closedBattle()));
}

void Game::clickedPlay()
{
    cerr << "Game::clickedPlay()" << endl;
    menuModel->hideGUI();
    selectionModel->beginPlay(&heroes);
}

void Game::clickedPlayOnline()
{
    cerr << "Game::clickedPlayOnline()" << endl;
    menuModel->hideGUI();
    selectionModel->beginPlayOnline(&heroes);
}

void Game::clickedPlayCPU()
{
    cerr << "Game::clickedPlayCPU()" << endl;
    menuModel->hideGUI();
    selectionModel->beginPlayCPU(&heroes);
}

void Game::clickedExit()
{
    cerr << "Game::clickedExit()" << endl;
    menuModel->hideGUI();
    app.quit();
}

void Game::closedMenu()
{
    cerr << "Game::closedMenu()" << endl;
    menuModel->hideGUI();
    app.quit();
}

// TODO: recieve and send data [Selection->Battle]
void Game::clickedStart()
{
    cerr << "Game::clickedStart()" << endl;
    selectionModel->hideGUI();
    battleGUI->show();
}

void Game::clickedMenu()
{
    cerr << "Game::clickedMenu()" << endl;
    selectionModel->hideGUI();
    menuModel->showGUI();
}

void Game::closedSelection()
{
    cerr << "Game::closedSelection()" << endl;
    selectionModel->hideGUI();
    app.quit();
}

void Game::finished()
{
    cerr << "Game::finished()" << endl;
    battleModel->hideGUI();
    menuModel->showGUI();
}

void Game::closedBattle()
{
    cerr << "Game::closedBattle()" << endl;
    battleModel->hideGUI();
    app.quit();
}

int Game::exec()
{
    menuGUI->show();

    return app.exec();
}

void Game::loadHeroes()
{
    HeroTemplate *hero = new HeroTemplate();

    //Resources *resource;
    //hero->setResources(resource);

    hero->setStats(Stats(HP(999), Damage(11, 99), Kind::melee, Element::neutral,
                         Initiative(99), Actions(), 10));
    heroes.push_back(hero);

    //hero->setStats();
    //...
}
