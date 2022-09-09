#pragma once
#include "Building.h"

#include "RpgGameConstants.h"

class House : public Building
{
public:
    //attributes

    //constructors
    House();
    House(SaveObject saveObject);
    House(int newWidth, int newHeight);
    House(std::vector< std::vector<BuildingTile*> > newTileMap);
    House(int entranceDirection);

    //methods
    int onActionAssignedUnit(RpgUnit* unit) override;

private:
    //attributed

    void init();
};

