#pragma once
#include "ZoneMap.h"

class RpgTileGridScene;

enum RPG_ZONE_ATTRIBUTES {
    RPG_ZONE_TYPE = 1000
};

class RpgZone : public ZoneMap
{
public:
    //attributes
    int zoneType;

    //constructors
    RpgZone(int newId, std::vector< std::vector<int> > tiles, RpgTileGridScene* gameScene);
    RpgZone(int newId, RpgTileGridScene* gameScene);
    RpgZone(SaveObject saveObject, RpgTileGridScene* gameScene);
    RpgZone(const RpgZone& oldMap);
    RpgZone();

    //methods
    int getNumUnits();
    int getNumUnitsOnTeam(int team);

    virtual std::string toSaveString(bool withHeaderAndFooter = true) override;

protected:
    //attributes
    RpgTileGridScene* scene;

private:

    void init();
    void init(RpgTileGridScene* gameScene);
};

