#pragma once
#include <vector>
#include "Equipment.h"
#include "Food.h"
#include "Building.h"

class RpgTileGridScene;
class RpgZone;

const int TICKS_PER_TOWN_PRODUCTION = 1000;


class RpgTown
{
public:
    //attributes
    int id;

    //constructors
    RpgTown();
    RpgTown(RpgTileGridScene* gameScene);
    RpgTown(RpgTileGridScene* gameScene, int zoneMapId);

    //methods
    void update();
    RpgZone* getZoneMap();
    void setTownZoneMap(RpgZone* newTownZoneMap);
    void addBuilding(Building* newBuilding);
    void removeBuilding(Building* building);
    std::vector<Item*>& getTownInventory();
    int getTownGold();
    void setTownGold(int goldAmount);
    bool subtractFromTownGold(int goldAmount);
    void addToTownGold(int goldAmount);

private:
    //attributes
    int population;
    int ticksSinceTownProduction;
    int townGold;
    RpgTileGridScene* scene;
    RpgZone* townZoneMap;
    std::vector<Item*> townInventory;
    std::vector<Equipment*> townArmoury;
    std::vector<Food*> townGranary;
    std::vector<Building*> buildings;
        
    //methods
    void init();
    void processTownCycle();
    //building vector
    void addToBuildingVector(Building* buildingToAdd);
    void removeFromBuildingVector(Building* buildingToRemove);
};

