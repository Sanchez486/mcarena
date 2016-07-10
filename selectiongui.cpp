#include "inc/selectiongui.h"
#define YINFO 180
#define XFIELD 166
#define YFIELD 300
#define XPOINTS 180
#define YPOINTS 130
#define XSCROLL 166
#define YBUTTONS 80
#define XPLAYERS 190
#define YPLAYERS 200
#define FRAME 10
#define XSCROLLBAR 30 //default scroll width of sfg::ScrollWindow
#define N 16 //debug

SelectionGUI::SelectionGUI(MainWindow& _app_window, QObject *parent)
    :
      QObject(parent),

      app_window(_app_window),
      //Boxes
      infoWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      infoLabelWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      infoBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL,FRAME)),
      infoTable(sfg::Table::Create()),
      pointsWindow(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      pointsBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, FRAME)),
      pointsLabel(sfg::Label::Create("POINTS: ")),
      fieldWindow(sfg::Window::Create(sfg::Window::Style::NO_STYLE)),
      fieldBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, FRAME)),
      fieldTable(sfg::Table::Create()),

      //Heroes menu
      scrollwin(sfg::Window::Create(sfg::Window::Style::BACKGROUND)),
      scrollwinbox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL, FRAME)),
      scroll(sfg::ScrolledWindow::Create()),
      table(sfg::Table::Create()),
      tablebox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL)),
      activeHeroNumber(0),
      pendingImage(sfg::Image::Create()),
      pendingImage2(sfg::Image::Create()),

      //Main box
      buttonsWindow(sfg::Window::Create(sfg::Window::Style::NO_STYLE)),
      buttonsBox(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 15)),
      menuButton(sfg::Button::Create( "MAIN MENU" )),
      discardButton(sfg::Button::Create( "DISCARD" )),
      startButton(sfg::Button::Create("START")),

      //Player box
      playerWindow(sfg::Window::Create(sfg::Window::Style::NO_STYLE)),
      playerBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 20)),
      player1Button(sfg::Button::Create( "PLAYER1" )),
      player2Button(sfg::Button::Create( "PLAYER2" )),

      label(sfg::Label::Create("Choose a hero!!!"))

