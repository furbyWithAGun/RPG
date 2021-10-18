#pragma once
#include "AiUnit.h"
class TownsPerson : public AiUnit
{
public:
    //attributes

    //constructors
    TownsPerson();
    TownsPerson(int zoneId, int unitType);
    TownsPerson(int zoneId, int unitType, TileGridScene* gameScene);
    TownsPerson(int zoneId, int unitType, TileGridScene* gameScene, int startX, int startY);

    //methods
    void createAnimations();

private:
    void init();
    void init(TileGridScene* gameScene);
};

