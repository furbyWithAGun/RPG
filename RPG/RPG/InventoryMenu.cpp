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
    ITEM_SELL_BUTTON,
    IVENTORY_TRANSFER_BUTTON
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

InventoryMenu::InventoryMenu(RpgOverWorldScene* gameScene, int newId) : GameMenu(gameScene, newId)
{
    init();
    scene = gameScene;
    width = engine->screenWidth * 0.25;
    height = engine->screenHeight * 0.7;
    xpos = scene->mainCanvasStartX + engine->screenWidth * 0.02;
    ypos = engine->screenHeight * 0.15;
    buildElements();
}

void InventoryMenu::open()
{
    GameMenu::open();
    rebuildElements();
    ((ScrollBox*)getElementbyId(ITEMS_SCROLL_BOX))->displayIndex = 0;
}

void InventoryMenu::draw()
{
    ScrollBox* items = (ScrollBox*)getElementbyId(ITEMS_SCROLL_BOX);
    int itemIndex = items->getSelectedElementValue();
    Item* item;

    MenuButton* btnEat = (MenuButton*)getElementbyId(INVENTORY_EAT_BUTTON);
    btnEat->active = false;

    MenuButton* btnEquip = (MenuButton*)getElementbyId(INVENTORY_EQUIP_BUTTON);
    btnEquip->active = false;

    MenuButton* btnDrop = (MenuButton*)getElementbyId(INVENTORY_DROP_BUTTON);
    btnDrop->active = false;

    MenuButton* btnSell = (MenuButton*)getElementbyId(ITEM_SELL_BUTTON);
    btnSell->active = false;

    MenuButton* btnXfer = (MenuButton*)getElementbyId(IVENTORY_TRANSFER_BUTTON);
    btnXfer->active = false;

    if (itemIndex != -1)
    {
        btnDrop->active = true;;
        item = scene->player->inventory[items->getSelectedElementValue()];
        if (item->generalType == FOOD)
        {
            btnEat->active = true;
        }
        else if (item->equipable) {
            btnEquip->active = true;
        }
        if (scene->menus[ITEM_SHOP_MENU]->isActive)
        {
            btnSell->active = true;
        }
        if (scene->menus[TRANSFER_ITEMS_MENU]->isActive)
        {
            btnXfer->active = true;
        }
    }

    
    GameMenu::draw();
    for (auto displaySlot : displaySlots)
    {
        if (displaySlot.second.icon.textureKey != -1)
        {
            displaySlot.second.icon.draw(xpos + displaySlot.second.x, ypos + displaySlot.second.y);
        }
    }
    for (auto toolTip : toolTips)
    {
        if (toolTip->active) {
            toolTip->draw();
        }
    }
}

void InventoryMenu::rebuildElements()
{
    ScrollBox* items = (ScrollBox*)getElementbyId(ITEMS_SCROLL_BOX);
    items->clear();
    toolTips.clear();
    for (int i=0 ; i < scene->player->inventory.size(); i++)
    {
        MenuText* txtInvItem = new MenuText(scene, scene->player->inventory[i]->name, 0, 0);
        HoverToolTip* toolTip = createItemToolTip(scene->player->inventory[i], scene);
        registerToolTip(txtInvItem, toolTip);

        if (scene->player->inventory[i]->generalType == FOOD) {
            txtInvItem->addBtnOneCallback([this, i]() {
                Item* selectedItem = scene->player->inventory[i];
                if (selectedItem->generalType == FOOD)
                {
                    Food* itemToEat = (Food*)selectedItem;
                    scene->player->eatFood(itemToEat);
                    if (itemToEat->stackSize <= 0)
                    {
                        scene->player->inventory.erase(scene->player->inventory.begin() + i);
                    }
                    rebuildElements();
                }
                });
        }

        if (scene->player->inventory[i]->stackSize > 1)
        {
            items->addElement(txtInvItem->setText(scene->player->inventory[i]->name + " X " + std::to_string(scene->player->inventory[i]->stackSize)), i);
        }
        else {
            items->addElement(txtInvItem->setText(scene->player->inventory[i]->name), i);
        }
    }
    items->selectedElement = nullptr;
    if (items->subElements.size() <= items->numElementsToDisplay)
    {
        items->displayIndex = 0;
    }

    for (int i = BARE_HANDS + 1; i != NUM_EQUIPMENT_SLOTS; i++)
    {
        if (scene->player->equippedItems[i] != nullptr)
        {
            displaySlots[i].icon = UiElement(scene, scene->player->equippedItems[i]->textureKey, xpos + displaySlots[i].x, ypos + displaySlots[i].y);
            displaySlots[i].icon.addOnClick([this, i]() {
                scene->player->unEquipItem(i);
                });
            HoverToolTip* toolTip = createItemToolTip(scene->player->equippedItems[i], scene);
            registerToolTip(&displaySlots[i].icon, toolTip);
        }
        else {
            displaySlots[i].icon = UiElement(scene, -1);
        }
    }
}

