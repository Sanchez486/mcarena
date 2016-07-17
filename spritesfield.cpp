#include "inc/spritesfield.h"

#define XSPRITE 120
#define YSPRITE 105
#define NCOL 9
#define NROW 4

#define X 800
#define XINFO 235
#define XBOUND 20
#define YBOUND 20
#define XINDENT 10
#define YINDENT 10
#define ACTIVECOLOR sf::Color(100, 180, 230, 50)
#define TARGETCOLOR sf::Color(230, 50, 50, 50)

SpritesField::SpritesField(BattleGUI* _parent, Player* _firstPlayer, Player* _secondPlayer)
    :
      firstPlayer(_firstPlayer),
      secondPlayer(_secondPlayer),
      parent(_parent),
      activePlayer(ActivePlayer::NOPLAYER),
      actionType(ActionType::NOACTION),
      col(0),
      row(0),
      play(false),
      action(nullptr),
      activeHero(nullptr)
{
    if(_firstPlayer == nullptr || _secondPlayer == nullptr)
        std::cerr << "Player is nullptr";

    for(int i = 0; i < 6; i++)
    {

        //firstPlayerTexture[i] = firstPlayer->getHeroGroup().at(iToPos(i))->getResources().getTexture();
        firstPlayerSprite[i] = sf::Sprite(firstPlayer->getHeroGroup().at(iToPos(i))->getResources().getTexture());
        firstPlayerSprite[i].setTextureRect(sf::IntRect(0, 0, XSPRITE, YSPRITE));
        firstPlayerSprite[i].setPosition(iToVector1(i));

        //secondPlayerTexture[i] = secondPlayer->getHeroGroup().at(iToPos(i))->getResources().getTexture();
        secondPlayerSprite[i] = sf::Sprite(secondPlayer->getHeroGroup().at(iToPos(i))->getResources().getTexture());
        secondPlayerSprite[i].setTextureRect(sf::IntRect(0, 0, XSPRITE, YSPRITE));
        secondPlayerSprite[i].setScale(-1, 1);
        secondPlayerSprite[i].setOrigin(XSPRITE, 0);
        secondPlayerSprite[i].setPosition(iToVector2(i));

        firstPlayerWindow[i] = sfg::Window::Create(sfg::Window::Style::NO_STYLE);
        secondPlayerWindow[i] = sfg::Window::Create(sfg::Window::Style::NO_STYLE);
        firstPlayerWindow[i]->SetAllocation(sf::FloatRect(iToVector1(i), sf::Vector2f(XSPRITE, YSPRITE)));
        secondPlayerWindow[i]->SetAllocation(sf::FloatRect(iToVector2(i), sf::Vector2f(XSPRITE, YSPRITE)));
        firstPlayerWindow[i]->SetId("first" + std::to_string(i));
        secondPlayerWindow[i]->SetId("second" + std::to_string(i));

        firstPlayerWindow[i]->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                    std::bind( &SpritesField::firstPlayerClicked , this, i) );
        secondPlayerWindow[i]->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                    std::bind( &SpritesField::secondPlayerClicked , this, i) );

        firstPlayerWindow[i]->GetSignal( sfg::Widget::OnMouseRightPress ).Connect(
                    std::bind( &BattleGUI::showInfo , parent, firstPlayer->getHeroGroup().at(iToPos(i))));

        secondPlayerWindow[i]->GetSignal( sfg::Widget::OnMouseRightPress ).Connect(
                    std::bind( &BattleGUI::showInfo , parent, secondPlayer->getHeroGroup().at(iToPos(i))));
    }
    activeWindow = sfg::Window::Create();
    clock.restart();
    //for debug
    //std::cerr << "/*\n* 0 == back1\n* 1 == front1\n* 2 == back2\n* 3 == front2\n* 4 == back3\n* 5 == front3\n*/\n";
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
        default: return HeroPosition::NONE;
    }
}

int SpritesField::posToI(HeroPosition pos)
{
    switch(pos)
    {
        case HeroPosition::back1: return 0;
        case HeroPosition::front1: return 1;
        case HeroPosition::back2: return 2;
        case HeroPosition::front2: return 3;
        case HeroPosition::back3: return 4;
        case HeroPosition::front3: return 5;
        default: return -1;
    }
}

sf::Vector2f SpritesField::iToVector1(int i)
{
   sf::Vector2f vector = iToVector(i);
   return sf::Vector2f(vector.x + XINFO, vector.y);
}

sf::Vector2f SpritesField::iToVector2(int i)
{
    sf::Vector2f vector = iToVector(i);
    return sf::Vector2f(X - XSPRITE - vector.x, vector.y);
}

sf::Vector2f SpritesField::iToVector(int i)
{
    switch(i)
    {
        case 0: return sf::Vector2f(XBOUND, YBOUND);
        case 1: return sf::Vector2f(XBOUND + XSPRITE + XINDENT, YBOUND);
        case 2: return sf::Vector2f(XBOUND, YBOUND + YSPRITE + YINDENT);
        case 3: return sf::Vector2f(XBOUND + XSPRITE + XINDENT, YBOUND + YSPRITE + YINDENT);
        case 4: return sf::Vector2f(XBOUND, YBOUND + 2*YSPRITE + 2*YINDENT);
        case 5: return sf::Vector2f(XBOUND + XSPRITE + XINDENT, YBOUND + 2*YSPRITE + 2*YINDENT);
        default: return sf::Vector2f(0, 0);
    }
}

