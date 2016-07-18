#include "inc/battlegui.h"

#define XICON 83
#define YICON 100
#define XINFO 240
#define YBUTTON 50
#define TIMEUPDATE 25
#define FRAME 15
#define YSCROLLBAR 30
#define YINDENT 10
#define YQTOTAL (YICON+FRAME*2+YSCROLLBAR+YINDENT - 10)
#define XWINDOW 160
#define YWINDOW 250
#define X 800
#define Y 600
#define XFINISH 200
#define YFINISH 200
#define YSKILL 30

BattleGUI::BattleGUI(MainWindow& _app_window, QObject *parent)
    :
      QObject(parent),

      app_window(_app_window),
      queueWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      buttonWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      infoWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),

      //Queuewindow
      queueSBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, FRAME)),
      qScroll(sfg::ScrolledWindow::Create()),
      queueBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10)),

      activeHero(nullptr),
      queueImages(),

      //Buttonwindow
      buttonBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 20)),
      attackButton(sfg::Button::Create( "Attack" )),
      skillButton(sfg::Button::Create( "Skill" )),
      skipButton(sfg::Button::Create("Skip")),
      menuButton(sfg::Button::Create("Main menu")),

      //InfoWindow
      infoBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL)),
      skillsBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL)),
      picBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL)),
      labelBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL)),
      skillBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL)),

      //InfoWindow2
      skillWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      skillInfo(sfg::Label::Create("")),

      frame(sfg::Frame::Create(sf::String(""))),

      //Sprite Field
      spritesField(nullptr),

      //Finish Window

      finishWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      finishBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL,FRAME)),
      menuButton2(sfg::Button::Create("Main menu")),
      winnerLabel(sfg::Label::Create("")),

      //Pop window
      popWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      popSkillsBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL)),
      popBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL)),
      popPicBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL)),
      popLabelBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL)),
      popSkillBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL))

