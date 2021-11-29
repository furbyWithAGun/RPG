#include "RpgZone.h"

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
    saveString += getAttributeString(getUniqueId(), RPG_ZONE_TYPE, zoneType);
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_RPG_ZONE) + "\n";
    }
    return saveString;
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
