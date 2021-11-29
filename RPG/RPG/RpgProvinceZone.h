#pragma once
#include "RpgZone.h"

enum RPG_ZONE_TYPES {
    ZONE_PROVINCE,
    ZONE_TOWN,
    ZONE_CAVE
};

class RpgProvinceZone : public RpgZone
{
public:
    //constructors
    RpgProvinceZone();
    RpgProvinceZone(int newId, std::vector< std::vector<int> > tiles, RpgTileGridScene* gameScene);
    RpgProvinceZone(int newId, RpgTileGridScene* gameScene);
    RpgProvinceZone(SaveObject saveObject, RpgTileGridScene* gameScene);
    RpgProvinceZone(const RpgProvinceZone& oldZone);

    //methods
    int getNumUnits();
    int getNumUnitsOnTeam(int team);
    void addTownToZone(RpgTown* townToAdd);

private:
    //attributes
    std::vector<RpgTown*> towns;
};

