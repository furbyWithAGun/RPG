#pragma once
#include "Building.h"

#include "RpgGameConstants.h"

class Barracks : public Building
{
public:
    //attributes

    //constructors
    Barracks();
    Barracks(SaveObject saveObject);
    Barracks(int newWidth, int newHeight);
    Barracks(std::vector< std::vector<BuildingTile*> > newTileMap);
    Barracks(int entranceDirection);

    //methods
    int onActionAssignedUnit(RpgUnit* unit) override;
    void update(RpgTileGridScene* scene) override;

private:
    //attributed
    int troopSpawnTick;
    int troopSpawnRate;

    void init();
};

