#include "inc/selectiongui.h"
#define XSIZE 800
#define YSIZE 600
#define XINFO 450
#define YINFO 180
#define XFIELD 270
#define YFIELD 300
#define XFRAME 30
#define YFRAME 20
#define XPOINTS 125
#define YPOINTS 130
#define XSCROLL 350
#define XBUTTONS 450
#define YBUTTONS 80
#define XBUTTONS2 135
#define YBUTTONS2 220
#define FRAME 10
#define N 16 //debug

SelectionGUI::SelectionGUI()
    :
      app_window( sf::VideoMode( XSIZE, YSIZE ), "McArena", sf::Style::Titlebar | sf::Style::Close ),

      //Boxes
      infoWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      infoBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL)),
      pointsWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      pointsBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL)),
      fieldWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      fieldBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL)),

      //Heroes menu
      scrollwin(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      scrollwinbox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL, FRAME)),
      scroll(sfg::ScrolledWindow::Create()),
      table(sfg::Table::Create()),
      tablebox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL)),

      //Main box
      buttonsWindow(sfg::Window::Create(sfg::Window::Style::NO_STYLE)),
      buttonsBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 20)),
      menuButton(sfg::Button::Create( "MAIN MENU" )),
      discardButton(sfg::Button::Create( "DISCARD" )),
      startButton(sfg::Button::Create("START")),

      //Player box
      playerWindow(sfg::Window::Create(sfg::Window::Style::NO_STYLE)),
      playerBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 15)),
      player1Button(sfg::Button::Create( "PLAYER1" )),
      player2Button(sfg::Button::Create( "PLAYER2" ))

{
    app_window.resetGLStates();
    backgroundT.loadFromFile("src/selectBACK.jpg");
    background.setTexture(backgroundT);

    //Boxes
    desktop.Add(infoWindow);
    infoWindow->Add(infoBox);
    infoWindow->SetAllocation(sf::FloatRect(XSIZE-XINFO,0,XINFO,YINFO));
    desktop.Add(pointsWindow);
    pointsWindow->Add(pointsBox);
    pointsWindow->SetAllocation(sf::FloatRect(XSIZE-XPOINTS,YINFO,XPOINTS,YPOINTS));
    desktop.Add(fieldWindow);
    fieldWindow->Add(fieldBox);
    fieldWindow->SetAllocation(sf::FloatRect(XSCROLL+XFRAME,YINFO+YFRAME,XFIELD,YFIELD));



    //Main window
    desktop.Add(buttonsWindow);
    buttonsWindow->Add(buttonsBox);
    buttonsWindow->SetAllocation(sf::FloatRect( XSIZE-XBUTTONS , YSIZE-YBUTTONS, XBUTTONS, YBUTTONS));

    buttonsBox->Pack(menuButton);
    buttonsBox->Pack(discardButton);
    buttonsBox->Pack(startButton);

    //Player window
    desktop.Add(playerWindow);
    playerWindow->Add(playerBox);
    playerWindow->SetAllocation(sf::FloatRect( XSIZE-XBUTTONS2, YSIZE-YBUTTONS2-YBUTTONS, XBUTTONS2, YBUTTONS2));

    playerBox->Pack(player1Button);
    playerBox->Pack(player2Button);

    //Heroes window
    desktop.Add(scrollwin);
    scroll->SetScrollbarPolicy( sfg::ScrolledWindow::HORIZONTAL_NEVER| sfg::ScrolledWindow::VERTICAL_ALWAYS);
    tablebox->Pack(table);
    scroll->AddWithViewport(tablebox);
    scroll->SetRequisition( sf::Vector2f( XSCROLL - FRAME*2, YSIZE - FRAME*2) );
    scrollwinbox->Pack(scroll, false, true);
    scrollwin->Add(scrollwinbox);

    //ОТЛАДОЧНОЕ ЗАПОЛНЕНИЕ!!!
    sf::Image heropic;
    heropic.loadFromFile("src/heroPIC.jpg");
    sfg::Image::Ptr images[N];
    for(int i=0;i<N;i++){
        images[i]=sfg::Image::Create(heropic);
        table->Attach(images[i],sf::Rect<sf::Uint32>( i%2, floor(i/2+0.5), 1, 1),sfg::Table::FILL, sfg::Table::FILL);
    }


    //Signals
    //settingsButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &MenuGUI::clickedSettings, this ) );

}

void SelectionGUI::show()
{
   timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(update()));
   timer->start(10);
}

void SelectionGUI::update()
{
    if (app_window.isOpen())
    {
        sf::Event event;
        while (app_window.pollEvent(event))
        {
              desktop.HandleEvent(event);

            if (event.type == sf::Event::Closed)
               app_window.close();
        }
        desktop.Update( 10 );
        app_window.clear();
        app_window.draw(background);
        sfgui.Display(app_window);
        app_window.display();
    }
}

void SelectionGUI::hide()
{

}

void SelectionGUI::setActiveHero(Hero *)
{

}

void SelectionGUI::setHeroGroup(HeroGroup *)
{

}

void SelectionGUI::setCost()
{

}

void SelectionGUI::setPlayer(Player *)
{

}

void SelectionGUI::showCross()
{

}
