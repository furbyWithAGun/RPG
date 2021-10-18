#pragma once
#include "GameMenu.h"
#include "ScrollBox.h"

class MainMenu : public GameMenu
{
public:
    //constructors
    MainMenu();
    MainMenu(GameScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);

private:
    //methods
    void buildElements();
};

