#include "inc/menugui.h"
#define XWINDOW 300
#define YWINDOW 400
#define XYSETTINGS 200
#define TIMEUPDATE 25 //Window updates every 25 milliseconds (40 fps)

MenuGUI::MenuGUI(MainWindow& _app_window, QObject *parent)
    :
      QObject(parent),
      app_window(_app_window),

      //Main window
      window(sfg::Window::Create(sfg::Window::Style::NO_STYLE)),
      box(sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 20)),
      playButton(sfg::Button::Create("Play")),
      playWithCpuButton(sfg::Button::Create( "Play with CPU" )),
      exitButton(sfg::Button::Create( "Exit" )),
      soundBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL)),
      soundToggle(sfg::Image::Create()),
      musicToggle(sfg::Image::Create())
{
    app_window.resetGLStates();
    backgroundT.loadFromFile("res/img/background/menuBACK.jpg");
    background.setTexture(backgroundT);
    desktop.Add(window);


    //Main window
    window->Add(box);
    window->SetAllocation(sf::FloatRect( (app_window.getX()-XWINDOW)/2 , (app_window.getY()-YWINDOW)/2, XWINDOW, YWINDOW));

    box->Pack(playButton);
    box->Pack(playWithCpuButton);
    box->Pack(exitButton);

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
    playWithCpuButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                std::bind( &MenuGUI::clickedButton, this, ButtonPressed::PLAY_WITH_CPU ) );
    exitButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedButton, this, ButtonPressed::EXIT ) );
    soundToggle->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedButton, this, ButtonPressed::SOUND ) );
    musicToggle->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedButton, this, ButtonPressed::MUSIC ) );

}

//Connecting Buttons and Qt signals
void MenuGUI::clickedButton(ButtonPressed Button)
{
    app_window.playButtonSound();
    switch (Button)
    {
        case PLAY: clickedPlay(); break;
        case PLAY_WITH_CPU: clickedPlayCPU(); break;
        case EXIT: clickedExit(); break;
        case MUSIC:
        if (app_window.ToggleMusic()) musicToggle->SetImage(musicImage);
        else musicToggle->SetImage(noMusicImage);
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
