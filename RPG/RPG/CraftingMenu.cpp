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
    xpos = scene->mainCanvasStartX + engine->screenWidth * 0.02;
    ypos = engine->screenHeight * 0.15;
    buildElements();
}

void CraftingMenu::open()
{
    scene->closeAllMenus();
    GameMenu::open();
    scene->openMenu(RPG_OVERWORLD_MENU);
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

    for (CraftingRecipe recipe : craftingRecipes)
    {
        recipeList->addElement(new MenuText(scene, recipe.getName(), 0, 0));
    }

    addElement(CRAFTING_MENU_CLOSE_BUTTON, (new MenuButton(scene, BUTTON_BACKGROUND, xpos + width * 0.65, height * 0.8))->setText("Cancel")->addOnClick([this] {
        this->close();
        }));

}


void CraftingMenu::init()
{
    scene = nullptr;
    currentCraftingStation = NO_CRAFTING_STATION;
    buildCraftingRecipes();
}

void CraftingMenu::buildCraftingRecipes()
{
    CraftingRecipe newRecipe;

    //recipe name
    newRecipe = CraftingRecipe("Club");
    //inputs
    newRecipe.addInput(ITEM_WOOD, 5);
    //outputs
    newRecipe.addOutput(ITEM_CLUB, 1);
    //crafting stations
    newRecipe.addCraftingStation(NO_CRAFTING_STATION);
    //skills requirements
    newRecipe.addSkillRequirement(BARELY_USABLE, SKILL_WOOD_WORKING, 1);
    newRecipe.addSkillRequirement(BARELY_USABLE, SKILL_WEAPON_CRAFTING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_WOOD_WORKING, 1);
    newRecipe.addSkillExperience(SKILL_WEAPON_CRAFTING, 1);
    //add to array
    craftingRecipes.push_back(newRecipe);

    //recipe name
    newRecipe = CraftingRecipe("This doesn't make sense");
    //inputs
    newRecipe.addInput(ITEM_WOOD, 5);
    newRecipe.addInput(ITEM_APPLE, 5);
    newRecipe.addInput(ITEM_SHORT_SWORD, 2);
    //outputs
    newRecipe.addOutput(ITEM_LONG_SWORD, 1);
    //crafting stations
    newRecipe.addCraftingStation(NO_CRAFTING_STATION);
    //skills requirements
    newRecipe.addSkillRequirement(BARELY_USABLE, SKILL_WOOD_WORKING, 1);
    newRecipe.addSkillRequirement(BARELY_USABLE, SKILL_METAL_WORKING, 1);
    newRecipe.addSkillRequirement(BARELY_USABLE, SKILL_WEAPON_CRAFTING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_WOOD_WORKING, 1);
    newRecipe.addSkillExperience(SKILL_WEAPON_CRAFTING, 1);
    //add to array
    craftingRecipes.push_back(newRecipe);
}

