#pragma once

#include <SFML/Graphics.hpp>
#include <SFGUI/Widget.hpp>

#include "player.h"
#include "heroposition.h"

class SpritesField
{
private:
    Player* firstPlayer;
    Player* secondPlayer;
    sf::Sprite firstPlayerSprite[6];
    sf::Sprite secondPlayerSprite[6];
    //sf::Texture firstPlayerTexture[6];
    //sf::Texture secondPlayerTexture[6];
    sfg::Widget::Ptr firstPlayerwidget[6];
    sfg::Widget::Ptr secondPlayerwidget[6];

    //Additional functions
    HeroPosition iToPos(int i);
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

public:
    SpritesField(Player* _firstPlayer, Player* _secondPlayer);
    void draw(sf::RenderWindow& app_window);
};
