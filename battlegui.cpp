#include "inc/battlegui.h"

#define XICON 150
#define YICON 180
#define XSICON 50
#define YSICON 60
#define XINFO 200
#define YINFO 500
#define YBUTTON 50
#define TIMEUPDATE 25

BattleGUI::BattleGUI(MainWindow& _app_window, QObject *parent)
    :
      QObject(parent),

      app_window(_app_window),
      queueWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      buttonWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      infoWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),

      //Queuewindow
      queueBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 15)),
      separator(sfg::Separator::Create(sfg::Separator::Orientation::VERTICAL)),

      //Buttonwindow
      buttonBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 75)),
      attackButton(sfg::Button::Create( "ATACK" )),
      skillButton(sfg::Button::Create( "SKILL" )),

      //InfoWindow
      infoBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 15)),
      skillsBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 15)),
      picBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 15)),
      labelBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 15)),


      hp(sfg::Label::Create(sf::String("80 hp"))),
      dmg(sfg::Label::Create(sf::String(" 27 dmg"))),
      init(sfg::Label::Create(sf::String("70 init"))),
      element(sfg::Label::Create(sf::String("fire"))),

      frame(sfg::Frame::Create(sf::String("Hero Name")))

{
    app_window.resetGLStates();
    backgroundT.loadFromFile("src/battleBACK.jpg");
    background.setTexture(backgroundT);

    //Queuewindow
    queueWindow->Add(queueBox);

    //for debug start
    sf::Image sfImage;
    sfImage.loadFromFile("src/debug/hat.png");

    image = sfg::Image::Create(sfImage);

    queueBox->Pack(image);
    queueBox->Pack(separator);

    for(int i=0; i<11; i++)
    {
        image = sfg::Image::Create(sfImage);
        queueBox->Pack(image);
    }
    //for debug end

    desktop.Add(queueWindow);
    queueWindow->SetAllocation(sf::FloatRect( 0 , YINFO, app_window.getX(), app_window.getY() - YINFO));

    //Buttonwindow

    buttonWindow->Add(buttonBox);
    buttonBox->Pack(skillButton);
    buttonBox->Pack(attackButton);

    desktop.Add(buttonWindow);
    buttonWindow->SetAllocation(sf::FloatRect( XINFO , YINFO - YBUTTON, app_window.getX() - XINFO, YBUTTON));

    //Ifowindow

    //for debug start
    sfImage.loadFromFile("src/debug/might.png");

    image = sfg::Image::Create(sfImage);
    infoBox->Pack(image);
    //for debug start

    infoWindow->Add(frame);
    frame->Add(infoBox);
    infoBox->Pack(skillsBox);
    skillsBox->Pack(picBox);
    skillsBox->Pack(labelBox);

    labelBox->Pack(hp);
    labelBox->Pack(dmg);
    labelBox->Pack(init);
    labelBox->Pack(element);

    //for debug start
    sfImage.loadFromFile("src/debug/icon.png");


    for(int i = 0; i < 4 ; i++)
    {
        image = sfg::Image::Create(sfImage);
        picBox->Pack(image);
    }
    //for debug end

    desktop.Add(infoWindow);
    infoWindow->SetAllocation(sf::FloatRect( 0 , 0, XINFO, YINFO));

    //Signals
    skillButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                std::bind( &BattleGUI::clickedButton, this, ButtonPressed::SKILL ) );
    attackButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                std::bind( &BattleGUI::clickedButton, this, ButtonPressed::ATTACK ) );
}

void BattleGUI::clickedButton(ButtonPressed Button)
{
    switch (Button)
    {
        case ATTACK: selectedAction(nullptr); break;
        case SKILL: selectedAction(nullptr); break;
    }
}

void BattleGUI::show()
{
   queueWindow->Show(true);
   buttonWindow->Show(true);
   infoWindow->Show(true);
   timer = app_window.newTimer();
   connect(timer, SIGNAL(timeout()), this, SLOT(update()));
   timer->start(TIMEUPDATE);
}

void BattleGUI::update()
{
    static bool flag = true;

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
        }
        desktop.Update( 0.5 );

        app_window.clear();
        app_window.draw(background);
        sfgui.Display(app_window);
        app_window.display();
    }

    else if(flag)
    {
        flag = false;
        closed();
    }
}


void BattleGUI::hide()
{
    queueWindow->Show(false);
    buttonWindow->Show(false);
    infoWindow->Show(false);
    app_window.deleteTimer();
    app_window.clear(sf::Color::Black);
    app_window.display();
}

void BattleGUI::setActiveHero(Hero *)
{

}

void BattleGUI::setQueue(HeroQueue *)
{

}

void BattleGUI::showInfo(Hero *)
{

}

void BattleGUI::showTargets(Action *)
{

}

void BattleGUI::playAction(Action *)
{

}