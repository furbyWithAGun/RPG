#pragma once
#include "GameMenu.h"
#include "TextBox.h"
#include "MenuText.h"
#include "RpgGameConstants.h"
#include "MenuButton.h"

class RpgOverWorldScene;

class SaveGameMenu : public GameMenu
{
public:
    //attributes
    RpgOverWorldScene* scene;

    //constructors
    SaveGameMenu();
    SaveGameMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);

    //methods
    //bool handleInput(InputMessage* message);
    void open() override;

private:
    //methods
    void buildElements();
};

