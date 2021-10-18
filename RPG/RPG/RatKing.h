#pragma once
#include "AiUnit.h"

class TileGridScene;

class RatKing : public AiUnit
{
public:
    //attributes

    //constructors
    RatKing();
    RatKing(int zoneId, int unitType);
    RatKing(int zoneId, int unitType, TileGridScene* gameScene);
    RatKing(int zoneId, int unitType, TileGridScene* gameScene, int startX, int startY);

    //methods
    void createAnimations();
    void setDropTable() override;

private:
    void init();
    void init(TileGridScene* gameScene);
};

