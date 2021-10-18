#include "ItemShop.h"
#include "Unit.h"
#include "ItemSellMenu.h"
#include "SelectPrompt.h"

ItemShop::ItemShop() : Building()
{
}

ItemShop::ItemShop(int newWidth, int newHeight) : Building(newWidth, newHeight)
{
}

ItemShop::ItemShop(std::vector<std::vector<BuildingTile*>> newTileMap) : Building(newTileMap)
{
}

int ItemShop::onActionAssignedUnit(Unit* unit)
{
    SelectPrompt* shopSelectPrompt;
    shopSelectPrompt = new SelectPrompt(unit->scene, COLOR_BLACK, unit->scene->engine->screenWidth * 0.5, unit->scene->engine->screenHeight * 0.5, unit->scene->engine->screenWidth * 0.1, unit->scene->engine->screenHeight * 0.1);
    shopSelectPrompt->addSelectOption("Buy Items", 1);
    shopSelectPrompt->addSelectOption("Sell Items", 2);
    shopSelectPrompt->addCallBack([this, shopSelectPrompt, unit]() {
        switch (shopSelectPrompt->getSelectedOptionValue())
        {
        case 1:
            ((ItemSellMenu*)unit->scene->menus[ITEM_BUY_MENU])->setItemShop(this);
            unit->scene->menus[ITEM_BUY_MENU]->open();
            break;
        case 2:
            ((ItemSellMenu*)unit->scene->menus[ITEM_SELL_MENU])->setItemShop(this);
            unit->scene->menus[ITEM_SELL_MENU]->open();
            break;
        default:
            break;
        }
        unit->scene->removePrompt(shopSelectPrompt);
        });
    shopSelectPrompt->active = true;
    shopSelectPrompt->closeOnClickMiss = true;
    unit->scene->addPrompt(shopSelectPrompt);
    return 0;
}

void ItemShop::setItemsForSale(std::vector<Item*> newItemsForSale)
{
    itemsForSale = newItemsForSale;
}
