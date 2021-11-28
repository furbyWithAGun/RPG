#include "RpgProvinceZone.h"
#include "RpgUnit.h"

RpgProvinceZone::RpgProvinceZone() : ZoneMap() {
    
}


RpgProvinceZone::RpgProvinceZone(int newId, std::vector< std::vector<int> > tiles) : ZoneMap(newId, tiles) {

}

RpgProvinceZone::RpgProvinceZone(int newId) : ZoneMap(newId)
{
}

RpgProvinceZone::RpgProvinceZone(SaveObject saveObject, RpgTileGridScene* gameScene) : ZoneMap(saveObject, gameScene)
{
}

RpgProvinceZone::RpgProvinceZone(const RpgProvinceZone& oldZone) : ZoneMap(oldZone)
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
