#pragma once
#include "AiUnit.h"

class TileGridScene;

class SkeletonKing : public AiUnit
{
public:
    //attributes

    //constructors
    SkeletonKing();
    SkeletonKing(SaveObject saveObject, RpgTileGridScene* gameScene);
    SkeletonKing(int zoneId, int unitType);
    SkeletonKing(int zoneId, int unitType, RpgTileGridScene* gameScene);
    SkeletonKing(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY);

    //methods
    void createAnimations() override;
    void setDropTable() override;
    void death() override;

private:
    void init();
    void init(RpgTileGridScene* gameScene);
};

