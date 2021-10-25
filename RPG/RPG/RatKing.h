#pragma once
#include "AiUnit.h"

class TileGridScene;

class RatKing : public AiUnit
{
public:
    //attributes

    //constructors
    RatKing();
    RatKing(SaveObject saveObject, RpgTileGridScene* gameScene);
    RatKing(int zoneId, int unitType);
    RatKing(int zoneId, int unitType, RpgTileGridScene* gameScene);
    RatKing(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY);

    //methods
    void createAnimations() override;
    void setDropTable() override;

private:
    void init();
    void init(RpgTileGridScene* gameScene);
};

