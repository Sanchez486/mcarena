#include "inc/battlegui.h"

#define XICON 83
#define YICON 100
#define XINFO 220
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

      //Buttonwindow
      buttonBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 75)),
      attackButton(sfg::Button::Create( "ATACK" )),
      skillButton(sfg::Button::Create( "SKILL" )),

      //InfoWindow
      infoBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL)),
      skillsBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL)),
      picBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL)),
      labelBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL)),

      frame(sfg::Frame::Create(sf::String(""))),

      //Sprite Field
      spritesField(nullptr),

      //Pop window
      popWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      popSkillsBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL)),
      popBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL)),
      popPicBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL)),
      popLabelBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL))

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

    for(int i = 0; i < 12; i++)
    {
        queueImages[i] = sfg::Image::Create();
        queueBox->Pack(queueImages[i]);
    }

    desktop.Add(queueWindow);
    queueWindow->SetAllocation(sf::FloatRect(0,app_window.getY() - YQTOTAL, app_window.getX(), YICON+FRAME*2+YSCROLLBAR));

    //Buttonwindow

    buttonWindow->Add(buttonBox);
    buttonBox->Pack(skillButton);
    buttonBox->Pack(attackButton);

    desktop.Add(buttonWindow);
    buttonWindow->SetAllocation(sf::FloatRect( XINFO , app_window.getY() - YQTOTAL - YBUTTON, app_window.getX() - XINFO, YBUTTON));

    //Ifowindow

    infoImage = sfg::Image::Create(sf::Image());
    infoBox->Pack(infoImage);

    infoWindow->Add(frame);
    frame->Add(infoBox);
    infoBox->Pack(skillsBox);
    skillsBox->Pack(picBox);
    skillsBox->Pack(labelBox);

    for(int i = 0; i < 6; i++)
        stats[i] = sfg::Label::Create(sf::String(""));

    for(int i = 1; i < 6; i++)
        labelBox->Pack(stats[i]);

    stats[5]->SetId("element1");

    //for debug start
    sf::Image sfImage;
    sfImage.loadFromFile("res/img/icons/icon.png");

    sfg::Image::Ptr image;
    for(int i = 0; i < 5 ; i++)
    {
        image = sfg::Image::Create(sfImage);
        picBox->Pack(image);
    }
    //for debug end

    desktop.Add(infoWindow);
    infoWindow->SetAllocation(sf::FloatRect( 0 , 0, XINFO,app_window.getY() - YQTOTAL));

    //Pop window
    popWindow->Add(popBox);
    popBox->Pack(popSkillsBox);
    popSkillsBox->Pack(popPicBox);
    popSkillsBox->Pack(popLabelBox);

    for(int i = 0; i < 5; i++)
    {
        image = sfg::Image::Create(sfImage);
        popPicBox->Pack(image);
    }

    for(int i = 0; i < 6; i++)
    {
        popStats[i] = sfg::Label::Create(sf::String(""));
        if(i != 0)
            popLabelBox->Pack(popStats[i]);
        else
            popBox->PackStart(popStats[i]);
    }
    popWindow->Show(false);
    desktop.Add(popWindow);

    popStats[0]->SetId("title");
    popStats[5]->SetId("element2");

    popWindow->SetId("window");
    sfg::Context::Get().GetEngine().SetProperty("Window#" + popWindow->GetId(),
                                                "BackgroundColor", sf::Color(0, 0, 0, 200));

    //Signals
    skillButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                std::bind( &BattleGUI::clickedButton, this, ButtonPressed::SKILL ) );
    attackButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                std::bind( &BattleGUI::clickedButton, this, ButtonPressed::ATTACK ) );
}

BattleGUI::~BattleGUI()
{
    if(spritesField != nullptr)
        delete spritesField;
}

void BattleGUI::clickedButton(ButtonPressed Button)
{
    switch (Button)
    {
        case ATTACK:
            selectedAction(activeHero->getAttack());
            break;
        case SKILL:
            selectedAction(activeHero->getSkill());
            break;
    }
}

void BattleGUI::show()
{
   queueWindow->Show(true);
   buttonWindow->Show(true);
   infoWindow->Show(true);
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
    activeHero = hero;
    infoImage->SetImage(hero->getResources().getImage2());
    completeStats(stats, hero);
    frame->SetLabel(stats[0]->GetText());
    spritesField->setActiveHero(hero);
}

void BattleGUI::setQueue(HeroQueue *queue)
{
    if(queue == nullptr)
        std::cerr << "queue is nullptr" << std::endl;

    int i = 0;
    for(auto it = queue->begin(), end = queue->end(); it != end; it++)
    {
        if (it == queue->begin())
            queueImages[i]->SetImage((*it)->getResources().getImage2());
        else
            queueImages[i]->SetImage((*it)->getResources().getImage());

        queueImages[i]->GetSignal( sfg::Widget::OnMouseRightPress ).Connect(
                    std::bind( &BattleGUI::showInfo, this, (*it)) );
        i++;
    }
}

void BattleGUI::showInfo(Hero *hero)
{
    completeStats(popStats, hero);
    sfg::Context::Get().GetEngine().SetProperty("Label#" + popStats[0]->GetId(), "FontSize", 16);
    popWindow->SetAllocation(setPopWindowPosition(sf::Mouse::getPosition(app_window)));
    desktop.BringToFront(popWindow);
    popWindow->Show(true);
}

void BattleGUI::showTargets(Action *action)
{
    spritesField->showTargets(action);
}

void BattleGUI::playAction(Action *)
{

}

void BattleGUI::completeStats(sfg::Label::Ptr* array, Hero* hero)
{

    array[0]->SetText(hero->getTemplate()->getName());
    array[1]->SetText(std::to_string( hero->getStats().hp.max ) + " HP");
    array[2]->SetText(std::to_string(hero->getStats().damage.min) + " - " + std::to_string(hero->getStats().damage.max) + " DMG");
    switch(hero->getStats().kind)
    {
        case Kind::melee:
            array[3]->SetText("MELEE ATTACK");
            break;
        case Kind::range:
            array[3]->SetText("RANGE ATTACK");
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
