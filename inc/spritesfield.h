#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Desktop.hpp>

#include "player.h"
#include "heroposition.h"
#include "hero.h"
#include "battlegui.h"
#include "action.h"
#include "targets.h"

class BattleGUI;

class SpritesField
{
private:

    BattleGUI* parent;
    Player* firstPlayer;
    Player* secondPlayer;
    sf::Sprite firstPlayerSprite[6];
    sf::Sprite secondPlayerSprite[6];
    //sf::Texture firstPlayerTexture[6];
    //sf::Texture secondPlayerTexture[6];
    sfg::Window::Ptr firstPlayerWindow[6];
    sfg::Window::Ptr secondPlayerWindow[6];
    sfg::Window::Ptr activeWindow;
    sf::Sound playingSound;
    sf::Texture hpBarT;
    sf::Sprite firstHpBars[6], secondHpBars[6];
    sf::Font font;
    sf::Text firstHpLabels[6], secondHpLabels[6];

    Hero *activeHero;
    Hero *deadHero;
    Action *action;
    Targets targetsPlayer1, targetsPlayer2;

    sf::Clock clock;

    enum ActivePlayer
    {
        FIRST,
        SECOND,
        NOPLAYER
    };
    ActivePlayer activePlayer;

    enum ActionType
    {
        ATTACK,
        SKILL,
        NOACTION
    };
    ActionType actionType;

    //For moving sprites
    int col;
    bool row;
    bool play;
    bool dead;
    bool dmg;

    //Additional functions
    HeroPosition iToPos(int i);
    int posToI(HeroPosition Pos);
    sf::Vector2f iToVector(int i);
    sf::Vector2f iToVector1(int i); //Returns position on the field to i unit of 1st player
    sf::Vector2f iToVector2(int i); //-||-||- of 2nd player
    /*
     * 0 == back1
     * 1 == front1
     * 2 == back2
     * 3 == front2
     * 4 == back3
     * 5 == front3
    */

    //Functions connected to sFGUI widget signals
    void firstPlayerClicked(int i);
    void secondPlayerClicked(int i);
    void colorActive(sfg::Window::Ptr& window);
    void colorTarget(sfg::Window::Ptr& window);
    void clearActive(sfg::Window::Ptr& window);
    void clearTargets();
    sf::Sprite& findSprite(Hero *hero);

public:
    SpritesField(BattleGUI* _parent, Player* _firstPlayer, Player* _secondPlayer);

    //For displaying
    void draw(MainWindow& app_window);
    void updateDesktop(sfg::Desktop& desktop);

    //Slots
    void setActiveHero(Hero *hero);
    void showTargets(Action* action);
    void playAction(Action* action);
    void showDead(Hero *hero);
    void updateHPBars();

    //Monitoring actions
    void setSkill();
    void setAttack();
    void setInsensitive();
    void setSensitive();
    void clear();
};
