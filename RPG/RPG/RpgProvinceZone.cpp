#include "RpgProvinceZone.h"
#include "RpgUnit.h"

RpgProvinceZone::RpgProvinceZone() : RpgZone() {
    
}


RpgProvinceZone::RpgProvinceZone(int newId, std::vector< std::vector<int> > tiles, RpgTileGridScene* gameScene) : RpgZone(newId, tiles, gameScene) {

}

RpgProvinceZone::RpgProvinceZone(int newId, RpgTileGridScene* gameScene) : RpgZone(newId, gameScene)
{
}

RpgProvinceZone::RpgProvinceZone(SaveObject saveObject, RpgTileGridScene* gameScene) : RpgZone(saveObject, gameScene)
{
}

RpgProvinceZone::RpgProvinceZone(const RpgProvinceZone& oldZone) : RpgZone(oldZone)
{
}

int RpgProvinceZone::getNumUnits()
{
    return getUnits().size();
}

int RpgProvinceZone::getNumUnitsOnTeam(int team)
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

void RpgProvinceZone::addTownToZone(RpgTown* townToAdd)
{
    towns.push_back(townToAdd);
}
