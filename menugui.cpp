#include "inc/menugui.h"
#define XWINDOW 300
#define YWINDOW 400
#define YOFFSET 80
#define YMCARENA 100
#define XYSETTINGS 200
#define XRULES 80
#define YRULES 30
#define TIMEUPDATE 25 //Window updates every 25 milliseconds (40 fps)

MenuGUI::MenuGUI(MainWindow& _app_window, QObject *parent)
    :
      QObject(parent),
      app_window(_app_window),

      //Main window
      window(sfg::Window::Create(sfg::Window::Style::NO_STYLE)),
      box(sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 20)),
      playButton(sfg::Button::Create("Play")),
      rulesButton(sfg::Button::Create( "How to play" )),
      exitButton(sfg::Button::Create( "Exit" )),
      soundBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL,30)),
      soundToggle(sfg::Image::Create()),
      musicToggle(sfg::Image::Create()),

      //How to play window
      rulesWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      rulesBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 4)),
      okButton(sfg::Button::Create( "Ok" )),
      rules(sfg::Label::Create(""))

{
    app_window.resetGLStates();
    backgroundT.loadFromFile("res/img/background/menuBACK.jpg");
    background.setTexture(backgroundT);
    desktop.Add(window);

    mcArenaT.loadFromFile("res/img/icons/McArena.png");
    mcArena.setTexture(mcArenaT);
    mcArena.setOrigin(mcArena.getGlobalBounds().width/2,
                      mcArena.getGlobalBounds().height/2);
    mcArena.setPosition(app_window.getX()/2, YMCARENA);

    //Main window
    window->Add(box);
    window->SetAllocation(sf::FloatRect( (app_window.getX()-XWINDOW)/2 ,
                                     (app_window.getY()-YWINDOW)/2 + YOFFSET, XWINDOW, YWINDOW));
    box->Pack(soundBox);
    box->Pack(playButton);
    box->Pack(rulesButton);
    box->Pack(exitButton);

    //How to play window
    rulesWindow->Add(rulesBox);
    rulesBox->Pack(rules, false, true);
    rulesBox->Pack(okButton);

    setLabel();
    rulesWindow->SetPosition(sf::Vector2f(XRULES, YRULES));

    desktop.Add(rulesWindow);
    rulesWindow->Show(false);
    rules->SetRequisition(sf::Vector2f(app_window.getX()-3*XRULES,app_window.getY()-2*YRULES-rulesButton->GetAllocation().height));

    //Sound Box
    noSoundImage.loadFromFile("res/img/icons/no_sound.png");
    soundImage.loadFromFile("res/img/icons/sound.png");
    musicImage.loadFromFile("res/img/icons/music.png");
    noMusicImage.loadFromFile("res/img/icons/no_music.png");
    soundBox->Pack(soundToggle);
    soundBox->Pack(musicToggle);
    soundToggle->SetImage(soundImage);
    musicToggle->SetImage(musicImage);

    //Signals
    playButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedButton, this, ButtonPressed::PLAY ) );
    rulesButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                std::bind( &MenuGUI::clickedButton, this, ButtonPressed::HOW_TO_PLAY ) );
    exitButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedButton, this, ButtonPressed::EXIT ) );
    soundToggle->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedButton, this, ButtonPressed::SOUND ) );
    musicToggle->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedButton, this, ButtonPressed::MUSIC ) );
    okButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                std::bind( &MenuGUI::clickedButton, this, ButtonPressed::OK ) );

    //coloring
    playButton->SetClass("buttons");
    rulesButton->SetClass("buttons");
    exitButton->SetClass("buttons");
    okButton->SetClass("smallButtons");
    rulesWindow->SetClass("windows");
}

