#pragma once
#include "GameMenu.h"
#include "ScrollBox.h"

class MainMenu : public GameMenu
{
public:
    //constructors
    MainMenu();
    MainMenu(GameScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);

    //methods
    void open() override;

private:
    //methods
    void buildElements();
    void buildPrompt();
};

