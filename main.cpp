#include "inc/selectiongui.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SelectionGUI sg;
    sg.show();

    return a.exec();
}
