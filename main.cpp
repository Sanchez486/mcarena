#include <QCoreApplication>
#include <inc/battlegui.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BattleGUI battle;
    battle.show();
    return a.exec();
}