{
    app_window.resetGLStates();
    backgroundT.loadFromFile("src/selectBACK.jpg");
    background.setTexture(backgroundT);

    //Boxes
    desktop.Add(infoWindow);
    infoWindow->Add(infoBox);
    infoWindow->SetAllocation(sf::FloatRect(XSCROLL+FRAME*2+XSCROLLBAR,0,app_window.getX()-XSCROLL-FRAME*2-XSCROLLBAR,YINFO));
    desktop.Add(infoLabelWindow);
    infoLabelWindow->Add(label);
    infoLabelWindow->SetAllocation(infoWindow->GetAllocation());
    infoBox->Pack(infoTable);
    desktop.Add(pointsWindow);
    pointsWindow->Add(pointsBox);
    pointsWindow->SetAllocation(sf::FloatRect(app_window.getX()-XPOINTS,YINFO,XPOINTS,YPOINTS));
    pointsBox->Pack(pointsLabel);
    desktop.Add(fieldWindow);
    fieldWindow->Add(fieldBox);
    fieldWindow->SetAllocation(sf::FloatRect((app_window.getX()+XSCROLL+FRAME*2+XSCROLLBAR-XPOINTS-XFIELD)/2,(app_window.getY()-FRAME*2-YBUTTONS+YINFO-YFIELD)/2,XFIELD,YFIELD));
    fieldBox->Pack(fieldTable);
    //debug
    sf::Image fieldImg;
    fieldImg.loadFromFile("res/img/images/sonic_img.png");
    for (int i=0;i<6;i++){
        sfg::Image::Ptr newimg = sfg::Image::Create(fieldImg);
        fieldTable->Attach(newimg,sf::Rect<sf::Uint32>( i%2, floor(i/2+0.5), 1, 1),sfg::Table::FILL, sfg::Table::FILL);
    }
    sf::Image icoImg;
    icoImg.loadFromFile("src/ico.jpg");
    sfg::Image::Ptr pic2 = sfg::Image::Create(fieldImg);
    for (int i=0;i<7;i++) infoLabels[i]= sfg::Label::Create("");
    for (int i=0;i<5;i++) infoPics[i]= sfg::Image::Create(icoImg);
    infoLabels[0]->SetText("Pretty Long Hero Name");
    infoLabels[1]->SetText("X HP");
    infoLabels[2]->SetText("X DMG");
    infoLabels[3]->SetText("X INIT");
    infoLabels[4]->SetText("Element: Fire");
    infoLabels[5]->SetText("X PTS");
    infoLabels[6]->SetText("Special Skill: very very long skill description, really long man, but it's OK");

    infoTable->Attach(pic2,sf::Rect<sf::Uint32>(0, 0, 1, 3),sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND );
    infoTable->Attach(infoLabels[0],sf::Rect<sf::Uint32>(1, 0, 2, 1),sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);
    infoTable->Attach(infoPics[0],sf::Rect<sf::Uint32>(1, 1, 1, 1),sfg::Table::EXPAND | sfg::Table::FILL, sfg::Table::EXPAND | sfg::Table::FILL);
    infoTable->Attach(infoPics[1],sf::Rect<sf::Uint32>(1, 2, 1, 1),sfg::Table::EXPAND | sfg::Table::FILL, sfg::Table::EXPAND | sfg::Table::FILL);
    infoTable->Attach(infoPics[2],sf::Rect<sf::Uint32>(3, 1, 1, 1),sfg::Table::EXPAND | sfg::Table::FILL, sfg::Table::EXPAND | sfg::Table::FILL);
    infoTable->Attach(infoPics[3],sf::Rect<sf::Uint32>(3, 2, 1, 1),sfg::Table::EXPAND | sfg::Table::FILL, sfg::Table::EXPAND | sfg::Table::FILL);
    infoTable->Attach(infoPics[4],sf::Rect<sf::Uint32>(3, 0, 1, 1),sfg::Table::EXPAND | sfg::Table::FILL, sfg::Table::EXPAND | sfg::Table::FILL);
    infoTable->Attach(infoLabels[1],sf::Rect<sf::Uint32>(2, 1, 1, 1),sfg::Table::EXPAND , sfg::Table::EXPAND | sfg::Table::FILL);
    infoTable->Attach(infoLabels[2],sf::Rect<sf::Uint32>(2, 2, 1, 1),sfg::Table::EXPAND , sfg::Table::EXPAND | sfg::Table::FILL);
    infoTable->Attach(infoLabels[3],sf::Rect<sf::Uint32>(4, 1, 1, 1),sfg::Table::EXPAND , sfg::Table::EXPAND | sfg::Table::FILL);
    infoTable->Attach(infoLabels[4],sf::Rect<sf::Uint32>(4, 2, 1, 1),sfg::Table::EXPAND , sfg::Table::EXPAND | sfg::Table::FILL);
    infoTable->Attach(infoLabels[5],sf::Rect<sf::Uint32>(4, 0, 1, 1),sfg::Table::EXPAND , sfg::Table::EXPAND | sfg::Table::FILL);
    infoTable->Attach(infoLabels[6],sf::Rect<sf::Uint32>(0, 3, 7, 1),sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);



    //Buttons Window
    desktop.Add(buttonsWindow);
    buttonsWindow->Add(buttonsBox);
    buttonsWindow->SetAllocation(sf::FloatRect( XSCROLL + FRAME + XSCROLLBAR, app_window.getY()-YBUTTONS, app_window.getX()-XSCROLL - FRAME - XSCROLLBAR, YBUTTONS));

    buttonsBox->Pack(menuButton);
    buttonsBox->Pack(discardButton);
    buttonsBox->Pack(startButton);

    //Player window
    desktop.Add(playerWindow);
    playerWindow->Add(playerBox);
    playerWindow->SetAllocation(sf::FloatRect( app_window.getX()-XPLAYERS, app_window.getY()-YPLAYERS-YBUTTONS, XPLAYERS, YPLAYERS));
    playerBox->Pack(player1Button);
    playerBox->Pack(player2Button);

    player1Button->SetId("p1");
    player2Button->SetId("p2");
    label->SetId("l1");
    sfg::Context::Get().GetEngine().SetProperty("Button#p1", "BackgroundColor", sf::Color(96,26,67));
    sfg::Context::Get().GetEngine().SetProperty("Label#l1", "FontSize", 20);
    player1Button->SetState(sfg::Widget::State::INSENSITIVE);

    //Heroes window
    desktop.Add(scrollwin);
    scroll->SetScrollbarPolicy( sfg::ScrolledWindow::HORIZONTAL_NEVER| sfg::ScrolledWindow::VERTICAL_ALWAYS);
    tablebox->Pack(table);
    scroll->AddWithViewport(tablebox);
    scroll->SetRequisition( sf::Vector2f( XSCROLL - FRAME*2, app_window.getY() - FRAME*2) );
    scrollwinbox->Pack(scroll, false, true);
    scrollwin->Add(scrollwinbox);

    //ОТЛАДОЧНОЕ ЗАПОЛНЕНИЕ!!!
//    sf::Image heropic;
//    heropic.loadFromFile("src/heroPIC.jpg");
//    sfg::Image::Ptr images[N];
//    for(int i=0;i<N;i++){
//        images[i]=sfg::Image::Create(heropic);
//        table->Attach(images[i],sf::Rect<sf::Uint32>( i%2, floor(i/2+0.5), 1, 1),sfg::Table::FILL, sfg::Table::FILL);
//    }

    //Signals
    startButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &SelectionGUI::clickedButton, this, ButtonPressed::START ) );
    discardButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(
                std::bind( &SelectionGUI::clickedButton, this, ButtonPressed::DISCARD ) );
    menuButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &SelectionGUI::clickedButton, this, ButtonPressed::MENU ) );
    player1Button->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &SelectionGUI::clickedButton, this, ButtonPressed::PLAYER1 ) );
    player2Button->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &SelectionGUI::clickedButton, this, ButtonPressed::PLAYER2 ) );
}

