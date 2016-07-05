#pragma once
#include <QObject>

class MenuGUI : public QObject
{
Q_OBJECT
private:

signals:
    void clickedPlay();
    void clickedPlayOnline();
    void clickedPlayCPU();
    void clickedExit();
    void clickedSound();  // Button sounds on/off
    void clickedMusic();  // Button music on/off

public slots:
    void show();  // Show this window
    void hide();  // Hide this window
    void setSounds(bool);  // Change sounds icon on/off
    void setMusic(bool);  // Change music icon on/off
};
