#include "OtherUnitInventoryMenu.h"
#include "RpgOverWorldScene.h"
#include "Player.h"
#include "inputPrompt.h"

struct EquipmentDisplaySlot {
    int x, y, width, height;
    UiElement icon;
};

enum INVENTORY_MENU_IDS {
    ITEMS_SCROLL_BOX,
    INVENTORY_CLOSE_BUTTON,
    INVENTORY_DROP_BUTTON,
    INVENTORY_EQUIP_BUTTON,
    INVENTORY_EAT_BUTTON,
    ITEM_SELL_BUTTON,
    IVENTORY_TRANSFER_BUTTON
};

OtherUnitInventoryMenu::OtherUnitInventoryMenu() : GameMenu()
{
    init();
}

OtherUnitInventoryMenu::OtherUnitInventoryMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos)
{
    init();
    scene = gameScene;
    buildElements();
}

OtherUnitInventoryMenu::OtherUnitInventoryMenu(RpgOverWorldScene* gameScene, int newId) : GameMenu(gameScene, newId)
{
    init();
    scene = gameScene;
    width = engine->screenWidth * 0.25;
    height = engine->screenHeight * 0.7;
    xpos = scene->mainCanvasStartX + engine->screenWidth * 0.3;
    ypos = engine->screenHeight * 0.15;
    buildElements();
}

void OtherUnitInventoryMenu::open()
{
    GameMenu::open();
    rebuildElements();
    ((ScrollBox*)getElementbyId(ITEMS_SCROLL_BOX))->displayIndex = 0;
}

void OtherUnitInventoryMenu::open(RpgUnit* newUnit)
{
    setUnit(newUnit);
    open();
}

void OtherUnitInventoryMenu::draw()
{
    if (needToRebuildElements)
    {
        rebuildElements();
        needToRebuildElements = false;
    }
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
        item = selectedUnit->inventory[items->getSelectedElementValue()];
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
    engine->renderText("Armour: " + std::to_string(selectedUnit->getAttributeLevel(UNIT_STAT_ARMOUR)), xpos + width * 0.1, ypos + height * 0.05, COLOR_WHITE);
    for (auto toolTip : toolTips)
    {
        if (toolTip->active) {
            toolTip->draw();
        }
    }
}

void OtherUnitInventoryMenu::rebuildElements()
{
    ScrollBox* items = (ScrollBox*)getElementbyId(ITEMS_SCROLL_BOX);
    items->clear();
    for (size_t i = 0; i < toolTips.size(); i++)
    {
        delete toolTips[i];
    }
    toolTips.clear();
    for (int i = 0; i < selectedUnit->inventory.size(); i++)
    {
        MenuText* txtInvItem = new MenuText(scene, selectedUnit->inventory[i]->name, 0, 0);
        HoverToolTip* toolTip = createItemToolTip(selectedUnit->inventory[i], scene);
        registerToolTip(txtInvItem, toolTip);

        if (selectedUnit->inventory[i]->generalType == FOOD) {
            txtInvItem->addBtnOneCallback([this, i]() {
                Item* selectedItem = selectedUnit->inventory[i];
                if (selectedItem->generalType == FOOD)
                {
                    Food* itemToEat = (Food*)selectedItem;
                    selectedUnit->eatFood(itemToEat);
                    if (itemToEat->stackSize <= 0)
                    {
                        selectedUnit->inventory.erase(selectedUnit->inventory.begin() + i);
                    }
                    rebuildElements();
                }
                });
        }

        if (selectedUnit->inventory[i]->stackSize > 1)
        {
            items->addElement(txtInvItem->setText(selectedUnit->inventory[i]->name + " X " + std::to_string(selectedUnit->inventory[i]->stackSize)), i);
        }
        else {
            items->addElement(txtInvItem->setText(selectedUnit->inventory[i]->name), i);
        }
    }
    items->selectedElement = nullptr;
    if (items->subElements.size() <= items->numElementsToDisplay)
    {
        items->displayIndex = 0;
    }

    for (int i = BARE_HANDS + 1; i != NUM_EQUIPMENT_SLOTS; i++)
    {
        if (selectedUnit->equippedItems[i] != nullptr)
        {
            displaySlots[i].icon = UiElement(scene, selectedUnit->equippedItems[i]->textureKey, xpos + displaySlots[i].x, ypos + displaySlots[i].y);
            displaySlots[i].icon.addOnClick([this, i]() {
                selectedUnit->unEquipItem(i);
                });
            HoverToolTip* toolTip = createItemToolTip(selectedUnit->equippedItems[i], scene);
            registerToolTip(&displaySlots[i].icon, toolTip);
        }
        else {
            displaySlots[i].icon = UiElement(scene, -1);
        }
    }
}

void OtherUnitInventoryMenu::setUnit(RpgUnit* newUnit)
{
    selectedUnit = newUnit;
}

RpgUnit* OtherUnitInventoryMenu::getSelectedUnit()
{
    return selectedUnit;
}

bool OtherUnitInventoryMenu::handleInput(InputMessage* message)
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