void SelectionGUI::clickedButton(ButtonPressed Button)
{
    switch (Button)
    {
        case START: clickedStart(); break;
        case DISCARD: clickedDiscard(); break;
        case MENU: clickedMenu(); break;
        case PLAYER1:
    {
        sfg::Context::Get().GetEngine().SetProperty("Button#p1", "BackgroundColor", sf::Color(96,26,67));
        sfg::Context::Get().GetEngine().SetProperty("Button#p2", "BackgroundColor", sf::Color(85,87,82));
        player1Button->SetState(sfg::Widget::State::INSENSITIVE);
        player2Button->SetState(sfg::Button::State::NORMAL);
        clickedPlayer1();
        break;
    }
        case PLAYER2:
    {
        sfg::Context::Get().GetEngine().SetProperty("Button#p2", "BackgroundColor", sf::Color(96,26,67));
        sfg::Context::Get().GetEngine().SetProperty("Button#p1", "BackgroundColor", sf::Color(85,87,82));
        player2Button->SetState(sfg::Widget::State::INSENSITIVE);
        player1Button->SetState(sfg::Button::State::NORMAL);
        clickedPlayer2();
        break;
    }
    }
}

void SelectionGUI::show()
{
   infoWindow->Show(true);
   pointsWindow->Show(true);
   fieldWindow->Show(true);
   buttonsWindow->Show(true);
   playerWindow->Show(true);
   infoLabelWindow->Show(true);
   scrollwin->Show(true);
   timer = app_window.newTimer();
   connect(timer, SIGNAL(timeout()), this, SLOT(update()));
   timer->start(10);
}

