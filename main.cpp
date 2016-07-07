#include "inc/menugui.h"
#include <QCoreApplication>
#include "inc/game.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Game game;
    game.start();

    return a.exec();
}
