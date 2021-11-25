#include "ItemShop.h"
#include "RpgUnit.h"
#include "ItemShopMenu.h"
#include "SelectPrompt.h"
#include "RpgTileGridScene.h"

ItemShop::ItemShop() : Building()
{
    init();
}

ItemShop::ItemShop(SaveObject saveObject) : Building(saveObject)
{
    init();
}

ItemShop::ItemShop(int newWidth, int newHeight) : Building(newWidth, newHeight)
{
    init();
}

ItemShop::ItemShop(std::vector<std::vector<BuildingTile*>> newTileMap) : Building(newTileMap)
{
    init();
}

ItemShop::ItemShop(int entranceDirection) : Building()
{
    init();
    switch (entranceDirection)
    {
    case LEFT:
        setTileMap({
        {new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), nullptr, new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), nullptr, nullptr, nullptr, new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), nullptr, nullptr, nullptr, new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), nullptr, nullptr, nullptr, new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO) },
        });
        
        break;
    case RIGHT:
        setTileMap({
        {new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), nullptr, nullptr, nullptr, new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), nullptr, nullptr, nullptr, new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), nullptr, nullptr, nullptr, new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), nullptr, new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO) },
            });

        break;
    default:
        break;
    }
}

int ItemShop::onActionAssignedUnit(RpgUnit* unit)
{
    SelectPrompt* shopSelectPrompt;
    shopSelectPrompt = new SelectPrompt(unit->scene, COLOR_BLACK, unit->scene->engine->screenWidth * 0.5, unit->scene->engine->screenHeight * 0.5, unit->scene->engine->screenWidth * 0.1, unit->scene->engine->screenHeight * 0.1);
    shopSelectPrompt->addSelectOption("Buy/Sell Items", 1);
    shopSelectPrompt->addCallBack([this, shopSelectPrompt, unit]() {
        switch (shopSelectPrompt->getSelectedOptionValue())
        {
        case 1:
            ((ItemShopMenu*)unit->scene->menus[ITEM_SHOP_MENU])->setItemShop(this);
            unit->scene->menus[ITEM_SHOP_MENU]->open();
            unit->scene->menus[INVENTORY_MENU]->open();
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

void ItemShop::init()
{
    productionOutputs.push_back({ITEM_SHORT_SWORD, 1});
    productionInputs.push_back({ITEM_WOOD, 1});
    type = BUILDING_ITEM_SHOP;
    iconTextureId = BUILDING_ICON_WEAPON_SHOP;
    goldCost = 700;
    woodCost = 10;
    setItemsForSale({ createNewItem(ITEM_CLUB), createNewItem(ITEM_SHORT_SWORD),createNewItem(ITEM_MACE), createNewItem(ITEM_LONG_SWORD), createNewItem(ITEM_RAG_BODY), createNewItem(ITEM_RAG_BOOTS), createNewItem(ITEM_RAG_GLOVES), createNewItem(ITEM_RAG_HAT), createNewItem(ITEM_RAG_PANTS), createNewItem(ITEM_LINEN_BODY), createNewItem(ITEM_LINEN_BOOTS), createNewItem(ITEM_LINEN_GLOVES), createNewItem(ITEM_LINEN_HAT), createNewItem(ITEM_LINEN_PANTS), createNewItem(ITEM_LEATHER_HAT) });
}
