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
    init(gameScene);
    buildElements();
}

CraftingMenu::CraftingMenu(RpgOverWorldScene* gameScene, int newId) : GameMenu(gameScene, newId)
{
    init(gameScene);
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
    ScrollBox* recipeList = (ScrollBox*)getElementbyId(RECIPE_SCROLL_BOX);
    if (recipeList->selectedElement != nullptr)
    {
        for (int i = 0; i < MAX_NUM_CRAFT_INPUTS; i++) {
            if (scene->getCraftingRecipe(recipeList->getSelectedElementValue()).getInputs().size() > i)
            {
                craftingInputsDisplay[i].icon->textureKey = getItemTextureId(scene->getCraftingRecipe(recipeList->getSelectedElementValue()).getInputs()[i].item);
                craftingInputsDisplay[i].icon->active = true;
            }
            else {
                craftingInputsDisplay[i].icon->active = false;
            }
            
            if (scene->getCraftingRecipe(recipeList->getSelectedElementValue()).getOutputs().size() > i)
            {
                craftingOutputsDisplay[i].icon->textureKey = getItemTextureId(scene->getCraftingRecipe(recipeList->getSelectedElementValue()).getOutputs()[i].item);
                craftingOutputsDisplay[i].icon->active = true;
            }
            else {
                craftingOutputsDisplay[i].icon->active = false;
            }
        }
    }
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
        MenuText* newtext = new MenuText(scene, scene->getCraftingRecipe(i).getName(), 0, 0);
        newtext->addOnClick([this]() {
            rebuildMenuElements();
            });
        recipeList->addElement(newtext, i);
    }

    addElement(CRAFTING_MENU_CLOSE_BUTTON, (new MenuButton(scene, BUTTON_BACKGROUND, xpos + width * 0.65, height * 0.8))->setText("Cancel")->addOnClick([this] {
        this->close();
        }));
    
    addElement(RECIPE_CRAFT_BUTTON, (new MenuButton(scene, BUTTON_BACKGROUND, xpos + width * 0.65, height * 0.7))->setText("Craft")->addOnClick([this, recipeList] {
        scene->addCommand(InputMessage(OVERWORLD_PLAYER_CRAFT, 0, 0, recipeList->getSelectedElementValue(), {currentCraftingStation}));
        }));

    addElement(new MenuText(scene, "Required Materials", { 255, 255, 255 }, xpos + scene->engine->screenWidth * 0.01, ypos + scene->engine->screenWidth * 0.01));

    for (int i = 0; i < MAX_NUM_CRAFT_INPUTS; i++)
    {
        UiElement* newInput = new UiElement(scene, BLANK_PORTAL, i + INPUT_DISPLAY_X, i * REAGENT_ICON_ROW_OFFSET + INPUT_DISPLAY_Y);
        UiElement* newOutput = new UiElement(scene, BLANK_PORTAL, i + INPUT_DISPLAY_X, i * REAGENT_ICON_ROW_OFFSET + INPUT_DISPLAY_Y);
        craftingInputsDisplay.push_back(craftingItemDisplay{ newInput, i + INPUT_DISPLAY_X, i * REAGENT_ICON_ROW_OFFSET + INPUT_DISPLAY_Y });
        craftingOutputsDisplay.push_back(craftingItemDisplay{ newOutput, i + INPUT_DISPLAY_X, i * REAGENT_ICON_ROW_OFFSET + INPUT_DISPLAY_Y });
        craftingInputsDisplay[i].icon->active = false;
        craftingOutputsDisplay[i].icon->active = false;
        addElement(craftingInputsDisplay[i].icon);
        addElement(craftingInputsDisplay[i].icon);
    }

}


void CraftingMenu::init()
{
    scene = nullptr;
    currentCraftingStation = NO_CRAFTING_STATION;
}

void CraftingMenu::init(RpgOverWorldScene* gameScene)
{
    init();
    scene = gameScene;
    width = engine->screenWidth * 0.25;
    height = engine->screenHeight * 0.7;
    xpos = scene->mainCanvasStartX + engine->screenWidth * 0.3;
    ypos = engine->screenHeight * 0.15;

    MAX_NUM_CRAFT_INPUTS = 5;
    INPUT_DISPLAY_X = xpos + engine->screenWidth * 0.01;
    INPUT_DISPLAY_Y = ypos + engine->screenHeight * 0.1;
    REAGENT_ICON_ROW_OFFSET = engine->screenHeight * 0.04;
}

