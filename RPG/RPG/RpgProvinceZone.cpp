#include "RpgProvinceZone.h"
#include "RpgUnit.h"
#include "RpgTileGridScene.h"
//#include "RpgTown.h"

RpgProvinceZone::RpgProvinceZone() : RpgZone() {
    init();
}


RpgProvinceZone::RpgProvinceZone(int newId, std::vector< std::vector<int> > tiles, RpgTileGridScene* gameScene) : RpgZone(newId, tiles, gameScene) {
    init();
}

RpgProvinceZone::RpgProvinceZone(int newId, RpgTileGridScene* gameScene) : RpgZone(newId, gameScene)
{
    init();
}

RpgProvinceZone::RpgProvinceZone(SaveObject saveObject, RpgTileGridScene* gameScene) : RpgZone(saveObject, gameScene)
{
    init();
}

RpgProvinceZone::RpgProvinceZone(const RpgProvinceZone& oldZone) : RpgZone(oldZone)
{
    init();
    towns = oldZone.towns;
}

void RpgProvinceZone::addTownToZone(RpgTown* townToAdd)
{
    towns.push_back(townToAdd);
}

RpgTown* RpgProvinceZone::getNearestTown(Location* location)
{
    RpgTown* returnZone = nullptr;
    int closestCoords[2] = { -1, -1 };
    for (auto portal : getPortals()) {
        if (((RpgZone*)scene->getZone(portal->exitZoneId))->zoneType == ZONE_RPG_TOWN)
        {
            if (!returnZone)
            {
                returnZone = ((RpgTown*) scene->getZone(portal->exitZoneId));
                closestCoords[0] = portal->tileCoords[0];
                closestCoords[1] = portal->tileCoords[1];
            }
            else if (manhattenDistance(location->x, location->y, portal->tileCoords[0], portal->tileCoords[1]) < manhattenDistance(location->x, location->y, closestCoords[0], closestCoords[1])){
                returnZone = ((RpgTown*)scene->getZone(portal->exitZoneId));
                closestCoords[0] = portal->tileCoords[0];
                closestCoords[1] = portal->tileCoords[1];
            }
        }
    }
    return returnZone;
}

RpgTown* RpgProvinceZone::getNearestTown(int xpos, int ypos)
{
    RpgTown* returnZone = nullptr;
    int closestCoords[2] = { -1, -1 };
    for (auto portal : getPortals()) {
        if (((RpgZone*)scene->getZone(portal->exitZoneId))->zoneType == ZONE_RPG_TOWN)
        {
            if (!returnZone)
            {
                returnZone = ((RpgTown*)scene->getZone(portal->exitZoneId));
                closestCoords[0] = portal->tileCoords[0];
                closestCoords[1] = portal->tileCoords[1];
            }
            else if (manhattenDistance(xpos, ypos, portal->tileCoords[0], portal->tileCoords[1]) < manhattenDistance(xpos, ypos, closestCoords[0], closestCoords[1])) {
                returnZone = ((RpgTown*)scene->getZone(portal->exitZoneId));
                closestCoords[0] = portal->tileCoords[0];
                closestCoords[1] = portal->tileCoords[1];
            }
        }
    }
    return returnZone;
}

std::string RpgProvinceZone::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_RPG_PROVINCE) + "\n";
    }
    saveString += RpgZone::toSaveString(false);
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_RPG_PROVINCE) + "\n";
    }
    return saveString;
}

void RpgProvinceZone::init()
{
    zoneType = ZONE_RPG_PROVINCE;
}
