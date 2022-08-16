#pragma once
#include "Building.h"
#include "RpgGameConstants.h"

class WoodCutter : public Building
{
public:
    //attributes

    //constructors
    WoodCutter();
    WoodCutter(SaveObject saveObject);
    WoodCutter(int newWidth, int newHeight);
    WoodCutter(std::vector< std::vector<BuildingTile*> > newTileMap);
    WoodCutter(int entranceDirection);

    //methods
    int onActionAssignedUnit(RpgUnit* unit) override;
    void update(RpgTileGridScene* scene) override;

private:
    //attributed

    void init();
};