void OtherUnitInventoryMenu::buildElements()
{
    UiElement* silh = new UiElement(scene, TEXTURE_EQUIPPED_MENU_SILHOUETTE, xpos + width * 0.1, ypos + height * 0.1, width * 0.55, height * 0.4);
    silh->backgroundColour = COLOR_LIGHT_GREY;
    addElement(silh);

    ScrollBox* items;
    items = new ScrollBox(ITEMS_SCROLL_BOX, scene, COLOR_GREY, xpos + width * 0.1, ypos + height * 0.45, width * 0.55, height * 0.4);
    items->numElementsToDisplay = 5;
    addElement(ITEMS_SCROLL_BOX, items);

    MenuButton* closeBtn = new MenuButton(INVENTORY_CLOSE_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.1, ypos + height * 0.9);
    closeBtn->setText("Close")->addOnClick([this]() {
        this->close();
        });
    addElement(INVENTORY_CLOSE_BUTTON, closeBtn);

    MenuButton* dropBtn = new MenuButton(INVENTORY_DROP_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.45);
    dropBtn->setText("Drop")->addOnClick([this, items]() {
        int selection = items->getSelectedElementValue();
        if (selection != -1)
        {
            if (selectedUnit->inventory[selection]->stackSize > 1)
            {
                InputPrompt* qtyPrompt = new InputPrompt(scene, "Drop How Many?", COLOR_BLACK, xpos + width, ypos, scene->engine->screenWidth * 0.2, scene->engine->screenHeight * 0.2);
                qtyPrompt->setInputText(std::to_string(selectedUnit->inventory[selection]->stackSize));
                qtyPrompt->addCallBack([selection, this](std::string enteredText) {
                    int numToDrop;
                    if (stringIsAnInt(enteredText))
                    {
                        numToDrop = std::stoi(enteredText);
                    }
                    else {
                        numToDrop = 0;
                    }

                    if (numToDrop >= selectedUnit->inventory[selection]->stackSize)
                    {
                        selectedUnit->dropItemFromInventory(selection);
                    }
                    else if (numToDrop > 0) {
                        Item* itemToDrop = createNewItem(selectedUnit->inventory[selection]->textureKey); // relies on fact each item type atm has a unique textureId
                        itemToDrop->stackSize = numToDrop;
                        scene->addItemsToMap(selectedUnit->zone, selectedUnit->tileLocation->x, selectedUnit->tileLocation->y, { itemToDrop });
                        selectedUnit->inventory[selection]->stackSize -= numToDrop;
                        rebuildElements();
                    }
                    });
                scene->addPrompt(qtyPrompt);
            }
            else {
                selectedUnit->dropItemFromInventory(selection);
            }
        }
        });

    addElement(INVENTORY_DROP_BUTTON, dropBtn);

    MenuButton* equipBtn = new MenuButton(INVENTORY_EQUIP_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.35);
    equipBtn->setText("Equip")->addOnClick([this, items]() {
        if (items->getSelectedElementValue() != -1)
        {
            Item* selectedItem = selectedUnit->inventory[items->getSelectedElementValue()];
            if (selectedItem->equipable)
            {
                Equipment* itemToEquip = (Equipment*)selectedItem;
                selectedUnit->equipItem(itemToEquip);
                /*if (selectedUnit->equippedItems[itemToEquip->slot] != nullptr)
                {
                    selectedUnit->inventory.push_back(selectedUnit->equippedItems[itemToEquip->slot]);
                }
                selectedUnit->equippedItems[itemToEquip->slot] = itemToEquip;
                selectedUnit->inventory.erase(selectedUnit->inventory.begin() + items->getSelectedElementValue());
                scene->menus[EQUIPPED_MENU]->rebuildElements();
                rebuildElements();*/
                rebuildMenuElements();
            }
        }
        });
    addElement(INVENTORY_EQUIP_BUTTON, equipBtn);

    MenuButton* eatBtn = new MenuButton(INVENTORY_EAT_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.55);
    eatBtn->setText("Eat")->addOnClick([this, items]() {
        if (items->getSelectedElementValue() != -1)
        {
            Item* selectedItem = selectedUnit->inventory[items->getSelectedElementValue()];
            if (selectedItem->generalType == FOOD)
            {
                Food* itemToEat = (Food*)selectedItem;
                selectedUnit->eatFood(itemToEat);
                if (itemToEat->stackSize <= 0)
                {
                    selectedUnit->inventory.erase(selectedUnit->inventory.begin() + items->getSelectedElementValue());
                }
                rebuildMenuElements();
            }
        }
        });
    addElement(INVENTORY_EAT_BUTTON, eatBtn);

    MenuButton* sellBtn = new MenuButton(ITEM_SELL_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.15);
    sellBtn->setText("Sell")->addOnClick([this, items]() {
        if (items->getSelectedElementValue() != -1)
        {
            Item* selectedItem = selectedUnit->inventory[items->getSelectedElementValue()];
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
                            selectedUnit->gold += goldToAdd;
                            selectedUnit->deleteItemFromInventory(items->getSelectedElementValue());
                            //scene->menus[EQUIPPED_MENU]->rebuildMenuElements();
                            rebuildElements();
                        }
                        else if (numToSell > 0) {
                            int goldToAdd = (selectedItem->value * numToSell) / 2;
                            if (goldToAdd < 1)
                            {
                                goldToAdd = 1;
                            }
                            selectedUnit->gold += goldToAdd;
                            selectedItem->stackSize -= numToSell;
                            //scene->menus[EQUIPPED_MENU]->rebuildMenuElements();
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
                selectedUnit->gold += goldToAdd;
                selectedUnit->deleteItemFromInventory(items->getSelectedElementValue());
                //scene->menus[EQUIPPED_MENU]->rebuildMenuElements();
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
            if (selectedUnit->inventory[selection]->stackSize > 1)
            {
                InputPrompt* qtyPrompt = new InputPrompt(scene, "Transfer How Many?", COLOR_BLACK, xpos + width, ypos, scene->engine->screenWidth * 0.2, scene->engine->screenHeight * 0.2);
                qtyPrompt->setInputText(std::to_string(selectedUnit->inventory[selection]->stackSize));
                qtyPrompt->addCallBack([selection, this](std::string enteredText) {
                    int numToXfer;
                    if (stringIsAnInt(enteredText))
                    {
                        numToXfer = std::stoi(enteredText);
                    }
                    else {
                        numToXfer = 0;
                    }

                    if (numToXfer >= selectedUnit->inventory[selection]->stackSize)
                    {
                        ((TransferItemsMenu*)scene->menus[TRANSFER_ITEMS_MENU])->transferItemToContainer(selectedUnit->inventory[selection]);
                        selectedUnit->removeItemFromInventory(selection);
                        scene->menus[TRANSFER_ITEMS_MENU]->rebuildMenuElements();
                    }
                    else if (numToXfer > 0) {
                        Item* itemToXfer = createNewItem(selectedUnit->inventory[selection]->specificType);
                        itemToXfer->stackSize = numToXfer;
                        ((TransferItemsMenu*)scene->menus[TRANSFER_ITEMS_MENU])->transferItemToContainer(itemToXfer);
                        selectedUnit->inventory[selection]->stackSize -= numToXfer;
                        rebuildElements();
                        scene->menus[TRANSFER_ITEMS_MENU]->rebuildMenuElements();
                    }
                    });
                scene->addPrompt(qtyPrompt);
            }
            else {
                ((TransferItemsMenu*)scene->menus[TRANSFER_ITEMS_MENU])->transferItemToContainer(selectedUnit->inventory[selection]);
                selectedUnit->removeItemFromInventory(selection);
                scene->menus[TRANSFER_ITEMS_MENU]->rebuildMenuElements();
            }
        }
        });

    addElement(IVENTORY_TRANSFER_BUTTON, xferBtn);

    defineEquipmentSlots();
}

