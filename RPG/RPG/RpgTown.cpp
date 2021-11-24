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

void RpgTown::init()
{
    ticksSinceTownProduction = 0;
    population = 0;
    scene = nullptr;
    townZoneMap = nullptr;
}

void RpgTown::processTownCycle()
{
    population++;
    for (auto building : buildings){

    }
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
