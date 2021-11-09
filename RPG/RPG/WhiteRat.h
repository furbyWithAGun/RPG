#pragma once
#include "AiUnit.h"

class RpgTileGridScene;

class WhiteRat : public AiUnit
{
public:
    //attributes

    //constructors
    WhiteRat();
    WhiteRat(SaveObject saveObject, RpgTileGridScene* gameScene);
    WhiteRat(int zoneId, int unitType);
    WhiteRat(int zoneId, int unitType, RpgTileGridScene* gameScene);
    WhiteRat(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY);

    //methods
    void createAnimations() override;
    void setDropTable() override;

private:
    void init();
    void init(RpgTileGridScene* gameScene);
};

