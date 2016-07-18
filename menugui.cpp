#include "inc/menugui.h"
#define XWINDOW 300
#define YWINDOW 400
#define YOFFSET 80
#define YMCARENA 100
#define XYSETTINGS 200
#define XRULES 110
#define YRULES 50
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
      rulesBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 300)),
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
        desktop.Update( 10 );
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
    str = "BBC is an abbreviation of \"British Broadcasting Corporation\"\n"
            ", which is the oldest British public service broadcaster.\n"
            "Nowadays it works all over the world, having a number of international programs.\n"
            "Of these, there are BBC World Service, providing a multimedia broadcasting online\n"
            "and via wireless handheld devices in different languages; BBC World News, broadcasting\n"
            "in English 24 hours a day in many countries across the world; BBC Worldwide, promoting\n"
            "the BBC content and BBC brand at all by, particularly, opening offices around the world\n"
            "with local staff; and BBC Monitoring, providing news, information and comment gathered\n "
            "from mass media around the world. ";
    rules->SetText(str);
}
