#pragma once
#include "AiUnit.h"
class TownsPerson : public AiUnit
{
public:
    //attributes

    //constructors
    TownsPerson();
    TownsPerson(SaveObject saveObject, RpgTileGridScene* gameScene);
    TownsPerson(int zoneId, int unitType);
    TownsPerson(int zoneId, int unitType, RpgTileGridScene* gameScene);
    TownsPerson(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY);

    //methods
    void createAnimations() override;

private:
    void init();
    void init(RpgTileGridScene* gameScene);
};

