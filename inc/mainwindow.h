#pragma once
#include <SFML/Window.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>
#include <QTimer>
#include <QObject>


class MainWindow: public sf::RenderWindow
{
private:
    QTimer* timer;
    const int XSIZE = 800;
    const int YSIZE = 600;
public:
    MainWindow();
    ~MainWindow();
    QTimer* getTimer();
    int getX();
    int getY();
};
