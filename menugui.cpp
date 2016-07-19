#include "inc/menugui.h"
#define XWINDOW 300
#define YWINDOW 400
#define YOFFSET 80
#define YMCARENA 100
#define XYSETTINGS 200
#define XRULES 80
#define YRULES 0
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
      soundBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL)),
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

    box->Pack(playButton);
    box->Pack(rulesButton);
    box->Pack(exitButton);

    //How to play window
    rulesWindow->Add(rulesBox);
    rulesBox->Pack(rules);
    rulesBox->Pack(okButton, false, false);

    setLabel();
    rulesWindow->SetAllocation(sf::FloatRect(XRULES, YRULES, app_window.getX() - 2*XRULES,
                               app_window.getY() - 2*YRULES));

    desktop.Add(rulesWindow);
    rulesWindow->Show(false);

    //Sound Box
    noSoundImage.loadFromFile("res/img/icons/no_sound.png");
    soundImage.loadFromFile("res/img/icons/sound.png");
    musicImage.loadFromFile("res/img/icons/music.png");
    noMusicImage.loadFromFile("res/img/icons/no_music.png");
    soundBox->Pack(soundToggle);
    soundBox->Pack(musicToggle);
    soundToggle->SetImage(soundImage);
    musicToggle->SetImage(musicImage);
    box->Pack(soundBox);

    //Signals
    playButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedButton, this, ButtonPressed::PLAY ) );
    rulesButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                std::bind( &MenuGUI::clickedButton, this, ButtonPressed::HOW_TO_PLAY ) );
    exitButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedButton, this, ButtonPressed::EXIT ) );
    soundToggle->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedButton, this, ButtonPressed::SOUND ) );
    musicToggle->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedButton, this, ButtonPressed::MUSIC ) );
    okButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                std::bind( &MenuGUI::clickedButton, this, ButtonPressed::OK ) );
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
    rulesWindow->Show(false);
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
            "Main rules."
            "\n\n"
            "McArena  is the game, where two players play to each other. The goal of this game is to kill all"
            "opponents\' heroes. Both players are allowed to pick any 6 heroes from the list of 16, furthemore "
            "any hero may be picked more than once. Every hero has health, damage and initiative points, its"
            "special skill, and it also belongs to some element (Water, Earth, Fire, Neutral) and is Melee or"
            "Range. During the battle, all hero characteristics will be shown, if you do a right click on the sprite"
            "or the image of the hero, you are interested in. In order to learn more about what special skill really"
            "does, you are to pass the mouse on skill name in left hero info window, and there will be shown a"
            "skill description."
            "\n\n"
            "Element system."
            "\n\n"
            "Heroes can get and deal 25% more damage, depending on the element they belong to: Earth is"
            "stronger than Water, but is weaker than Fire; Fire is stronger than Earth, but is weaker than Water;"
            "Water is stronger than Fire, but is weaker than Earth. Heroes of Neutral element have no bonuses in"
            "damage. A hero of a stronger element deals an increased damage, a hero of a weaker one -"
            "decreased damage. If attacking hero element is stronger than attacked hero element, than the"
            "damage coefficient equals 1.25; if it is wekaer, than the damage coefficient equals 0.75; in orther"
            "cases - 1."
            "\n\n"
            "Queue system."
            "\n\n"
            "Battles take place on the \"battle field\". Heroes take turns one after another. Turns queue is set"
            "regarding the heroes initiative points, may be changed during the battle and is diaplyed at the"
            "bottom of the screen. Every time, when some hero takes its turn, the initiative of every hero is"
            "increased by its initiative value, until a threshold will be reached. The overreaching of the threshold"
            "intiates a hero turn. Among all heroes, whose accumulated initiative overreached a threshold, the"
            "hero with the lowest initiativee takes turn. If this value is equal for several heroes, the turn is"
            "defined by random."
            "\n\n"
            "Heroes Selection."
            "\n\n"
            "In the single turn, the single hero can use Attack or Skill. Range is able to attack all opponent"
            "heroes, whereas Melee is able to attack just opponent front line heroes and only when it has no"
            "friendlies in front of them. During the hero choosing and placing, it is a good idea to place Melees"
            "at the front line, as they has higher HP value and are not able to attack at the back line until a hero"
            "in front of them will be killed. Ranges should be apparently placed at the back line, however it is"
            "possible to place them at the front line too, in order to have more heroes, who can attack all 6"
            "opponent heroes."
            ;
    rules->SetText(str);
    rules->SetLineWrap(true);
}
