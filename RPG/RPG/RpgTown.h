#pragma once
#include <vector>
#include "Equipment.h"
#include "Food.h"
#include "Building.h"

class RpgTileGridScene;
class ZoneMap;

const int TICKS_PER_TOWN_PRODUCTION = 1000;


class RpgTown
{
public:
    //attributes
    std::vector<Item*> townInventory;

    //constructors
    RpgTown();
    RpgTown(RpgTileGridScene* gameScene);
    RpgTown(RpgTileGridScene* gameScene, int zoneMapId);

    //methods
    void update();
    ZoneMap* getZoneMap();

private:
    //attributes
    int population;
    int ticksSinceTownProduction;
    RpgTileGridScene* scene;
    ZoneMap* townZoneMap;
    std::vector<Equipment*> townArmoury;
    std::vector<Food*> townGranary;
    std::vector<Building*> buildings;
        
    //methods
    void init();
    void processTownCycle();
};

