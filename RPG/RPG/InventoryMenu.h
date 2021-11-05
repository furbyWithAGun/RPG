#pragma once
#include "GameMenu.h"
#include "MenuButton.h"
#include "ScrollBox.h"
#include "MenuText.h"

class RpgOverWorldScene;

class InventoryMenu : public GameMenu
{
public:
    //constructors
    InventoryMenu();
    InventoryMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);
    InventoryMenu(RpgOverWorldScene* gameScene, int newId);
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