bool InventoryMenu::handleInput(InputMessage* message)
{
    for (auto displaySlot : displaySlots)
    {
        if (displaySlot.second.icon.textureKey != -1)
        {
            if (displaySlot.second.icon.handleInput(message)) {
                return true;
            }
        }
    }
    return GameMenu::handleInput(message);
}

void InventoryMenu::buildElements()
{
    UiElement* silh = new UiElement(scene, TEXTURE_EQUIPPED_MENU_SILHOUETTE, xpos + width * 0.1, ypos + height * 0.05, width * 0.55, height * 0.4);
    silh->backgroundColour = COLOR_LIGHT_GREY;
    addElement(silh);

    ScrollBox* items;
    items = new ScrollBox(ITEMS_SCROLL_BOX, scene, COLOR_GREY, xpos + width * 0.1, ypos + height * 0.4, width * 0.55, height * 0.4);
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
                    }
                    else if (numToDrop > 0){
                        Item* itemToDrop = createNewItem(scene->player->inventory[selection]->textureKey); // relies on fact each item type atm has a unique textureId
                        itemToDrop->stackSize = numToDrop;
                        scene->addItemsToMap(scene->player->zone, scene->player->tileLocation->x, scene->player->tileLocation->y, {itemToDrop});
                        scene->player->inventory[selection]->stackSize -= numToDrop;
                        rebuildElements();
                    }
                    });
                scene->addPrompt(qtyPrompt);
            }
            else {
                scene->player->dropItemFromInventory(selection);
            }
        }
        });

    addElement(INVENTORY_DROP_BUTTON, dropBtn);

    MenuButton* equipBtn = new MenuButton(INVENTORY_EQUIP_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.35);
    equipBtn->setText("Equip")->addOnClick([this, items]() {
        if (items->getSelectedElementValue() != -1)
        {
            Item* selectedItem = scene->player->inventory[items->getSelectedElementValue()];
            if (selectedItem->equipable)
            {   
                Equipment* itemToEquip = (Equipment*)selectedItem;
                scene->player->equipItem(itemToEquip);
                /*if (scene->player->equippedItems[itemToEquip->slot] != nullptr)
                {
                    scene->player->inventory.push_back(scene->player->equippedItems[itemToEquip->slot]);
                }
                scene->player->equippedItems[itemToEquip->slot] = itemToEquip;
                scene->player->inventory.erase(scene->player->inventory.begin() + items->getSelectedElementValue());
                scene->menus[EQUIPPED_MENU]->rebuildElements();
                rebuildElements();*/
            }
        }
        });
    addElement(INVENTORY_EQUIP_BUTTON, equipBtn);

    MenuButton* eatBtn = new MenuButton(INVENTORY_EAT_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.55);
    eatBtn->setText("Eat")->addOnClick([this, items]() {
        if (items->getSelectedElementValue() != -1)
        {
            Item* selectedItem = scene->player->inventory[items->getSelectedElementValue()];
            if (selectedItem->generalType == FOOD)
            {
                Food* itemToEat = (Food*)selectedItem;
                scene->player->eatFood(itemToEat);
                if (itemToEat->stackSize <= 0)
                {
                    scene->player->inventory.erase(scene->player->inventory.begin() + items->getSelectedElementValue());
                }
                rebuildElements();
            }
        }
        });
    addElement(INVENTORY_EAT_BUTTON, eatBtn);

    MenuButton* sellBtn = new MenuButton(ITEM_SELL_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.15);
    sellBtn->setText("Sell")->addOnClick([this, items]() {
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
                        else if (numToSell > 0) {
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
    addElement(ITEM_SELL_BUTTON, sellBtn);

    MenuButton* xferBtn = new MenuButton(IVENTORY_TRANSFER_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.85);
    xferBtn->setText("Transfer")->addOnClick([this, items]() {
        if (!scene->menus[TRANSFER_ITEMS_MENU]->isActive)
        {
            return;
        }
        int selection = items->getSelectedElementValue();
        if (selection != -1)
        {
            if (scene->player->inventory[selection]->stackSize > 1)
            {
                InputPrompt* qtyPrompt = new InputPrompt(scene, "Transfer How Many?", COLOR_BLACK, xpos + width, ypos, scene->engine->screenWidth * 0.2, scene->engine->screenHeight * 0.2);
                qtyPrompt->setInputText(std::to_string(scene->player->inventory[selection]->stackSize));
                qtyPrompt->addCallBack([selection, this](std::string enteredText) {
                    int numToXfer;
                    if (stringIsAnInt(enteredText))
                    {
                        numToXfer = std::stoi(enteredText);
                    }
                    else {
                        numToXfer = 0;
                    }

                    if (numToXfer >= scene->player->inventory[selection]->stackSize)
                    {
                        ((TransferItemsMenu*)scene->menus[TRANSFER_ITEMS_MENU])->transferItemToContainer(scene->player->inventory[selection]);
                        scene->player->removeItemFromInventory(selection);
                        scene->menus[TRANSFER_ITEMS_MENU]->rebuildElements();
                    }
                    else if (numToXfer > 0) {
                        Item* itemToXfer = createNewItem(scene->player->inventory[selection]->textureKey); // relies on fact each item type atm has a unique textureId
                        itemToXfer->stackSize = numToXfer;
                        ((TransferItemsMenu*)scene->menus[TRANSFER_ITEMS_MENU])->transferItemToContainer(itemToXfer);
                        scene->player->inventory[selection]->stackSize -= numToXfer;
                        rebuildElements();
                        scene->menus[TRANSFER_ITEMS_MENU]->rebuildElements();
                    }
                    });
                scene->addPrompt(qtyPrompt);
            }
            else {
                ((TransferItemsMenu*)scene->menus[TRANSFER_ITEMS_MENU])->transferItemToContainer(scene->player->inventory[selection]);
                scene->player->removeItemFromInventory(selection);
                scene->menus[TRANSFER_ITEMS_MENU]->rebuildElements();
            }
        }
        });

    addElement(IVENTORY_TRANSFER_BUTTON, xferBtn);

    defineEquipmentSlots();
}

void InventoryMenu::defineEquipmentSlots()
{
    displaySlots[HEAD_SLOT] = EquipmentDisplaySlot{(int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.036), 0, 0, UiElement(scene, -1)};
    displaySlots[NECK_SLOT] = EquipmentDisplaySlot{(int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.036), 0, 0, UiElement(scene, -1)};
    displaySlots[SHOULDERS_SLOT] = EquipmentDisplaySlot{(int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.036), 0, 0, UiElement(scene, -1)};
    displaySlots[BODY_SLOT] = EquipmentDisplaySlot{(int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.096), 0, 0, UiElement(scene, -1)};
    displaySlots[ARMS_SLOT] = EquipmentDisplaySlot{(int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.036), 0, 0, UiElement(scene, -1)};
    displaySlots[HANDS_SLOT] = EquipmentDisplaySlot{(int)(scene->engine->screenWidth * 0.04),(int)(scene->engine->screenHeight * 0.14), 0, 0, UiElement(scene, -1)};
    displaySlots[LEFT_HAND] = EquipmentDisplaySlot{(int)(scene->engine->screenWidth * 0.04),(int)(scene->engine->screenHeight * 0.2), 0, 0, UiElement(scene, -1)};
    displaySlots[RIGHT_HAND] = EquipmentDisplaySlot{(int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.036), 0, 0, UiElement(scene, -1)};
    displaySlots[LEFT_RING_SLOT] = EquipmentDisplaySlot{(int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.2), 0, 0, UiElement(scene, -1)};
    displaySlots[RIGHT_RING_SLOT] = EquipmentDisplaySlot{(int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.036), 0, 0, UiElement(scene, -1)};
    displaySlots[BELT_SLOT] = EquipmentDisplaySlot{(int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.036), 0, 0, UiElement(scene, -1)};
    displaySlots[LEGS_SLOT] = EquipmentDisplaySlot{(int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.18), 0, 0, UiElement(scene, -1)};
    displaySlots[FEET_SLOT] = EquipmentDisplaySlot{(int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.23), 0, 0, UiElement(scene, -1)};
}


void InventoryMenu::init()
{
    scene = nullptr;
}
