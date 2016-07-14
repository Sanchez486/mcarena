#include "inc/spritesfield.h"

#define SCALE 0.6
#define XSPRITE 142
#define YSPRITE 140
#define XSPR (XSPRITE * SCALE)
#define YSPR (YSPRITE * SCALE)
#define NCOL 9
#define NROW 4

#define XBACK1 280
#define YBACK1 50
#define XINDENT 30
#define YINDENT 20
#define XBREAK 100

SpritesField::SpritesField(Player* _firstPlayer, Player* _secondPlayer)
    :
      firstPlayer(_firstPlayer),
      secondPlayer(_secondPlayer)
{
    if(_firstPlayer == nullptr || _secondPlayer == nullptr)
        std::cerr << "Player is nullptr";

    for(int i = 0; i < 6; i++)
    {

        //firstPlayerTexture[i] = firstPlayer->getHeroGroup().at(iToPos(i))->getResources().getTexture();
        firstPlayerSprite[i] = sf::Sprite(firstPlayer->getHeroGroup().at(iToPos(i))->getResources().getTexture());
        firstPlayerSprite[i].setTextureRect(sf::IntRect((NCOL - 1)*XSPRITE, 0, XSPRITE, YSPRITE));
        firstPlayerSprite[i].setPosition(iToVector1(i));
        firstPlayerSprite[i].setScale(SCALE, SCALE);

        //secondPlayerTexture[i] = secondPlayer->getHeroGroup().at(iToPos(i))->getResources().getTexture();
        secondPlayerSprite[i] = sf::Sprite(firstPlayer->getHeroGroup().at(iToPos(i))->getResources().getTexture());
        secondPlayerSprite[i].setTextureRect(sf::IntRect((NCOL - 1)*XSPRITE, 0, XSPRITE, YSPRITE));
        secondPlayerSprite[i].setScale(-SCALE, SCALE);
        secondPlayerSprite[i].setOrigin(XSPR, 0);
        secondPlayerSprite[i].setPosition(iToVector2(i));
    }
}

HeroPosition SpritesField::iToPos(int i)
{
    switch(i)
    {
        case 0: return HeroPosition::back1;
        case 1: return HeroPosition::front1;
        case 2: return HeroPosition::back2;
        case 3: return HeroPosition::front2;
        case 4: return HeroPosition::back3;
        case 5: return HeroPosition::front3;
    }
}

sf::Vector2f SpritesField::iToVector1(int i)
{
    switch(i)
    {
        case 0: return sf::Vector2f(XBACK1, YBACK1);
        case 1: return sf::Vector2f(XBACK1 + XSPR + XINDENT, YBACK1);
        case 2: return sf::Vector2f(XBACK1, YBACK1 + YSPR + YINDENT);
        case 3: return sf::Vector2f(XBACK1 + XSPR + XINDENT, YBACK1 + YSPR + YINDENT);
        case 4: return sf::Vector2f(XBACK1, YBACK1 + 2*YSPR + 2*YINDENT);
        case 5: return sf::Vector2f(XBACK1 + XSPR + XINDENT, YBACK1 + 2*YSPR + 2*YINDENT);
    }
}

sf::Vector2f SpritesField::iToVector2(int i)
{
    switch(i)
    {
        case 0: return sf::Vector2f(XBACK1 + 3*XSPR + 2*XINDENT + XBREAK, YBACK1);
        case 1: return sf::Vector2f(XBACK1 + 2*XSPR + XINDENT + XBREAK, YBACK1);
        case 2: return sf::Vector2f(XBACK1 + 3*XSPR + 2*XINDENT + XBREAK, YBACK1 + YSPR + YINDENT);
        case 3: return sf::Vector2f(XBACK1 + 2*XSPR + XINDENT + XBREAK, YBACK1 + YSPR + YINDENT);
        case 4: return sf::Vector2f(XBACK1 + 3*XSPR + 2*XINDENT + XBREAK, YBACK1 + 2*YSPR + 2*YINDENT);
        case 5: return sf::Vector2f(XBACK1 + 2*XSPR + XINDENT + XBREAK, YBACK1 + 2*YSPR + 2*YINDENT);
    }
}

void SpritesField::draw(sf::RenderWindow& app_window)
{
    for(int i = 0; i < 6; i++)
    {
        app_window.draw(firstPlayerSprite[i]);
        app_window.draw(secondPlayerSprite[i]);
    }
}