//Connecting Buttons and Qt signals
void MenuGUI::clickedButton(ButtonPressed Button)
{
    app_window.playButtonSound();
    switch (Button)
    {
        case PLAY:
            clickedPlay();
            break;
        case HOW_TO_PLAY:
            desktop.BringToFront(rulesWindow);
            window->SetState(sfg::Window::State::INSENSITIVE);
            rulesWindow->Show(true);
            break;
        case OK:
            rulesWindow->Show(false);
            window->SetState(sfg::Window::State::NORMAL);
            break;
        case EXIT:
            clickedExit();
            break;
        case MUSIC:
            if (app_window.ToggleMusic())
                musicToggle->SetImage(musicImage);
            else
                musicToggle->SetImage(noMusicImage);
            break;
        case SOUND:
            if (app_window.isSound())
            {
                app_window.setSound(false);
                soundToggle->SetImage(noSoundImage);
            }
            else
            {
                app_window.setSound(true);
                soundToggle->SetImage(soundImage);
            }
            break;
    }
}

void MenuGUI::show()
{
   window->Show(true);
   connect(app_window.getTimer(), SIGNAL(timeout()), this, SLOT(update()));
   app_window.getTimer()->start(TIMEUPDATE);
}

void MenuGUI::update()
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
        desktop.Update( TIMEUPDATE );
        app_window.clear();
        app_window.draw(background);
        app_window.draw(mcArena);
        sfgui.Display(app_window);
        app_window.display();
    }

    else if(flag)
    {
        flag = false;
        closed();
    }
}

void MenuGUI::hide()
{
    window->Show(false);
    //rulesWindow->Show(false);
    disconnect(app_window.getTimer(), SIGNAL(timeout()), this, SLOT(update()));
    app_window.clear(sf::Color::Black);
    app_window.display();
}

void MenuGUI::setSounds(bool)
{

}

void MenuGUI::setMusic(bool)
{

}

void MenuGUI::setLabel()
{
    str =   ""
            "Main rules.\n"
            "\n"
            "McArena is the game, where two players fight to each other. The goal is to defeat all opponent's\n"
            "heroes. Both players pick a group of 6 heroes from the list, any hero may be picked more than\n"
            "once. Each hero has health, damage and initiative points, special skill, it belongs to some element\n"
            "(Water, Earth, Fire, Neutral) and also is melee or range. During the battle, all hero's characteristics\n"
            "may be viewed, if you right-click on that hero. To find out what special skill does, move the mouse\n"
            "cursor on skill name in left hero's info window.\n"
            "\n"
            "Element system.\n"
            "\n"
            "Heroes can get and deal 25% more damage, depending on the element they belong to: Earth is\n"
            "stronger than Water, but is weaker than Fire; Fire is stronger than Earth, but is weaker than Water;\n"
            "Water is stronger than Fire, but is weaker than Earth. Heroes of Neutral element have no bonuses in\n"
            "damage. When hero of a stronger element deals damage to a weaker one, its damage is multiplied\n"
            "by 1.25. If attacking hero has weaker element, its damage is multiplied by 0.8.\n"
            "\n"
            "Queue system.\n"
            "\n"
            "Battles take place on the \"battle field\". Heroes take turns one after another. Turns order is set\n"
            "regarding the heroes initiative points, may be changed during the battle and is diaplyed at the\n"
            "bottom of the screen. Every time, when some hero takes its turn, the initiative of every hero is\n"
            "increased by its initiative value, until a threshold will be reached. The overreaching of the threshold\n"
            "intiates a hero turn. Among all heroes, whose accumulated initiative overreached a threshold, the\n"
            "hero with the lowest initiativee takes turn. If this value is equal for several heroes, the turn is\n"
            "defined by random.\n"
            "\n"
            "Heroes Selection.\n"
            "\n"
            "When it's hero's turn, he can use either Attack or Skill. Range heroes are able to attack any\n"
            "opponent's hero, whereas melees can only choose the nearest target in each line. Furthermore,\n"
            "melee hero can't attack if there is an ally in front of him. It is a good idea to place melees at the\n"
            "front line, as they have more health and are not able to attack from the back line until a hero in\n"
            "front of them will be killed. Rangers are best when placed at the back line, but it is possible to\n"
            "place them at the front line too."
            ;
    rules->SetText(str);    
}
