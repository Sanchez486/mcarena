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
    connect(menuGUI, SIGNAL(closed()), menuModel, SLOT(closed()));
    // Signals Menu Model -> GUI
    connect(menuModel, SIGNAL(show()), menuGUI, SLOT(show()));
    connect(menuModel, SIGNAL(hide()), menuGUI, SLOT(hide()));
    connect(menuModel, SIGNAL(setSounds(bool)), menuGUI, SLOT(setSounds(bool)));
    connect(menuModel, SIGNAL(setMusic(bool)), menuGUI, SLOT(setMusic(bool)));

    // Signals Selection GUI -> Model
    connect(selectionGUI, SIGNAL(clickedHero(HeroTemplate*)), selectionModel, SLOT(clickedHero(HeroTemplate*)));
    connect(selectionGUI, SIGNAL(clickedPlace(HeroPosition)), selectionModel, SLOT(clickedPlace(HeroPosition)));
    connect(selectionGUI, SIGNAL(clickedCross(HeroPosition)), selectionModel, SLOT(clickedCross(HeroPosition)));
    connect(selectionGUI, SIGNAL(clickedDiscard()), selectionModel, SLOT(clickedDiscard()));
    connect(selectionGUI, SIGNAL(clickedStart()), selectionModel, SLOT(clickedStart()));
    connect(selectionGUI, SIGNAL(clickedMenu()), selectionModel, SLOT(clickedMenu()));
    connect(selectionGUI, SIGNAL(clickedPlayer1()), selectionModel, SLOT(clickedPlayer1()));
    connect(selectionGUI, SIGNAL(clickedPlayer2()), selectionModel, SLOT(clickedPlayer2()));
    connect(selectionGUI, SIGNAL(closed()), selectionModel, SLOT(closed()));
    // Signals Selection Model -> GUI
    connect(selectionModel, SIGNAL(show()), selectionGUI, SLOT(show()));
    connect(selectionModel, SIGNAL(hide()), selectionGUI, SLOT(hide()));
    connect(selectionModel, SIGNAL(setHeroVector(HeroVector*)), selectionGUI, SLOT(setHeroVector(HeroVector*)));
    connect(selectionModel, SIGNAL(setActiveHero(HeroTemplate*)), selectionGUI, SLOT(setActiveHero(HeroTemplate*)));
    connect(selectionModel, SIGNAL(setHeroGroup(HeroGroup*)), selectionGUI, SLOT(setHeroGroup(HeroGroup*)));
    connect(selectionModel, SIGNAL(setCost(Cost*)), selectionGUI, SLOT(setCost(Cost*)));

    // Signals Battle GUI -> Model
    connect(battleGUI, SIGNAL(selectedAction(Action*)), battleModel, SLOT(selectedAction(Action*)));
    connect(battleGUI, SIGNAL(selectedTarget(Hero*)), battleModel, SLOT(selectedTarget(Hero*)));
    connect(battleGUI, SIGNAL(closed()), battleModel, SLOT(closed()));
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
    loadHeroes();
    menuModel->showGUI();

    return app.exec();
}

