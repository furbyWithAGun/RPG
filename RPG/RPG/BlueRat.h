#pragma once
#include "AiUnit.h"

class RpgTileGridScene;

class BlueRat : public AiUnit
{
public:
    //attributes

    //constructors
    BlueRat();
    BlueRat(SaveObject saveObject, RpgTileGridScene* gameScene);
    BlueRat(int zoneId, int unitType);
    BlueRat(int zoneId, int unitType, RpgTileGridScene* gameScene);
    BlueRat(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY);

    //methods
    void createAnimations() override;
    void setDropTable() override;

private:
    void init();
    void init(RpgTileGridScene* gameScene);
};

