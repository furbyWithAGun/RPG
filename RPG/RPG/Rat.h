#pragma once
#include "AiUnit.h"

class TileGridScene;

class Rat : public AiUnit
{
public:
    //attributes

    //constructors
    Rat();
    Rat(int zoneId, int unitType);
    Rat(int zoneId, int unitType, RpgTileGridScene* gameScene);
    Rat(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY);

    //methods
    void createAnimations();
    void setDropTable() override;

private:
    void init();
    void init(RpgTileGridScene* gameScene);
};