void OtherUnitInventoryMenu::defineEquipmentSlots()
{
    displaySlots[HEAD_SLOT] = EquipmentDisplaySlot{ (int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.086), 0, 0, UiElement(scene, -1) };
    displaySlots[NECK_SLOT] = EquipmentDisplaySlot{ (int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.086), 0, 0, UiElement(scene, -1) };
    displaySlots[SHOULDERS_SLOT] = EquipmentDisplaySlot{ (int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.086), 0, 0, UiElement(scene, -1) };
    displaySlots[BODY_SLOT] = EquipmentDisplaySlot{ (int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.146), 0, 0, UiElement(scene, -1) };
    displaySlots[ARMS_SLOT] = EquipmentDisplaySlot{ (int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.086), 0, 0, UiElement(scene, -1) };
    displaySlots[HANDS_SLOT] = EquipmentDisplaySlot{ (int)(scene->engine->screenWidth * 0.04),(int)(scene->engine->screenHeight * 0.19), 0, 0, UiElement(scene, -1) };
    displaySlots[LEFT_HAND] = EquipmentDisplaySlot{ (int)(scene->engine->screenWidth * 0.04),(int)(scene->engine->screenHeight * 0.25), 0, 0, UiElement(scene, -1) };
    displaySlots[RIGHT_HAND] = EquipmentDisplaySlot{ (int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.086), 0, 0, UiElement(scene, -1) };
    displaySlots[LEFT_RING_SLOT] = EquipmentDisplaySlot{ (int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.25), 0, 0, UiElement(scene, -1) };
    displaySlots[RIGHT_RING_SLOT] = EquipmentDisplaySlot{ (int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.086), 0, 0, UiElement(scene, -1) };
    displaySlots[BELT_SLOT] = EquipmentDisplaySlot{ (int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.086), 0, 0, UiElement(scene, -1) };
    displaySlots[LEGS_SLOT] = EquipmentDisplaySlot{ (int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.21), 0, 0, UiElement(scene, -1) };
    displaySlots[FEET_SLOT] = EquipmentDisplaySlot{ (int)(scene->engine->screenWidth * 0.081),(int)(scene->engine->screenHeight * 0.26), 0, 0, UiElement(scene, -1) };
}


void OtherUnitInventoryMenu::init()
{
    scene = nullptr;
    selectedUnit = nullptr;
}
