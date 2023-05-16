#pragma once
#include "Building.h"
class SmeltingWorks :  public Building
{
public:
    //attributes

    //constructors
    SmeltingWorks();
    SmeltingWorks(SaveObject saveObject);
    SmeltingWorks(int newWidth, int newHeight);
    SmeltingWorks(std::vector< std::vector<BuildingTile*> > newTileMap);
    SmeltingWorks(int entranceDirection);

    //methods

private:
    //attributed

    void init();
};

