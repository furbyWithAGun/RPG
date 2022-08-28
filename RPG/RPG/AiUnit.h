#pragma once
#include "RpgUnit.h"

class RpgOverWorldScene;


enum AI_UNIT_SAVE_ATTRIBUTES {
    AI_UNIT_IS_HOSTILE = 2000,
    AI_UNIT_DOES_RANDOM_MOVEMENT,
    AI_UNIT_CHANCE_TO_MOVE_EACH_TICK,
    NUM_AI_UNIT_ATTRIBUTES
};

class AiUnit : public RpgUnit
{
public:
    //attributes
    bool isHostile;
    bool doesRandomMovement;

    //constructor
    AiUnit();
    AiUnit(SaveObject saveObject, RpgTileGridScene* gameScene);
    AiUnit(int zoneId, int unitType);
    AiUnit(int zoneId, int unitType, RpgTileGridScene* gameScene);
    AiUnit(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY);

    //methods
    void update() override;
    virtual std::string toSaveString(bool withHeaderAndFooter = true) override;
    void randomMovement();
    bool attackNearbyUnit();

private:
    //attribues
    double chanceToMoveEachTick;
    int checkToAttackTick;
    //int checkToAttackRate;

    //methods
    bool meleeAttackUnitInDirection(int direction);
    void init();
};

