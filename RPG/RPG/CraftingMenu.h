#pragma once
#include "GameMenu.h"
#include "MenuButton.h"
#include "ScrollBox.h"
#include "MenuText.h"
#include "CraftingRecipe.h"

class RpgOverWorldScene;
class RpgUnit;

class CraftingMenu : public GameMenu
{
public:
    //attributes

    //constructors
    CraftingMenu();
    CraftingMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);
    CraftingMenu(RpgOverWorldScene* gameScene, int newId);
    void open() override;
    void open(RpgUnit* newCraftingUnit, int newCraftingStation);
    void draw() override;
    void rebuildElements() override;

    //methods
    bool handleInput(InputMessage* message);

private:
    //attributes
    RpgOverWorldScene* scene;
    int currentCraftingStation;
    RpgUnit* craftingUnit;

    //methods
    void buildElements();
    void init();
};
