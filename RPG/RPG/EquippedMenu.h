#pragma once
#include "GameMenu.h"
#include "MenuButton.h"
#include "ScrollBox.h"
#include "MenuText.h"

class RpgOverWorldScene;

class EquippedMenu : public GameMenu
{
public:
    //constructors
    EquippedMenu();
    EquippedMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);
    void open() override;
    void draw() override;
    void rebuildElements() override;

    //methods
    bool handleInput(InputMessage* message);

private:
    //attributes
    RpgOverWorldScene* scene;

    //methods
    void buildElements();
    void init();
};

