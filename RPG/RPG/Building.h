#pragma once
#include <vector>
#include "BuildingTile.h"

class Unit;
struct Location;

class Building
{
public:
    //attributes
    std::vector< std::vector<BuildingTile*> > tileMap;
    Location* tileLocation;
    int width, height;
    bool active;
    std::vector<Unit*> assignedUnits;


    //constructors
    Building();
    Building(int newWidth, int newHeight);
    Building(std::vector< std::vector<BuildingTile*> > newTileMap);
    int getX();
    int getY();

    //methods
    BuildingTile* getTileAtMapLocation(int x, int y);
    virtual int onActionAssignedUnit(Unit* unit);
    void assignUnit(Unit* unit);
    void unAssignUnit(Unit* unit);

private:
    //methods
    void init();

};

