#include "itemBuyMenu.h"
#include "RpgOverWorldScene.h"
#include "ItemShop.h"
#include "Player.h"

enum ITEM_BUY_MENU_IDS {
    ITEMS_SCROLL_BOX,
    ITEM_BUY_CLOSE_BUTTON,
    ITEM_BUY_BUTTON,
};

ItemBuyMenu::ItemBuyMenu() : GameMenu()
{
    init();
}

ItemBuyMenu::ItemBuyMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos)
{
    init();
    scene = gameScene;
    buildElements();
}

void ItemBuyMenu::open()
{
    GameMenu::open();
    scene->closeMenu(INVENTORY_MENU);
}

void ItemBuyMenu::draw()
{
    GameMenu::draw();
}

void ItemBuyMenu::update()
{
    ScrollBox* items = (ScrollBox*)getElementbyId(ITEMS_SCROLL_BOX);
    items->clear();
    for (int i = 0; i < itemShop->itemsForSale.size(); i++)
    {
        items->addElement(new MenuText(scene, itemShop->itemsForSale[i]->name + " Cost: " + std::to_string(itemShop->itemsForSale[i]->value * 2), 0, 0), i);
    }
    items->selectedElement = nullptr;
}

bool ItemBuyMenu::handleInput(InputMessage* message)
{
    return GameMenu::handleInput(message);
}

void ItemBuyMenu::setItemShop(ItemShop* newItemShop)
{
    itemShop = newItemShop;
}

void ItemBuyMenu::buildElements()
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
                    scene->player->inventory.push_back(new Weapon(*(Weapon*)selectedItem));
                    break;
                case ARMOUR:
                    scene->player->inventory.push_back(new Armour(*(Armour*)selectedItem));
                    break;
                default:
                    if (selectedItem->equipable)
                    {
                        scene->player->inventory.push_back(new Equipment(*(Equipment*)selectedItem));
                    }
                    else {
                        scene->player->inventory.push_back(new Item(*(Item*)selectedItem));
                    }
                    break;
                }
            }
            update();
        }
        });
    addElement(ITEM_BUY_BUTTON, equipBtn);
}

void ItemBuyMenu::init()
{
    scene = nullptr;
}


