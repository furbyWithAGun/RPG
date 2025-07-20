#pragma once
#include <vector>
#include "BuildingTile.h"
#include <string>
#include "ItemFactory.h"

const int DEFAULT_UNIT_TETHER_DISTANCE = 5;

class RpgUnit;
class DooDad;
struct Location;
class RpgTown;
class ZoneMap;
class RpgTileGridScene;

struct ProductionInputOutput {
    int itemType;
    int qty;
};

struct DoodadOnConstruct{
    int doodadType;
    int x;
    int y;
};

enum BUILDING_SAVE_ATTRIBUTES {
    BULDING_TYPE,
    BUILDING_TILE_MAP,
    BUILDING_LOCATION,
    BUILDING_ACTIVE,
    BUILDING_ASSIGNED_UNITS,
    BUILDING_UNIT_LOCATIONS,
    BUILDING_ID,
    BUILDING_ICON_TEXTURE_ID,
    BUILDING_GOLD_COST,
    BUILDING_WOOD_COST,
    BUILDING_PRODUCTION_GOLD_COST
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
    int goldCost;
    int woodCost;
    std::vector<RpgUnit*> housedUnits;
    std::vector<Location> unitLocations;
    std::vector<DoodadOnConstruct> doodadsOnConstruct;


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
    virtual void update(RpgTileGridScene* scene);
    BuildingTile* getTileAtMapLocation(int x, int y);
    virtual int onActionAssignedUnit(RpgUnit* unit);
    virtual int onActionAssignedDooDad(DooDad* dooDad);
    void assignUnit(RpgUnit* unit);
    void houseUnit(RpgUnit* unit);
    void unAssignUnit(RpgUnit* unit);
    void unHouseUnit(RpgUnit* unit);
    void assignDooDad(DooDad* dooDad);
    void unAssignDooDad(DooDad* dooDad);
    void setTileMap(std::vector< std::vector<BuildingTile*> > newTileMap);
    std::string toSaveString();
    std::string getBuildingTileMapSaveString();
    std::vector<std::vector<BuildingTile*>> getBuldingTileMapFromSaveString(std::string saveString);
    std::vector<BuildingTile*> getBuldingTileVectorFromSaveString(std::string saveString);
    static void resetUid();
    virtual std::vector<Item*> production(RpgTown* town);
    void setZone(ZoneMap* newZone);
    int getPopSupported();
    std::string getBuildingName();
    bool canBeBuiltOnOverworld();
    void setCanBeBuiltOnOverworld(bool newVal);
    std::vector<ProductionInputOutput> getProductionOutputs();
    RpgUnit* createHousedUnit(RpgTileGridScene* scene);


    std::vector<RpgUnit*> getAssignedUnits();
    std::vector<DooDad*> getAssignedDooDads();

protected:
    //attributes
    int maxUnits;
    int spawnedUnitType;
    int unitTeatherLocationOffset[2];
    int popSupported;
    bool unitRandomMovement;
    std::string buildingName;
    std::vector<ProductionInputOutput> productionInputs;
    std::vector<ProductionInputOutput> productionOutputs;
    ZoneMap* zone;

    std::vector<RpgUnit*> assignedUnits;
    std::vector<DooDad*> assignedDooDads;

private:
    //attributes
    int productionGoldCost;
    bool overworldBuildable;
    int tetherUnitDistance;
    //methods
    void init();
    void init(int buildingType);
    bool townCanAfffordProduction(RpgTown* town);
    virtual std::vector<Item*> createOutputs(RpgTown* town);
};

int getUniqueBuildingId();