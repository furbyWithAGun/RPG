#include "itemShopMenu.h"
#include "RpgOverWorldScene.h"
#include "ItemShop.h"
#include "Player.h"

enum ITEM_SHOP_MENU_IDS {
    ITEMS_SCROLL_BOX,
    ITEM_BUY_CLOSE_BUTTON,
    ITEM_BUY_BUTTON,
};

ItemShopMenu::ItemShopMenu() : GameMenu()
{
    init();
}

ItemShopMenu::ItemShopMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos)
{
    init();
    scene = gameScene;
    buildElements();
}

void ItemShopMenu::open()
{
    GameMenu::open();
    scene->closeMenu(INVENTORY_MENU);
    rebuildElements();
}

void ItemShopMenu::draw()
{
    GameMenu::draw();
}

void ItemShopMenu::rebuildElements()
{
    ScrollBox* items = (ScrollBox*)getElementbyId(ITEMS_SCROLL_BOX);
    items->clear();
    toolTips.clear();
    for (int i = 0; i < itemShop->itemsForSale.size(); i++)
    {
        MenuText* txtInvItem = new MenuText(scene, itemShop->itemsForSale[i]->name + " Cost: " + std::to_string(itemShop->itemsForSale[i]->value * 2), 0, 0);
        HoverToolTip* toolTip = createItemToolTip(itemShop->itemsForSale[i], scene);
        toolTip->setScene(scene);
        registerToolTip(txtInvItem, toolTip);
        items->addElement(txtInvItem, i);
    }
    items->selectedElement = nullptr;
}

bool ItemShopMenu::handleInput(InputMessage* message)
{
    if (message->id == BUTTON_2_ON || message->id == BUTTON_3_ON || message->id == BUTTON_4_ON || message->id == BUTTON_5_ON)
    {
        close();
        return false;
    }
    return GameMenu::handleInput(message);
}

void ItemShopMenu::setItemShop(ItemShop* newItemShop)
{
    itemShop = newItemShop;
}

void ItemShopMenu::buildElements()
{
    ScrollBox* items;
    items = new ScrollBox(ITEMS_SCROLL_BOX, scene, COLOR_GREY, xpos + width * 0.1, ypos + height * 0.1, width * 0.55, height * 0.7);
    items->numElementsToDisplay = 5;
    addElement(ITEMS_SCROLL_BOX, items);

    MenuButton* closeBtn = new MenuButton(ITEM_BUY_CLOSE_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.1, ypos + height * 0.85);
    closeBtn->setText("Close")->addOnClick([this]() {
        this->close();
        });
    addElement(ITEM_BUY_CLOSE_BUTTON, closeBtn);

    MenuButton* equipBtn = new MenuButton(ITEM_BUY_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.15);
    equipBtn->setText("Buy")->addOnClick([this, items]() {
        if (items->getSelectedElementValue() != -1)
        {
            Item* selectedItem = itemShop->itemsForSale[items->getSelectedElementValue()];
            if (scene->player->gold >= selectedItem->value * 2)
            {
                scene->player->gold -= selectedItem->value * 2;
                switch (selectedItem->type)
                {
                case WEAPON:
                    scene->player->addToInventory(new Weapon(*(Weapon*)selectedItem));
                    break;
                case ARMOUR:
                    scene->player->addToInventory(new Armour(*(Armour*)selectedItem));
                    break;
                default:
                    if (selectedItem->equipable)
                    {
                        scene->player->addToInventory(new Equipment(*(Equipment*)selectedItem));
                    }
                    else {
                        scene->player->addToInventory(new Item(*(Item*)selectedItem));
                    }
                    break;
                }
            }
            update();
        }
        });
    addElement(ITEM_BUY_BUTTON, equipBtn);
}

void ItemShopMenu::init()
{
    scene = nullptr;
}


