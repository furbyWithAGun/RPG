#pragma once
#include <vector>
#include "BuildingTile.h"
#include <string>

class RpgUnit;
struct Location;

enum BUILDING_SAVE_ATTRIBUTES {
    BULDING_TYPE,
    BUILDING_TILE_MAP,
    BUILDING_LOCATION,
    BUILDING_ACTIVE,
    BUILDING_ASSIGNED_UNITS,
    BUILDING_UNIT_LOCATIONS,
    BUILDING_ID,
    BUILDING_ICON_TEXTURE_ID
};

class Building
{
public:
    //attributes
    int type;
    int id;
    int iconTextureId;
    std::vector< std::vector<BuildingTile*> > tileMap;
    Location* tileLocation;
    int width, height;
    bool active;
    std::vector<RpgUnit*> assignedUnits;
    std::vector<Location> unitLocations;


    //constructors
    Building();
    Building(SaveObject saveObject);
    Building(int buildingType);
    Building(int newWidth, int newHeight);
    Building(int buildingType, int newWidth, int newHeight);
    Building(std::vector< std::vector<BuildingTile*> > newTileMap);
    Building(int buildingType, std::vector< std::vector<BuildingTile*> > newTileMap);
    int getX();
    int getY();

    //methods
    BuildingTile* getTileAtMapLocation(int x, int y);
    virtual int onActionAssignedUnit(RpgUnit* unit);
    void assignUnit(RpgUnit* unit);
    void unAssignUnit(RpgUnit* unit);
    void setTileMap(std::vector< std::vector<BuildingTile*> > newTileMap);
    std::string toSaveString();
    std::string getBuildingTileMapSaveString();
    std::vector<std::vector<BuildingTile*>> getBuldingTileMapFromSaveString(std::string saveString);
    std::vector<BuildingTile*> getBuldingTileVectorFromSaveString(std::string saveString);

private:
    //methods
    void init();
    void init(int buildingType);
};

int getUniqueBuildingId();