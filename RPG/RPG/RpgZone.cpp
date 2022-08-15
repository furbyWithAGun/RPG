#include "RpgZone.h"
#include "RpgUnit.h"

RpgZone::RpgZone(int newId, std::vector<std::vector<int>> tiles, RpgTileGridScene* gameScene) : ZoneMap(newId, tiles)
{
    init(gameScene);
}

RpgZone::RpgZone(int newId, RpgTileGridScene* gameScene) : ZoneMap(newId)
{
    init(gameScene);
}

RpgZone::RpgZone(SaveObject saveObject, RpgTileGridScene* gameScene) : ZoneMap(saveObject, gameScene)
{
    init(gameScene);
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case RPG_ZONE_TYPE:
            zoneType = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
}

RpgZone::RpgZone(const RpgZone& oldMap) : ZoneMap(oldMap)
{
    init();
    zoneType = oldMap.zoneType;
    scene = oldMap.scene;
}

RpgZone::RpgZone() : ZoneMap()
{
    init();
}

std::string RpgZone::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_RPG_ZONE) + "\n";
    }
    saveString += ZoneMap::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), RPG_ZONE_TYPE, zoneType);
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_RPG_ZONE) + "\n";
    }
    return saveString;
}


int RpgZone::getNumUnits()
{
    return getUnits().size();
}

int RpgZone::getNumUnitsOnTeam(int team)
{
    int numUnitsOnTeam = 0;

    for (auto* unit : getUnits()) {
        if (((RpgUnit*)unit)->team == team)
        {
            numUnitsOnTeam++;
        }
    }

    return numUnitsOnTeam;
}

RpgTown* RpgZone::getNearestTown(Location* location)
{
    return nullptr;
}

RpgTown* RpgZone::getNearestTown(int xpos, int ypos)
{
    return nullptr;
}

void RpgZone::update()
{
    ZoneMap::update();

    for (auto building : getBuildings())
    {
        building->update(scene);
    }
}

void RpgZone::init()
{
    zoneType = -1;
}

void RpgZone::init(RpgTileGridScene* gameScene)
{
    init();
    scene = gameScene;
}