{
    app_window.resetGLStates();
    backgroundT.loadFromFile("res/img/background/battleBACK.jpg");
    background.setTexture(backgroundT);

    //Queuewindow
    queueWindow->Add(queueSBox);
    queueSBox->Pack(qScroll, false, true);
    qScroll->AddWithViewport(queueBox);
    qScroll->SetScrollbarPolicy( sfg::ScrolledWindow::VERTICAL_NEVER| sfg::ScrolledWindow::HORIZONTAL_ALWAYS);
    qScroll->SetRequisition( sf::Vector2f(app_window.getX() - FRAME*2, YICON ) );

    desktop.Add(queueWindow);
    queueWindow->SetAllocation(sf::FloatRect(0,app_window.getY() - YQTOTAL, app_window.getX(), YICON+FRAME*2+YSCROLLBAR));

    //Buttonwindow

    buttonWindow->Add(buttonBox);
    buttonBox->Pack(attackButton);
    buttonBox->Pack(skillButton);
    buttonBox->Pack(skipButton);
    buttonBox->Pack(menuButton);

    desktop.Add(buttonWindow);
    buttonWindow->SetAllocation(sf::FloatRect( XINFO , app_window.getY() - YQTOTAL - YBUTTON, app_window.getX() - XINFO, YBUTTON));

    //Ifowindow

    infoImage = sfg::Image::Create(sf::Image());

    infoWindow->Add(frame);
    frame->Add(infoBox);
    infoBox->Pack(infoImage);
    infoBox->Pack(skillsBox);
    infoBox->Pack(skillBox);
    skillsBox->Pack(picBox);
    skillsBox->Pack(labelBox);


    for(int i = 0; i < 6; i++)
    {
        stats[i] = sfg::Label::Create(sf::String(""));
        if(i != 0)
            labelBox->Pack(stats[i]);
        if(i != 5)
        {
            infoIconImages[i] = sfg::Image::Create(app_window.getImageForBattle(i));
            picBox->Pack(infoIconImages[i]);
        }
        if(i == 0 || i == 1)
            typeImages[i] = sfg::Image::Create(app_window.getImage(i));
    }
    stats[6] = sfg::Label::Create(sf::String(""));
    skillBox->Pack(stats[6]);

    stats[5]->SetId("element1");

    desktop.Add(infoWindow);
    infoWindow->SetAllocation(sf::FloatRect( 0 , 0, XINFO,app_window.getY() - YQTOTAL));

    //FinishWindow
    desktop.Add(finishWindow);
    finishWindow->Add(finishBox);
    finishWindow->Show(false);
    finishWindow->SetAllocation(sf::FloatRect((app_window.getX()-XFINISH)/2,(app_window.getY()-YFINISH)/2-FRAME,XFINISH,YFINISH));
    finishBox->Pack(winnerLabel);
    finishBox->Pack(menuButton2);

    //Pop window
    popWindow->Add(popBox);
    popBox->Pack(popSkillsBox);
    popBox->Pack(popSkillBox);
    popSkillsBox->Pack(popPicBox);
    popSkillsBox->Pack(popLabelBox);

    for(int i = 0; i < 6; i++)
    {

        popStats[i] = sfg::Label::Create(sf::String(""));
        if(i != 0)
            popLabelBox->Pack(popStats[i]);
        else
            popBox->PackStart(popStats[i]);
        if(i != 5)
        {
            popIconImages[i] = sfg::Image::Create(app_window.getImageForBattle(i));
            popPicBox->Pack(popIconImages[i]);
        }
    }
    popStats[6] = sfg::Label::Create(sf::String(""));
    popSkillBox->Pack(popStats[6]);

    popWindow->Show(false);
    desktop.Add(popWindow);

    popStats[0]->SetId("title");
    popStats[5]->SetId("element2");

    popWindow->SetId("window");
    sfg::Context::Get().GetEngine().SetProperty("Window#" + popWindow->GetId(),
                                                "BackgroundColor", sf::Color(0, 0, 0, 200));

    //InfoWindow2
    desktop.Add(skillWindow);
    skillWindow->Add(skillInfo);
    skillWindow->Show(false);
    skillWindow->SetId("Skill");
    sfg::Context::Get().GetEngine().SetProperty("Window#" + skillWindow->GetId(),
                                                "BackgroundColor", sf::Color(0, 0, 0, 200));


    //Signals

    skillButton->GetSignal( sfg::Widget::OnMouseRightPress ).Connect(
                std::bind( &BattleGUI::showSkill, this) );
    skillButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                std::bind( &BattleGUI::clickedButton, this, ButtonPressed::SKILL ) );
    attackButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                std::bind( &BattleGUI::clickedButton, this, ButtonPressed::ATTACK ) );
    skipButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                std::bind( &BattleGUI::clickedButton, this, ButtonPressed::SKIP ) );
    menuButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                std::bind( &BattleGUI::clickedButton, this, ButtonPressed::MENU ) );
    menuButton2->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                std::bind( &BattleGUI::clickedButton, this, ButtonPressed::MENU2 ) );
}

BattleGUI::~BattleGUI()
{
    if(spritesField != nullptr)
        delete spritesField;
}

void BattleGUI::clickedButton(ButtonPressed Button)
{
    app_window.playButtonSound();
    switch (Button)
    {
        case ATTACK:
            selectedAction(activeHero->getAttack());
            spritesField->setAttack();
            break;
        case SKILL:
            selectedAction(activeHero->getSkill());
            spritesField->setSkill();
            break;
        case SKIP:
            spritesField->clear();
            beginTurn();
            break;
        case MENU:
            spritesField->clear();
            finished();
            break;
        case MENU2:
            spritesField->clear();
            spritesField->setSensitive();
            finishWindow->Show(false);
            finished();
            break;
    }
}

