#include "inc/menugui.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MenuGUI mg;
    mg.show();

    return a.exec();
}
