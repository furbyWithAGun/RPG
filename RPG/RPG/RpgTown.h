#pragma once
#include <vector>
#include "Equipment.h"
#include "Food.h"

class RpgTileGridScene;
class ZoneMap;


class RpgTown
{
public:
    RpgTown();
    RpgTown(RpgTileGridScene* gameScene);
    RpgTown(RpgTileGridScene* gameScene, int zoneMapId);

private:
    //attributes
    RpgTileGridScene* scene;
    ZoneMap* townZoneMap;
    std::vector<Item*> townInventory;
    std::vector<Equipment*> townArmoury;
    std::vector<Food*> townGranary;
        
    //methods
    void init();
};

