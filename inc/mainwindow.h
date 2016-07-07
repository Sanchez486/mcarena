#pragma once
#include <SFML/Window.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
 #include <SFML/Graphics.hpp>


class MainWindow: public sf::RenderWindow
{
private:
    const int XSIZE = 800;
    const int YSIZE = 600;
public:
    MainWindow();
    int getX();
    int getY();
};
