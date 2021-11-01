#include "InventoryMenu.h"
#include "RpgOverWorldScene.h"
#include "Player.h"
#include "inputPrompt.h"

enum INVENTORY_MENU_IDS {
    ITEMS_SCROLL_BOX,
    INVENTORY_CLOSE_BUTTON,
    INVENTORY_DROP_BUTTON,
    INVENTORY_EQUIP_BUTTON,
    INVENTORY_EAT_BUTTON,
    OPEN_EQUIPPED_MENU_BUTTON
};

InventoryMenu::InventoryMenu() : GameMenu()
{
    init();
}

InventoryMenu::InventoryMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos)
{
    init();
    scene = gameScene;
    buildElements();
}

void InventoryMenu::open()
{
    GameMenu::open();
    ((ScrollBox*)getElementbyId(ITEMS_SCROLL_BOX))->displayIndex = 0;
}

void InventoryMenu::draw()
{
    GameMenu::draw();
}

void InventoryMenu::update()
{
    ScrollBox* items = (ScrollBox*)getElementbyId(ITEMS_SCROLL_BOX);
    items->clear();
    for (int i=0 ; i < scene->player->inventory.size(); i++)
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
    if (items->subElements.size() <= items->numElementsToDisplay)
    {
        items->displayIndex = 0;
    }
}

bool InventoryMenu::handleInput(InputMessage* message)
{
    return GameMenu::handleInput(message);
}

void InventoryMenu::buildElements()
{
    ScrollBox* items;
    items = new ScrollBox(ITEMS_SCROLL_BOX, scene, COLOR_GREY, xpos + width * 0.1, ypos + height * 0.1, width * 0.55, height * 0.7);
    items->numElementsToDisplay = 5;
    addElement(ITEMS_SCROLL_BOX, items);

    MenuButton* closeBtn = new MenuButton(INVENTORY_CLOSE_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.1, ypos + height * 0.85);
    closeBtn->setText("Close")->addOnClick([this]() {
        this->close();
        });
    addElement(INVENTORY_CLOSE_BUTTON, closeBtn);

    MenuButton* dropBtn = new MenuButton(INVENTORY_DROP_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.45);
    dropBtn->setText("Drop")->addOnClick([this, items]() {
        int selection = items->getSelectedElementValue();
        if (selection != -1)
        {
            if (scene->player->inventory[selection]->stackSize > 1)
            {
                InputPrompt* qtyPrompt = new InputPrompt(scene, "Drop How Many?", COLOR_BLACK, xpos + width, ypos, scene->engine->screenWidth * 0.2, scene->engine->screenHeight * 0.2);
                qtyPrompt->setInputText(std::to_string(scene->player->inventory[selection]->stackSize));
                qtyPrompt->addCallBack([selection, this](std::string enteredText) {
                    if (true)
                    {
                        int numToDrop;
                        if (stringIsAnInt(enteredText))
                        {
                            numToDrop = std::stoi(enteredText);
                        }
                        else {
                            numToDrop = 0;
                        }
                        
                        if (numToDrop >= scene->player->inventory[selection]->stackSize)
                        {
                            scene->player->dropItemFromInventory(selection);
                            update();
                        }
                        else if (numToDrop > 0){
                            Item* itemToDrop = createNewItem(scene->player->inventory[selection]->textureKey);
                            itemToDrop->stackSize = numToDrop;
                            scene->addItemsToMap(scene->player->zone, scene->player->tileLocation->x, scene->player->tileLocation->y, {itemToDrop});
                            scene->player->inventory[selection]->stackSize -= numToDrop;
                            update();
                        }
                    }
                    });
                scene->addPrompt(qtyPrompt);
            }
            else {
                scene->player->dropItemFromInventory(selection);
                this->update();
            }
        }
        });
    addElement(INVENTORY_DROP_BUTTON, dropBtn);

    MenuButton* equipBtn = new MenuButton(INVENTORY_EQUIP_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.15);
    equipBtn->setText("Equip")->addOnClick([this, items]() {
        if (items->getSelectedElementValue() != -1)
        {
            Item* selectedItem = scene->player->inventory[items->getSelectedElementValue()];
            if (selectedItem->equipable)
            {   
                Equipment* itemToEquip = (Equipment*)selectedItem;
                if (scene->player->equippedItems[itemToEquip->slot] != nullptr)
                {
                    scene->player->inventory.push_back(scene->player->equippedItems[itemToEquip->slot]);
                }
                scene->player->equippedItems[itemToEquip->slot] = itemToEquip;
                scene->player->inventory.erase(scene->player->inventory.begin() + items->getSelectedElementValue());
                scene->menus[EQUIPPED_MENU]->update();
                update();
            }
        }
        });
    addElement(INVENTORY_EQUIP_BUTTON, equipBtn);

    MenuButton* eatBtn = new MenuButton(INVENTORY_EAT_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.55);
    eatBtn->setText("Eat")->addOnClick([this, items]() {
        if (items->getSelectedElementValue() != -1)
        {
            Item* selectedItem = scene->player->inventory[items->getSelectedElementValue()];
            if (selectedItem->type == FOOD)
            {
                Food* itemToEat = (Food*)selectedItem;
                scene->player->eatFood(itemToEat);
                if (itemToEat->stackSize <= 0)
                {
                    scene->player->inventory.erase(scene->player->inventory.begin() + items->getSelectedElementValue());
                }
                scene->menus[EQUIPPED_MENU]->update();
                update();
            }
        }
        });
    addElement(INVENTORY_EAT_BUTTON, eatBtn);

    MenuButton* equipMenuBtn = new MenuButton(OPEN_EQUIPPED_MENU_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.25);
    equipMenuBtn->setText("Equipment")->addOnClick([this]() {
        scene->openMenu(EQUIPPED_MENU);
        });
    addElement(OPEN_EQUIPPED_MENU_BUTTON, equipMenuBtn);
}

void InventoryMenu::init()
{
    scene = nullptr;
}
