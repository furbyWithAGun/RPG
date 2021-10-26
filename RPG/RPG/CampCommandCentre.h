#pragma once
#include "Building.h"

#include "RpgGameConstants.h"

class CampCommandCentre : public Building
{
public:
    //attributes

    //constructors
    CampCommandCentre();
    CampCommandCentre(SaveObject saveObject);
    CampCommandCentre(int newWidth, int newHeight);
    CampCommandCentre(std::vector< std::vector<BuildingTile*> > newTileMap);
    CampCommandCentre(int entranceDirection);

    //methods
    int onActionAssignedUnit(RpgUnit* unit) override;

private:
    void init();
};

