#pragma once
#include "AiUnit.h"
class Soldier : public AiUnit
{
public:
    //attributes

    //constructors
    Soldier();
    Soldier(int zoneId, int unitType);
    Soldier(int zoneId, int unitType, RpgTileGridScene* gameScene);
    Soldier(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY);

    //methods
    void createAnimations();

private:
    void init();
    void init(RpgTileGridScene* gameScene);
};

