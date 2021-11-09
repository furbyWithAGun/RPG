#pragma once
#include "AiUnit.h"
    class RpgTileGridScene;

class Skeleton : public AiUnit
{
public:
    //attributes

    //constructors
    Skeleton();
    Skeleton(SaveObject saveObject, RpgTileGridScene* gameScene);
    Skeleton(int zoneId, int unitType);
    Skeleton(int zoneId, int unitType, RpgTileGridScene* gameScene);
    Skeleton(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY);

    //methods
    void createAnimations() override;
    void setDropTable() override;

private:
    void init();
    void init(RpgTileGridScene* gameScene);
};