void SpritesField::draw(sf::RenderWindow& app_window)
{       
    if((clock.getElapsedTime().asMilliseconds() > 70) && play)
    {
        sf::Sprite& activeSprite = findSprite(activeHero);
        if(col < 8)
        {
            activeSprite.setTextureRect(sf::IntRect(col*XSPRITE, 0, XSPRITE, YSPRITE));
            col++;
            clock.restart();
        }
        else
        {
            activeSprite.setTextureRect(sf::IntRect(0, 0, XSPRITE, YSPRITE));
            play = false;
            col = 0;
            parent->beginTurn();
        }
    }
    for(int i = 0; i < 6; i++)
    {
        app_window.draw(firstPlayerSprite[i]);
        app_window.draw(secondPlayerSprite[i]);
    }
}

void SpritesField::updateDesktop(sfg::Desktop& desktop)
{
    for(int i = 0; i < 6; i++)
    {
        desktop.Add(firstPlayerWindow[i]);
        desktop.Add(secondPlayerWindow[i]);
    }
}

void SpritesField::firstPlayerClicked(int i)
{
    if((firstPlayerWindow[i]->GetStyle() == sfg::Window::Style::BACKGROUND) &&
       (sfg::Context::Get().GetEngine().GetProperty<sf::Color>("BackgroundColor", firstPlayerWindow[i]) == TARGETCOLOR))
    {
        parent->selectedTarget(firstPlayer->at(iToPos(i)));
    }

}

void SpritesField::secondPlayerClicked(int i)
{
    if((secondPlayerWindow[i]->GetStyle() == sfg::Window::Style::BACKGROUND) &&
       (sfg::Context::Get().GetEngine().GetProperty<sf::Color>("BackgroundColor", secondPlayerWindow[i]) == TARGETCOLOR))
    {
        parent->selectedTarget(secondPlayer->at(iToPos(i)));
    }

}

void SpritesField::setActiveHero(Hero *hero)
{
    activeHero = hero;
    if(firstPlayer->has(hero))
        activePlayer = FIRST;
    else
        activePlayer = SECOND;

    if(activePlayer == ActivePlayer::FIRST)
    {
        int i = posToI(firstPlayer->find(hero));
        colorActive(firstPlayerWindow[i]);
        activeWindow = firstPlayerWindow[i];
    }
    else
    {
        int i = posToI(secondPlayer->find(hero));
        colorActive(secondPlayerWindow[i]);
        activeWindow = secondPlayerWindow[i];
    }
}

void SpritesField::colorActive(sfg::Window::Ptr& window)
{
    window->SetStyle(sfg::Window::Style::BACKGROUND);
    sfg::Context::Get().GetEngine().SetProperty("Window#" + window->GetId() ,
                                                "BackgroundColor", ACTIVECOLOR);
    sfg::Context::Get().GetEngine().SetProperty("Window#" + window->GetId(),
                                                "BorderColor", ACTIVECOLOR);
}

void SpritesField::colorTarget(sfg::Window::Ptr& window)
{
    window->SetStyle(sfg::Window::Style::BACKGROUND);
    sfg::Context::Get().GetEngine().SetProperty("Window#" + window->GetId() ,
                                                "BackgroundColor", TARGETCOLOR);
    sfg::Context::Get().GetEngine().SetProperty("Window#" + window->GetId(),
                                                "BorderColor", TARGETCOLOR);

}

void SpritesField::clearActive(sfg::Window::Ptr& window)
{
    window->SetStyle(sfg::Window::Style::NO_STYLE);
}

void SpritesField::clearTargets()
{
    for(int i = 0; i < 6; i++)
    {
        firstPlayerWindow[i]->SetStyle(sfg::Window::Style::NO_STYLE);
        secondPlayerWindow[i]->SetStyle(sfg::Window::Style::NO_STYLE);
    }
}

void SpritesField::showTargets(Action* action)
{
    if(action != nullptr)
    {
        clearTargets();
        colorActive(activeWindow);
        Targets targets = action->getAvaliableTargetsPlayer1();
        for(int i = 0; i < 6; i++)
        {
            if(targets.is(iToPos(i)))
                colorTarget(firstPlayerWindow[i]);
        }
        targets = action->getAvaliableTargetsPlayer2();
        for(int i = 0; i < 6; i++)
        {
            if(targets.is(iToPos(i)))
                colorTarget(secondPlayerWindow[i]);
        }
    }
}

void SpritesField::playAction(Action* _action)
{
    clearActive(activeWindow);
    clearTargets();

    action = _action;
    play = true;
}

void SpritesField::showDead(Hero *hero)
{
    std::cerr << "dead" << std::endl;
    sf::Sprite& deadSprite = findSprite(hero);

    deadSprite.setTextureRect(sf::IntRect(XSPRITE*(NCOL - 1), YSPRITE*(NROW - 1),
                                 XSPRITE, YSPRITE));
}

void SpritesField::setSkill()
{
    actionType = SKILL;
}

void SpritesField::setAttack()
{
    actionType = ATTACK;
}

sf::Sprite& SpritesField::findSprite(Hero *hero)
{
    if (firstPlayer->has(hero))
    {
        int i = posToI(firstPlayer->find(hero));
        return firstPlayerSprite[i];
    }

    int i = posToI(secondPlayer->find(hero));
    return secondPlayerSprite[i];
}