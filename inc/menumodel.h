#pragma once
#include <QObject>

class MenuModel : public QObject
{
Q_OBJECT
private:

signals:
    void show();  // Show GUI window
    void hide();  // Hide GUI window
    void setSounds(bool);  // Change sounds icon on/off
    void setMusic(bool);  // Change music icon on/off

public slots:
    void clickedPlay();
    void clickedPlayOnline();
    void clickedPlayCPU();
    void clickedExit();
    void clickedSound();  // Button sounds on/off
    void clickedMusic();  // Button music on/off
};
