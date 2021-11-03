#include "ItemSellMenu.h"
#include "RpgOverWorldScene.h"
#include "ItemShop.h"
#include "Player.h"
#include "InputPrompt.h"

enum ITEM_SELL_MENU_IDS {
    ITEMS_SCROLL_BOX,
    ITEM_SELL_CLOSE_BUTTON,
    ITEM_SELL_BUTTON,
};

ItemSellMenu::ItemSellMenu() : GameMenu()
{
    init();
}

ItemSellMenu::ItemSellMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos)
{
    init();
    scene = gameScene;
    buildElements();
}

void ItemSellMenu::open()
{
    GameMenu::open();
    scene->closeMenu(INVENTORY_MENU);
}

void ItemSellMenu::draw()
{
    GameMenu::draw();
}

void ItemSellMenu::rebuildElements()
{
    ScrollBox* items = (ScrollBox*)getElementbyId(ITEMS_SCROLL_BOX);
    items->clear();

    for (int i = 0; i < scene->player->inventory.size(); i++)
    {
        if (scene->player->inventory[i]->stackSize > 1)
        {
            items->addElement(new MenuText(scene, scene->player->inventory[i]->name + " X " + std::to_string(scene->player->inventory[i]->stackSize), 0, 0), i);
        }
        else {
            items->addElement(new MenuText(scene, scene->player->inventory[i]->name, 0, 0), i);
        }
    }
    items->selectedElement = nullptr;
}

bool ItemSellMenu::handleInput(InputMessage* message)
{
    return GameMenu::handleInput(message);
}

void ItemSellMenu::setItemShop(ItemShop* newItemShop)
{
    itemShop = newItemShop;
}

void ItemSellMenu::buildElements()
{
    ScrollBox* items;
    items = new ScrollBox(ITEMS_SCROLL_BOX, scene, COLOR_GREY, xpos + width * 0.1, ypos + height * 0.1, width * 0.55, height * 0.7);
    items->numElementsToDisplay = 5;
    addElement(ITEMS_SCROLL_BOX, items);

    MenuButton* closeBtn = new MenuButton(ITEM_SELL_CLOSE_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.1, ypos + height * 0.85);
    closeBtn->setText("Close")->addOnClick([this]() {
        this->close();
        });
    addElement(ITEM_SELL_CLOSE_BUTTON, closeBtn);

    MenuButton* equipBtn = new MenuButton(ITEM_SELL_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.15);
    equipBtn->setText("Sell")->addOnClick([this, items]() {
        if (items->getSelectedElementValue() != -1)
        {
            Item* selectedItem = scene->player->inventory[items->getSelectedElementValue()];
            if (selectedItem->stackSize > 1)
            {
                InputPrompt* qtyPrompt = new InputPrompt(scene, "Sell How Many?", COLOR_BLACK, xpos + width, ypos, scene->engine->screenWidth * 0.2, scene->engine->screenHeight * 0.2);
                qtyPrompt->setInputText(std::to_string(selectedItem->stackSize));
                qtyPrompt->addCallBack([selectedItem, this, items](std::string enteredText) {
                    if (true)
                    {
                        int numToSell;
                        if (stringIsAnInt(enteredText))
                        {
                            numToSell = std::stoi(enteredText);
                        }
                        else {
                            numToSell = 0;
                        }
                        if (numToSell >= selectedItem->stackSize)
                        {
                            int goldToAdd = (selectedItem->value * selectedItem->stackSize) / 2;
                            if (goldToAdd < 1)
                            {
                                goldToAdd = 1;
                            }
                            scene->player->gold += goldToAdd;
                            scene->player->deleteItemFromInventory(items->getSelectedElementValue());
                            scene->menus[EQUIPPED_MENU]->rebuildElements();
                            rebuildElements();
                        }
                        else if (numToSell > 0){
                            int goldToAdd = (selectedItem->value * numToSell) / 2;
                            if (goldToAdd < 1)
                            {
                                goldToAdd = 1;
                            }
                            scene->player->gold += goldToAdd;
                            selectedItem->stackSize -= numToSell;
                            scene->menus[EQUIPPED_MENU]->rebuildElements();
                            rebuildElements();
                        }
                    }
                    });
                scene->addPrompt(qtyPrompt);
            }
            else {
                int goldToAdd = (selectedItem->value * selectedItem->stackSize) / 2;
                if (goldToAdd < 1)
                {
                    goldToAdd = 1;
                }
                scene->player->gold += goldToAdd;
                scene->player->deleteItemFromInventory(items->getSelectedElementValue());
                scene->menus[EQUIPPED_MENU]->rebuildElements();
                rebuildElements();
            }
        }
        });
    addElement(ITEM_SELL_BUTTON, equipBtn);
}

void ItemSellMenu::init()
{
    scene = nullptr;
}