void SelectionGUI::update()
{
    static bool flag = true;

    if (app_window.isOpen())
    {
        sf::Event event;
        while (app_window.pollEvent(event))
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

void SelectionGUI::hide()
{
    infoWindow->Show(false);
    pointsWindow->Show(false);
    fieldWindow->Show(false);
    buttonsWindow->Show(false);
    playerWindow->Show(false);
    infoLabelWindow->Show(false);
    scrollwin->Show(false);
    app_window.deleteTimer();
    app_window.clear(sf::Color::Black);
    app_window.display();
}

void SelectionGUI::setHeroVector(HeroVector *heroVector)
{
    heroesList = heroVector;
    int i = 0;
    for(auto it = heroesList->begin(), end = heroesList->end(); it != end; it++)
    {
        sfg::Image::Ptr finalImage = sfg::Image::Create((*it)->getResources().getImage());
        table->Attach(finalImage,sf::Rect<sf::Uint32>( i%2, floor(i/2+0.5), 1, 1),sfg::Table::FILL, sfg::Table::FILL);
        //Signal setting
        finalImage->GetSignal( sfg::Widget::OnLeftClick ).Connect(  std::bind( &SelectionGUI::heroChosen, this, i));
        i++;
    }
}

void SelectionGUI::heroChosen(int i)
{
    if(i != activeHeroNumber)
    {
        std::cout << i << "Hero chosen" << std::endl;
        clickedHero(heroesList->at(i));

    }
}

void SelectionGUI::setActiveHero(HeroTemplate *hero)
{
    //Heroes highlightin in left menu

    if(!heroesList->size() || hero == nullptr)
        std::cerr << "SelectionGUI::setActiveHero(HeroTemplate *hero): No heroes in heroesList";

    int i = 0, pos = -1;
    for(auto it = heroesList->begin(), end = heroesList->end(); it != end; it++, i++)
    {
        if(*it == hero)
        {
            pendingImage->SetImage((hero)->getResources().getImage2());
            table->Attach(pendingImage,sf::Rect<sf::Uint32>( i%2, floor(i/2+0.5), 1, 1),sfg::Table::FILL, sfg::Table::FILL);
            pos = i;
        }
        else if(i == activeHeroNumber)
        {
            pendingImage2->SetImage((*it)->getResources().getImage());
            table->Attach(pendingImage2,sf::Rect<sf::Uint32>( i%2, floor(i/2+0.5), 1, 1),sfg::Table::FILL, sfg::Table::FILL);
        }
    }
    activeHeroNumber = pos;
    std::cout << pos << "Set active hero" << std::endl;

    //Active hero info on the top
    if(activeHeroNumber == -1)
    {
        infoLabelWindow->Show(true);
        infoWindow->Show(false);
    }
    else
    {
        infoLabelWindow->Show(false);
        infoWindow->Show(true);
        infoLabels[0]->SetText("Pretty Long Hero Name");
        infoLabels[1]->SetText(std::to_string( hero->getStats().hp.max ) + " HP");
        infoLabels[2]->SetText(std::to_string( hero->getStats().damage.max ) + " DMG");
        infoLabels[3]->SetText(std::to_string( hero->getStats().initiative.val ) + " INIT");
        switch(hero->getStats().element)
        {
            case Element::neutral: infoLabels[4]->SetText("Neutral element");
            case Element::fire: infoLabels[4]->SetText("Fire element");
            case Element::water: infoLabels[4]->SetText("Water element");
            case Element::earth: infoLabels[4]->SetText("Earth element");
        }
        infoLabels[5]->SetText(std::to_string( hero->getStats().cost ) + " COINS");
        switch(hero->getStats().kind)
        {
            case Kind::melee: infoLabels[6]->SetText("Melee");
            case Kind::range: infoLabels[6]->SetText("Range");
        }
    }
}

void SelectionGUI::setHeroGroup(HeroGroup *)
{

}

void SelectionGUI::setCost()
{

}

void SelectionGUI::showCross(HeroPosition)
{

}
