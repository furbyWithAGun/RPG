#include "GuardHouse.h"

#include "RpgUnit.h"
#include "SelectPrompt.h"
#include "RpgTileGridScene.h"

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
    if (zone != nullptr && ((RpgZone*)zone)->zoneType == ZONE_RPG_TOWN)
    {
        troopSpawnTick++;
        if (troopSpawnTick >= troopSpawnRate)
        {
            troopSpawnTick = 0;
            if (((RpgTown*)zone)->getNumTrainedSoldiers() > 0 && assignedUnits.size() < maxTroops)
            {
                ((RpgTown*)zone)->subtractFromTrainedSoldiers(1);
                ((RpgTown*)zone)->addUnitToLocation(new Soldier(zone->id, SOLDIER, scene, tileLocation->x, tileLocation->y + 1), tileLocation->x, tileLocation->y + 1);
            }
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
    canBeBuiltOnOverworld = true;
    //popSupported = 2;
}
