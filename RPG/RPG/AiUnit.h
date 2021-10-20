#pragma once
#include "RpgUnit.h"

class RpgOverWorldScene;

class AiUnit : public RpgUnit
{
public:
    //attributes
    bool isHostile;
    bool doesRandomMovement;

    //constructor
    AiUnit();
    AiUnit(int zoneId, int unitType);
    AiUnit(int zoneId, int unitType, RpgTileGridScene* gameScene);
    AiUnit(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY);

    //methods
    void update() override;

private:
    //attribues
    double chanceToMoveEachTick;

    //methods
    void randomMovement();
    bool attackNearbyUnit();
    bool meleeAttackUnitInDirection(int direction);
    void init();
};