void Game::loadHeroes()
{
    Resources *resource = new Resources();
    resource->loadAttackSound("res/sfx/sonic_attack.wav");
    resource->loadSkillSound("res/sfx/sonic_attack.wav");
    resource->loadTexture("res/img/sprites/sonic_sprite.png");
    resource->loadImage("res/img/images/sonic_img.png");
    resource->loadImage2("res/img/images/sonic_img2.png");

    HeroTemplate *hero1 = new HeroTemplate();
    hero1->setResources(*resource);
    hero1->setStats(Stats(HP(90),Damage(30,35),Kind::range,Element::earth,Initiative(50),Actions(),5));
    heroes.push_back(hero1);

    HeroTemplate *hero2 = new HeroTemplate();
    hero2->setResources(*resource);
    hero2->setStats(Stats(HP(90),Damage(20,25),Kind::range,Element::earth,Initiative(30),Actions(),5));
    heroes.push_back(hero2);

    HeroTemplate *hero3 = new HeroTemplate();
    hero3->setResources(*resource);
    hero3->setStats(Stats(HP(60),Damage(10,15),Kind::range,Element::earth,Initiative(40),Actions(),8));
    heroes.push_back(hero3);

    HeroTemplate *hero4 = new HeroTemplate();
    hero4->setResources(*resource);
    hero4->setStats(Stats(HP(140),Damage(50,55),Kind::melee,Element::earth,Initiative(40),Actions(),9));
    heroes.push_back(hero4);

    HeroTemplate *hero5 = new HeroTemplate();
    hero5->setResources(*resource);
    hero5->setStats(Stats(HP(75),Damage(30,35),Kind::melee,Element::water,Initiative(30),Actions(),6));
    heroes.push_back(hero5);

    HeroTemplate *hero6 = new HeroTemplate();
    hero6->setResources(*resource);
    hero6->setStats(Stats(HP(120),Damage(45,50),Kind::melee,Element::water,Initiative(45),Actions(),8));
    heroes.push_back(hero6);

    HeroTemplate *hero7 = new HeroTemplate();
    hero7->setResources(*resource);
    hero7->setStats(Stats(HP(45),Damage(20,25),Kind::melee,Element::water,Initiative(40),Actions(),2));
    heroes.push_back(hero7);

    HeroTemplate *hero8 = new HeroTemplate();
    hero8->setResources(*resource);
    hero8->setStats(Stats(HP(135),Damage(10,15),Kind::range,Element::water,Initiative(30),Actions(),5));
    heroes.push_back(hero8);

    HeroTemplate *hero9 = new HeroTemplate();
    hero9->setResources(*resource);
    hero9->setStats(Stats(HP(150),Damage(50,60),Kind::melee,Element::fire,Initiative(40),Actions(),10));
    heroes.push_back(hero9);

    HeroTemplate *hero10 = new HeroTemplate();
    hero10->setResources(*resource);
    hero10->setStats(Stats(HP(130),Damage(45,50),Kind::melee,Element::fire,Initiative(35),Actions(),8));
    heroes.push_back(hero10);

    HeroTemplate *hero11 = new HeroTemplate();
    hero11->setResources(*resource);
    hero11->setStats(Stats(HP(75),Damage(40,45),Kind::range,Element::fire,Initiative(45),Actions(),6));
    heroes.push_back(hero11);

    HeroTemplate *hero12 = new HeroTemplate();
    hero12->setResources(*resource);
    hero12->setStats(Stats(HP(45),Damage(15,20),Kind::range,Element::fire,Initiative(60),Actions(),1));
    heroes.push_back(hero12);

    HeroTemplate *hero13 = new HeroTemplate();
    hero13->setResources(*resource);
    hero13->setStats(Stats(HP(80),Damage(20,25),Kind::melee,Element::neutral,Initiative(30),Actions(),6));
    heroes.push_back(hero13);

    HeroTemplate *hero14 = new HeroTemplate();
    hero14->setResources(*resource);
    hero14->setStats(Stats(HP(100),Damage(20,25),Kind::range,Element::neutral,Initiative(40),Actions(),4));
    heroes.push_back(hero14);

    HeroTemplate *hero15 = new HeroTemplate();
    hero15->setResources(*resource);
    hero15->setStats(Stats(HP(20),Damage(40,45),Kind::melee,Element::neutral,Initiative(80),Actions(),7));
    heroes.push_back(hero15);

    HeroTemplate *hero16 = new HeroTemplate();
    hero16->setResources(*resource);
    hero16->setStats(Stats(HP(90),Damage(40,50),Kind::range,Element::neutral,Initiative(30),Actions(),4));
    heroes.push_back(hero16);
}
