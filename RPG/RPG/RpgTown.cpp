#include "RpgTown.h"
#include "RpgTileGridScene.h"

RpgTown::RpgTown()
{
    init();
}

RpgTown::RpgTown(RpgTileGridScene* gameScene)
{
    init();
}

RpgTown::RpgTown(RpgTileGridScene* gameScene, int zoneMapId)
{
    init();
}

void RpgTown::update()
{
    ticksSinceTownProduction++;
    if (ticksSinceTownProduction > TICKS_PER_TOWN_PRODUCTION)
    {
        processTownCycle();
        ticksSinceTownProduction = 0;
    }
}

std::vector<Item*>& RpgTown::getTownInventory()
{
    return townInventory;
}

int RpgTown::getTownGold()
{
    return townGold;
}

void RpgTown::setTownGold(int goldAmount)
{
    townGold = goldAmount;
}

bool RpgTown::subtractFromTownGold(int goldAmount)
{
    townGold -= goldAmount;
    if (townGold < 0)
    {
        townGold = 0;
        return false;
    }
    return true;
}

void RpgTown::addToTownGold(int goldAmount)
{
    townGold += goldAmount;
}

void RpgTown::init()
{
    townGold = 0;
    ticksSinceTownProduction = 0;
    population = 0;
}

void RpgTown::processTownCycle()
{
    population++;
    std::vector<Item*> producedItems;
    for (auto building : getBuildings()){
        for (auto item : building->production(this)) {
            producedItems.push_back(item);
        }
    }
    for (auto item : producedItems)
    {
        addItemToContainer(item, getTownInventory());
    }
    scene->menus[TRANSFER_ITEMS_MENU]->rebuildElements();
}
