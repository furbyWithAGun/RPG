#include "RpgTown.h"
#include "RpgTileGridScene.h"

RpgTown::RpgTown()
{
    init();
}

RpgTown::RpgTown(RpgTileGridScene* gameScene)
{
    init();
    scene = gameScene;
}

RpgTown::RpgTown(RpgTileGridScene* gameScene, int zoneMapId)
{
    init();
    scene = gameScene;
    townZoneMap = scene->getZone(zoneMapId);
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

ZoneMap* RpgTown::getZoneMap()
{
    return townZoneMap;
}

void RpgTown::addBuilding(Building* newBuilding)
{
    addToBuildingVector(newBuilding);
}

void RpgTown::removeBuilding(Building* building)
{
    removeFromBuildingVector(building);
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
    scene = nullptr;
    townZoneMap = nullptr;
}

void RpgTown::processTownCycle()
{
    population++;
    std::vector<Item*> producedItems;
    for (auto building : buildings){
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

void RpgTown::addToBuildingVector(Building* buildingToAdd)
{
    if (std::find(buildings.begin(), buildings.end(), buildingToAdd) == buildings.end())
    {
        buildings.push_back(buildingToAdd);
    }
}

void RpgTown::removeFromBuildingVector(Building* buildingToRemove)
{
    auto buildingIterator = buildings.begin();
    while (buildingIterator != buildings.end())
    {
        if ((*buildingIterator) == buildingToRemove) {
            buildingIterator = buildings.erase(buildingIterator);
        }
        else {
            buildingIterator++;
        }
    }
}
