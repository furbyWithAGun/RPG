#pragma once
#include <vector>
#include "BuildingTile.h"

class RpgUnit;
struct Location;

class Building
{
public:
    //attributes
    std::vector< std::vector<BuildingTile*> > tileMap;
    Location* tileLocation;
    int width, height;
    bool active;
    std::vector<RpgUnit*> assignedUnits;
    std::vector<Location> unitLocations;


    //constructors
    Building();
    Building(int newWidth, int newHeight);
    Building(std::vector< std::vector<BuildingTile*> > newTileMap);
    int getX();
    int getY();

    //methods
    BuildingTile* getTileAtMapLocation(int x, int y);
    virtual int onActionAssignedUnit(RpgUnit* unit);
    void assignUnit(RpgUnit* unit);
    void unAssignUnit(RpgUnit* unit);
    void setTileMap(std::vector< std::vector<BuildingTile*> > newTileMap);

private:
    //methods
    void init();

};