void BattleGUI::show()
{
   queueWindow->Show(true);
   buttonWindow->Show(true);
   infoWindow->Show(true);
   queueWindow->SetState(sfg::Window::State::NORMAL);
   infoWindow->SetState(sfg::Window::State::NORMAL);
   buttonWindow->SetState(sfg::Window::State::NORMAL);
   connect(app_window.getTimer(), SIGNAL(timeout()), this, SLOT(update()));
   app_window.getTimer()->start(TIMEUPDATE);
}

void BattleGUI::hide()
{
    queueWindow->Show(false);
    buttonWindow->Show(false);
    infoWindow->Show(false);
    popWindow->Show(false);
    disconnect(app_window.getTimer(), SIGNAL(timeout()), this, SLOT(update()));
    app_window.clear(sf::Color::Black);
    app_window.display();
}

void BattleGUI::update()
{
    if(app_window.isOpen())
    {
        sf::Event event;
        while(app_window.pollEvent(event))
        {
            desktop.HandleEvent(event);

            if (event.type == sf::Event::Closed)
            {
               app_window.close();
               closed();
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if(event.mouseButton.button == sf::Mouse::Button::Right)
                {
                    popWindow->Show(false);
                    popWindow->SetState(sfg::Widget::State::INSENSITIVE);
                    skillWindow->Show(false);
                }
            }
        }
        desktop.Update( 0.5 );

        app_window.clear();
        app_window.draw(background);
        if(spritesField != nullptr)
            spritesField->draw(app_window);
        sfgui.Display(app_window);
        app_window.display();
    }
}

void BattleGUI::setPlayers(Player *player1, Player *player2)
{
    if(spritesField != nullptr)
        delete spritesField;

    spritesField = new SpritesField(this, player1, player2);
    spritesField->updateDesktop(desktop);
}

void BattleGUI::setActiveHero(Hero *hero)
{
    //info
    activeHero = hero;
    infoImage->SetImage(hero->getResources().getImage2());
    completeStats(stats, infoIconImages, hero);
    frame->SetLabel(stats[0]->GetText());
    updateHPBars();

    //button
    if(hero->getSkill() != nullptr)
        skillButton->SetLabel(sf::String(hero->getSkill()->getName()));
    if(hero->getAttack() != nullptr)
        attackButton->SetLabel(sf::String(hero->getAttack()->getName()));

    //highlighting
    spritesField->setActiveHero(hero);

    //+info
    skillInfo->SetText(hero->getSkill()->getName()+": " + hero->getSkill()->getDescription());
}

void BattleGUI::setQueue(HeroQueue *queue)
{

    if(!queueImages.empty())
    {
        for(auto it = queueImages.begin(), end = queueImages.end(); it != end; it++)
            queueBox->Remove(*it);
        queueImages.clear();
    }

    int i = 0;
    for(auto it = queue->begin() , end = queue->end(); it != end; it++)
    {
        if (it == queue->begin())
            queueImages.push_back(sfg::Image::Create((*it)->getResources().getImage2()));
        else
            queueImages.push_back(sfg::Image::Create((*it)->getResources().getImage()));

        queueBox->Pack(queueImages.at(i));
        queueImages.at(i)->GetSignal( sfg::Widget::OnMouseRightPress ).Connect(
                  std::bind( &BattleGUI::showInfo, this, (*it)) );
        i++;
    }

}

void BattleGUI::showInfo(Hero *hero)
{
    completeStats(popStats, popIconImages, hero);
    sfg::Context::Get().GetEngine().SetProperty("Label#" + popStats[0]->GetId(), "FontSize", 16);
    popWindow->SetAllocation(setPopWindowPosition(sf::Mouse::getPosition(app_window)));
    desktop.BringToFront(popWindow);
    popWindow->Show(true);
}

void BattleGUI::showTargets(Action *action)
{
    spritesField->showTargets(action);
}

void BattleGUI::playAction(Action *action)
{
    spritesField->playAction(action);
    updateHPBars();
}

void BattleGUI::updateHPBars()
{
    spritesField->updateHPBars();
}

void BattleGUI::showDead(Hero *hero)
{
    spritesField->showDead(hero);
}

