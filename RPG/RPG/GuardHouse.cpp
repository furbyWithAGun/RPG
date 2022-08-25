#include "GuardHouse.h"

#include "RpgUnit.h"
#include "SelectPrompt.h"
#include "RpgTileGridScene.h"
#include "ZoneMap.h"

GuardHouse::GuardHouse() : Building()
{
    init();
}

GuardHouse::GuardHouse(SaveObject saveObject) : Building(saveObject)
{
    init();
}

GuardHouse::GuardHouse(int newWidth, int newHeight) : Building(newWidth, newHeight)
{
    init();
}

GuardHouse::GuardHouse(std::vector<std::vector<BuildingTile*>> newTileMap) : Building(newTileMap)
{
    init();
}

GuardHouse::GuardHouse(int entranceDirection) : Building()
{
    init();
    setTileMap({
    {new BuildingTile(false, TEXTURE_GUARDHOUSE_TOP),
    new BuildingTile(false, TEXTURE_GUARDHOUSE_BOTTOM)}
        });
}


void GuardHouse::update(RpgTileGridScene* scene)
{
    RpgTown* localTown = ((RpgZone*)scene->currentZone)->getNearestTown(tileLocation);
    if (localTown != nullptr)
    {
        troopSpawnTick++;
        if (troopSpawnTick >= troopSpawnRate)
        {
            troopSpawnTick = 0;
            if (localTown->getNumTrainedSoldiers() > 0 && assignedUnits.size() < maxTroops)
            {
                localTown->subtractFromTrainedSoldiers(1);
                RpgUnit* newUnit = new Soldier(zone->id, SOLDIER, scene, tileLocation->x, tileLocation->y + 1);
                zone->addUnitToLocation(newUnit, tileLocation->x, tileLocation->y + 1);
                assignUnit(newUnit);
            }
        }
    }

    for (auto unit : assignedUnits) {
        if (unit->zone == zone->id && zone->manhattenDistance(unit->tileDestination, tileLocation) > 5)
        {
            unit->setTargetLocation(tileLocation->x, tileLocation->y + 2);
        }
    }
}


void GuardHouse::init()
{
    type = BUILDING_GUARDHOUSE;
    iconTextureId = BUILDING_ICON_BLACKSMITH;
    goldCost = 100;
    woodCost = 10;
    troopSpawnTick = 0;
    troopSpawnRate = 1000;
    buildingName = "Guard House";
    popCost = 0;
    maxTroops = 2;
    setCanBeBuiltOnOverworld(true);
    //popSupported = 2;
}
