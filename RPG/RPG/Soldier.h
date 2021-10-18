#pragma once
#include "AiUnit.h"
class Soldier : public AiUnit
{
public:
    //attributes

    //constructors
    Soldier();
    Soldier(int zoneId, int unitType);
    Soldier(int zoneId, int unitType, TileGridScene* gameScene);
    Soldier(int zoneId, int unitType, TileGridScene* gameScene, int startX, int startY);

    //methods
    void createAnimations();

private:
    void init();
    void init(TileGridScene* gameScene);
};

