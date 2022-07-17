#pragma once
#include "GameMenu.h"
#include "MenuText.h"
#include "MenuButton.h"
#include "ScrollBox.h"
#include <filesystem>

class RpgOverWorldScene;

class LoadSaveGameMenu : public GameMenu
{
public:
    //attributes
    GameScene* scene;
    ScrollBox* savesDisplay;

    //constructors
    LoadSaveGameMenu();
    LoadSaveGameMenu(GameScene* gameScene, RpgOverWorldScene* overWorldScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);

    //methods
    //bool handleInput(InputMessage* message);
    void open() override;

private:
    //methods
    void buildElements(RpgOverWorldScene* overWorldScene);
    void init();
};