void BattleGUI::winPlayer1()
{
    finishWindow->Show(true);
    desktop.BringToFront(finishWindow);
    winnerLabel->SetText("PLAYER 1 WON!!!");
    queueWindow->SetState(sfg::Window::State::INSENSITIVE);
    infoWindow->SetState(sfg::Window::State::INSENSITIVE);
    buttonWindow->SetState(sfg::Window::State::INSENSITIVE);
    spritesField->setInsensitive();
}

void BattleGUI::winPlayer2()
{
    finishWindow->Show(true);
    desktop.BringToFront(finishWindow);
    winnerLabel->SetText("PLAYER 2 WON!!!");
    queueWindow->SetState(sfg::Window::State::INSENSITIVE);
    infoWindow->SetState(sfg::Window::State::INSENSITIVE);
    buttonWindow->SetState(sfg::Window::State::INSENSITIVE);
    spritesField->setInsensitive();
}

void BattleGUI::completeStats(sfg::Label::Ptr* array, sfg::Image::Ptr* imageArray, Hero* hero)
{
    array[0]->SetText(hero->getTemplate()->getName());
    array[1]->SetText(std::to_string( hero->getStats().hp.curr ) + " HP");
    array[2]->SetText(std::to_string(hero->getStats().damage.min) + " - " + std::to_string(hero->getStats().damage.max) + " DMG");
    switch(hero->getStats().kind)
    {
        case Kind::melee:
            array[3]->SetText("MELEE ATTACK");
            imageArray[2]->SetImage(typeImages[0]->GetImage());
            break;
        case Kind::range:
            array[3]->SetText("RANGE ATTACK");
            imageArray[2]->SetImage(typeImages[1]->GetImage());
            break;
    }
    array[4]->SetText(std::to_string( hero->getStats().initiative.val ) + " INIT");
    switch(hero->getStats().element)
    {
        case Element::neutral:
            array[5]->SetText("NEUTRAL");
            sfg::Context::Get().GetEngine().SetProperty("Label#" + array[5]->GetId(), "Color", sf::Color::Magenta);
            break;
        case Element::fire:
            array[5]->SetText("FIRE");
            sfg::Context::Get().GetEngine().SetProperty("Label#" + array[5]->GetId(), "Color", sf::Color::Red);
            break;
        case Element::water:
            array[5]->SetText("WATER");
            sfg::Context::Get().GetEngine().SetProperty("Label#" + array[5]->GetId(), "Color", sf::Color::Blue);
            break;
        case Element::earth:
            array[5]->SetText("EARTH");
            sfg::Context::Get().GetEngine().SetProperty("Label#" + array[5]->GetId(), "Color", sf::Color::Green);
            break;
    }
    array[6]->SetText("Special skill:\n" + hero->getSkill()->getName());
}

sf::FloatRect BattleGUI::setPopWindowPosition(sf::Vector2i mousePos)
{
    int Xmouse = mousePos.x, Ymouse = mousePos.y;

    if(YWINDOW > Y - Ymouse)
    {
        if(XWINDOW > X - Xmouse)
            return sf::FloatRect(Xmouse - XWINDOW, Ymouse - YWINDOW, XWINDOW, YWINDOW);
        else
            return sf::FloatRect(Xmouse, Ymouse - YWINDOW, XWINDOW, YWINDOW);
    }
    else if(XWINDOW > X - Xmouse)
        return sf::FloatRect(Xmouse - XWINDOW, Ymouse, XWINDOW, YWINDOW);
    else
        return sf::FloatRect(Xmouse+1, Ymouse+1, XWINDOW, YWINDOW);

}

void BattleGUI::showSkill()
{
    skillWindow->SetAllocation(sf::FloatRect((sf::Mouse::getPosition(app_window).x-skillInfo->GetAlignment().x)/2,
                                             sf::Mouse::getPosition(app_window).y-YSKILL-1,0,YSKILL));
    skillWindow->Show(true);
    desktop.BringToFront(skillWindow);
}
