#pragma once
#include "AiUnit.h"

class TileGridScene;

class BlueRat : public AiUnit
{
public:
    //attributes

    //constructors
    BlueRat();
    BlueRat(int zoneId, int unitType);
    BlueRat(int zoneId, int unitType, TileGridScene* gameScene);
    BlueRat(int zoneId, int unitType, TileGridScene* gameScene, int startX, int startY);

    //methods
    void createAnimations();
    void setDropTable() override;

private:
    void init();
    void init(TileGridScene* gameScene);
};

