#include "CraftingMenu.h"
#include "RpgOverWorldScene.h"
#include "Player.h"
#include "inputPrompt.h"

enum CRAFTING_MENU_IDS {
    RECIPE_SCROLL_BOX,
    RECIPE_CRAFT_BUTTON,
    CRAFTING_MENU_CLOSE_BUTTON
};

CraftingMenu::CraftingMenu() : GameMenu()
{
    init();
}

CraftingMenu::CraftingMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos)
{
    init();
    scene = gameScene;
    buildElements();
}

CraftingMenu::CraftingMenu(RpgOverWorldScene* gameScene, int newId) : GameMenu(gameScene, newId)
{
    init();
    scene = gameScene;
    width = engine->screenWidth * 0.25;
    height = engine->screenHeight * 0.7;
    xpos = scene->mainCanvasStartX + engine->screenWidth * 0.3;
    ypos = engine->screenHeight * 0.15;
    buildElements();
}

void CraftingMenu::open()
{
    //scene->closeAllMenus();
    scene->closeMenu(ITEM_SHOP_MENU);
    GameMenu::open();
    scene->openMenu(INVENTORY_MENU);
}

void CraftingMenu::open(RpgUnit* newCraftingUnit, int newCraftingStation)
{
    open();
    craftingUnit = newCraftingUnit;
    currentCraftingStation = newCraftingStation;
}

void CraftingMenu::draw()
{
    GameMenu::draw();
}

void CraftingMenu::rebuildElements()
{
    
}

bool CraftingMenu::handleInput(InputMessage* message)
{
    return GameMenu::handleInput(message);
}

void CraftingMenu::buildElements()
{
    ScrollBox* recipeList;
    recipeList = new ScrollBox(scene, COLOR_GREY, xpos + width * 0.1, ypos + height * 0.45, width * 0.55, height * 0.4);
    recipeList->numElementsToDisplay = 5;
    addElement(RECIPE_SCROLL_BOX, recipeList);

    //for (CraftingRecipe recipe : craftingRecipes)
    for(int i = 0; i < scene->getCraftingRecipes().size(); i++)
    {
        recipeList->addElement(new MenuText(scene, scene->getCraftingRecipe(i).getName(), 0, 0), i);
    }

    addElement(CRAFTING_MENU_CLOSE_BUTTON, (new MenuButton(scene, BUTTON_BACKGROUND, xpos + width * 0.65, height * 0.8))->setText("Cancel")->addOnClick([this] {
        this->close();
        }));
    
    addElement(RECIPE_CRAFT_BUTTON, (new MenuButton(scene, BUTTON_BACKGROUND, xpos + width * 0.65, height * 0.7))->setText("Craft")->addOnClick([this, recipeList] {
        scene->addCommand(InputMessage(OVERWORLD_PLAYER_CRAFT, 0, 0, recipeList->getSelectedElementValue(), {currentCraftingStation}));
        }));

}


void CraftingMenu::init()
{
    scene = nullptr;
    currentCraftingStation = NO_CRAFTING_STATION;
}

