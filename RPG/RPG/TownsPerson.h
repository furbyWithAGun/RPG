#pragma once
#include "AiUnit.h"
class TownsPerson : public AiUnit
{
public:
    //attributes

    //constructors
    TownsPerson();
    TownsPerson(int zoneId, int unitType);
    TownsPerson(int zoneId, int unitType, RpgTileGridScene* gameScene);
    TownsPerson(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY);

    //methods
    void createAnimations();

private:
    void init();
    void init(RpgTileGridScene* gameScene);
};

