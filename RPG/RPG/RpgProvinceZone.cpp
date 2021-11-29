#include "RpgProvinceZone.h"
#include "RpgUnit.h"

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
