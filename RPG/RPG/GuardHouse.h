#pragma once
#include "Building.h"
class GuardHouse : public Building
{

public:
    //attributes

    //constructors
    GuardHouse();
    GuardHouse(SaveObject saveObject);
    GuardHouse(int newWidth, int newHeight);
    GuardHouse(std::vector< std::vector<BuildingTile*> > newTileMap);
    GuardHouse(int entranceDirection);

    //methods
    void update(RpgTileGridScene* scene) override;

private:
    //attributes
    int maxTroops;
    int troopSpawnTick;
    int troopSpawnRate;

    void init();
};

