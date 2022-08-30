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
    scene->closeMenu(OTHER_UNIT_INVENTORY_MENU);
    GameMenu::open();
    scene->openMenu(INVENTORY_MENU);
}

void CraftingMenu::open(RpgUnit* newCraftingUnit, int newCraftingStation)
{
    open();
    craftingUnit = newCraftingUnit;
    currentCraftingStation = newCraftingStation;
    needToRebuildElements = true;
    ScrollBox* recipeList = (ScrollBox*)getElementbyId(RECIPE_SCROLL_BOX);
    recipeList->selectedElement = nullptr;
}

void CraftingMenu::draw()
{
    GameMenu::draw();
}

void CraftingMenu::rebuildElements()
{
    int amountInContainer;
    CraftingRecipe recipe = getSelectedRecipe();
    //if (recipe.getName() != "NULL")
    {
        for (int i = 0; i < MAX_NUM_CRAFT_INPUTS; i++) {
            if (recipe.getInputs().size() > i)
            {
                craftingInputsDisplay[i].icon->textureKey = getItemTextureId(recipe.getInputs()[i].item);
                craftingInputsDisplay[i].icon->active = true;
                craftingInputsDisplay[i].txtQty->active = true;
                int inQty = recipe.getInputs()[i].qty;
                if (inQty > 1)
                {
                    craftingInputsDisplay[i].txtQty->setText(" X " + std::to_string(inQty));
                    amountInContainer = qtyInContainer(recipe.getInputs()[i].item, craftingUnit->inventory);
                    if (amountInContainer >= inQty)
                    {
                        craftingInputsDisplay[i].txtQty->setTextColour(COLOR_GREEN);
                    }
                    else {
                        craftingInputsDisplay[i].txtQty->setTextColour(COLOR_RED);
                    }
                }
            }
            else {
                craftingInputsDisplay[i].icon->active = false;
                craftingInputsDisplay[i].txtQty->active = false;
            }

            if (recipe.getOutputs().size() > i)
            {
                craftingOutputsDisplay[i].icon->textureKey = getItemTextureId(recipe.getOutputs()[i].item);
                craftingOutputsDisplay[i].icon->active = true;
                craftingOutputsDisplay[i].txtQty->active = true;
                int outQty = recipe.getOutputs()[i].qty;
                if (outQty > 1)
                {
                    craftingOutputsDisplay[i].txtQty->setText(" X " + std::to_string(outQty));
                    if (amountInContainer >= outQty)
                    {
                        craftingOutputsDisplay[i].txtQty->setTextColour(COLOR_GREEN);
                    }
                    else {
                        craftingOutputsDisplay[i].txtQty->setTextColour(COLOR_RED);
                    }
                }
            }
            else {
                craftingOutputsDisplay[i].icon->active = false;
                craftingOutputsDisplay[i].txtQty->active = false;
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

    //MenuText* txtReqMats = new MenuText(scene, "Required Materials", { 255, 255, 255 }, xpos + scene->engine->screenWidth * 0.01, ypos + scene->engine->screenWidth * 0.01);
    //txtReqMats->setAutoUpdateDimensions(false);
    //txtReqMats->setText("Required Materials");
    //txtReqMats->setdimensions(engine->screenWidth * 0.09, engine->screenHeight * 0.04);
    //addElement(txtReqMats);

    UiElement* arrowImage = new UiElement(scene, TEXTURE_LARGE_ARROW_RIGHT, xpos + engine->screenWidth * 0.1, ypos + engine->screenHeight * 0.06);
    addElement(arrowImage);

    for (int i = 0; i < MAX_NUM_CRAFT_INPUTS; i++)
    {
        UiElement* newInput = new UiElement(scene, BLANK_PORTAL, i + INPUT_DISPLAY_X, i * REAGENT_ICON_ROW_OFFSET + INPUT_DISPLAY_Y);
        UiElement* newOutput = new UiElement(scene, BLANK_PORTAL, i + OUTPUT_DISPLAY_X, i * REAGENT_ICON_ROW_OFFSET + OUTPUT_DISPLAY_Y);
        MenuText* txtInputQty = new MenuText(scene, "", { 255, 255, 255 }, i + INPUT_DISPLAY_X + engine->screenWidth * 0.025, i * REAGENT_ICON_ROW_OFFSET + INPUT_DISPLAY_Y + engine->screenWidth * 0.005);
        MenuText* txtOutputQty = new MenuText(scene, "", { 255, 255, 255 }, i + OUTPUT_DISPLAY_X + engine->screenWidth * 0.025, i * REAGENT_ICON_ROW_OFFSET + OUTPUT_DISPLAY_Y + engine->screenWidth * 0.005);
        craftingInputsDisplay.push_back(craftingItemDisplay{ newInput, i + INPUT_DISPLAY_X, i * REAGENT_ICON_ROW_OFFSET + INPUT_DISPLAY_Y, txtInputQty });
        craftingOutputsDisplay.push_back(craftingItemDisplay{ newOutput, i + OUTPUT_DISPLAY_X, i * REAGENT_ICON_ROW_OFFSET + OUTPUT_DISPLAY_Y, txtOutputQty });
        craftingInputsDisplay[i].icon->active = false;
        craftingOutputsDisplay[i].icon->active = false;
        addElement(craftingInputsDisplay[i].icon);
        addElement(craftingOutputsDisplay[i].icon);
        addElement(craftingInputsDisplay[i].txtQty);
        addElement(craftingOutputsDisplay[i].txtQty);
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
    width = engine->screenWidth * 0.3;
    height = engine->screenHeight * 0.7;
    xpos = scene->mainCanvasStartX + engine->screenWidth * 0.3;
    ypos = engine->screenHeight * 0.15;

    MAX_NUM_CRAFT_INPUTS = 5;
    INPUT_DISPLAY_X = xpos + engine->screenWidth * 0.04;
    INPUT_DISPLAY_Y = ypos + engine->screenHeight * 0.08;
    OUTPUT_DISPLAY_X = xpos + engine->screenWidth * 0.2;
    OUTPUT_DISPLAY_Y = ypos + engine->screenHeight * 0.08;
    REAGENT_ICON_ROW_OFFSET = engine->screenHeight * 0.04;
}

CraftingRecipe CraftingMenu::getSelectedRecipe()
{
    ScrollBox* recipeList = (ScrollBox*)getElementbyId(RECIPE_SCROLL_BOX);

    if (recipeList->selectedElement != nullptr)
    {
        return scene->getCraftingRecipe(recipeList->getSelectedElementValue());
    }
    return CraftingRecipe("NULL");
}

