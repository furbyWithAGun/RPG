#pragma once
#include <vector>
#include "Equipment.h"
#include "Food.h"
#include "Building.h"
#include "RpgZone.h"

class RpgTileGridScene;
class RpgZone;

const int TICKS_PER_TOWN_PRODUCTION = 1000;


class RpgTown : public RpgZone
{
public:
    //constructors
    RpgTown();
    RpgTown(RpgTileGridScene* gameScene);
    RpgTown(RpgTileGridScene* gameScene, int zoneMapId);

    //methods
    void update();
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
    std::vector<Item*> townInventory;
    std::vector<Equipment*> townArmoury;
    std::vector<Food*> townGranary;
        
    //methods
    void init();
    void processTownCycle();
};

