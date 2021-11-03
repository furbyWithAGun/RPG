#pragma once
#include "GameMenu.h"
#include "MenuButton.h"
#include "HoverToolTip.h"

class RpgOverWorldScene;

class OverWorldSceneMenu : public GameMenu
{
public:
    //constructors
    OverWorldSceneMenu();
    OverWorldSceneMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);
    void close() override;

    //methods
    bool handleInput(InputMessage* message);

private:
    //attributes
    RpgOverWorldScene* scene;

    //methods
    void buildElements();
    void init();
};

