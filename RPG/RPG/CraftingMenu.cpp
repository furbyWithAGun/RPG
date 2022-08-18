#include "CraftingMenu.h"
#include "RpgOverWorldScene.h"
#include "Player.h"
#include "inputPrompt.h"

enum CRAFTING_MENU_IDS {

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
    xpos = scene->mainCanvasStartX + engine->screenWidth * 0.02;
    ypos = engine->screenHeight * 0.15;
    buildElements();
}

void CraftingMenu::open()
{
    GameMenu::open();
}

void CraftingMenu::draw()
{
    
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
    
}


void CraftingMenu::init()
{
    scene = nullptr;
}

