#pragma once
#include "Building.h"
#include "RpgGameConstants.h"

class Orchard : public Building
{
public:
    //attributes

    //constructors
    Orchard();
    Orchard(SaveObject saveObject);
    Orchard(int newWidth, int newHeight);
    Orchard(std::vector< std::vector<BuildingTile*> > newTileMap);
    Orchard(int entranceDirection);

    //methods
    int onActionAssignedUnit(RpgUnit* unit) override;
    void update(RpgTileGridScene* scene) override;

private:
    //attributed

    void init();
};

