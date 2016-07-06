#include "inc/menugui.h"
#define XSIZE 800
#define YSIZE 600
#define XWINDOW 300
#define YWINDOW 400
#define XYSETTINGS 200

MenuGUI::MenuGUI()
    :
      app_window( sf::VideoMode( XSIZE, YSIZE ), "McArena", sf::Style::Titlebar | sf::Style::Close ),

      //Main window
      window(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      box(sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 25)),
      playButton(sfg::Button::Create( "PLAY" )),
      playWithCpuButton(sfg::Button::Create( "Play with CPU" )),
      settingsButton(sfg::Button::Create( "Settings" )),
      exitButton(sfg::Button::Create( "Exit" )),

      //Settings window
      settingsWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      sharedBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 15)),
      settingsBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 15)),
      okBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 15)),
      soundButton(sfg::Button::Create( "Music enabled" )),
      musicButton(sfg::Button::Create( "Sound enabled" )),
      okButton(sfg::Button::Create( "OK" ))


{
    app_window.resetGLStates();

    //Main window
    desktop.Add(window);
    window->Add(box);
    window->SetAllocation(sf::FloatRect( (XSIZE-XWINDOW)/2 , (YSIZE-YWINDOW)/2, XWINDOW, YWINDOW));

    box->Pack(playButton);
    box->Pack(playWithCpuButton);
    box->Pack(settingsButton);
    box->Pack(exitButton);

    //Settings window
    desktop.Add(settingsWindow);
    settingsWindow->Add(sharedBox);
    settingsWindow->Show(false);
    settingsWindow->SetAllocation(sf::FloatRect( (XSIZE-XYSETTINGS)/2 - 15, (YSIZE-XYSETTINGS)/2, XYSETTINGS, XYSETTINGS));
    sharedBox->Pack(settingsBox);
    sharedBox->Pack(okBox);

    settingsBox->Pack(soundButton);
    settingsBox->Pack(musicButton);
    okBox->Pack(okButton);

    //Signals
    settingsButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedSettings, this ) );
    okButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedOk, this  ) );
    playButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedButton, this, ButtonPressed::PLAY ) );
    playWithCpuButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                std::bind( &MenuGUI::clickedButton, this, ButtonPressed::PLAY_WITH_CPU ) );
    exitButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedButton, this, ButtonPressed::EXIT ) );
    soundButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedButton, this, ButtonPressed::SOUND ) );
    musicButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedButton, this, ButtonPressed::MUSIC ) );
}

void MenuGUI::clickedSettings()
{
    settingsWindow->Show(true);
    desktop.BringToFront(settingsWindow);
    window->SetState(sfg::Widget::State::INSENSITIVE);
}
void MenuGUI::clickedOk()
{
    settingsWindow->Show(false);
    window->SetState(sfg::Widget::State::NORMAL);
}

//Connecting Button and Qt signals
void MenuGUI::clickedButton(ButtonPressed Button)
{
    switch (Button)
    {
        case PLAY: clickedPlay(); break;
        case PLAY_WITH_CPU: clickedPlayCPU(); break;
        case EXIT: clickedExit(); break;
        case MUSIC:clickedMusic();break;
        case SOUND:clickedSound(); break;
    }
}

void MenuGUI::show()
{
   timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(update()));
   timer->start(10);
}

void MenuGUI::update()
{
    if (app_window.isOpen())
    {
        sf::Event event;
        if (app_window.pollEvent(event))
        {
              desktop.HandleEvent(event);

            if (event.type == sf::Event::Closed)
               app_window.close();
        }
        desktop.Update( 0.5 );

        app_window.clear();
        sfgui.Display(app_window);
        app_window.display();
    }
}

void MenuGUI::hide()
{

}

void MenuGUI::setSounds(bool)
{

}

void MenuGUI::setMusic(bool)
{

}
