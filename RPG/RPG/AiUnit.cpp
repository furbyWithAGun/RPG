#include "AiUnit.h"
#include "RpgOverWorldScene.h"

//constants
const double RANDOM_MOVE_CHANCE = 0.005;

//constructors
AiUnit::AiUnit() : RpgUnit() {
    init();
}

AiUnit::AiUnit(int zoneId, int unitType) : RpgUnit(zoneId, unitType) {
    init();
}

AiUnit::AiUnit(int zoneId, int unitType, RpgTileGridScene* gameScene) : RpgUnit(zoneId, unitType, gameScene) {
    init();
}

AiUnit::AiUnit(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY) : RpgUnit(zoneId, unitType, gameScene, startX, startY) {
    init();
}

void AiUnit::init() {
    isStatic = false;
    isHostile = false;
    chanceToMoveEachTick = RANDOM_MOVE_CHANCE;
    doesRandomMovement = true;
}

void AiUnit::update() {
    updateAggro();
    if (!attackNearbyUnit() && doesRandomMovement && pathDirections.size() <= 0)
    {
        randomMovement();
    }
    RpgUnit::update();
}


void AiUnit::randomMovement() {
    if (leftToMove == 0 && scene->engine->randomDouble() <= chanceToMoveEachTick)
    {
        int randomDirection = scene->engine->randomInt(UP, RIGHT);
        switch (randomDirection)
        {
        case UP:
            handleInput(&InputMessage(START_MOVE_UP));
            handleInput(&InputMessage(STOP_MOVE_UP));
            break;
        case DOWN:
            handleInput(&InputMessage(START_MOVE_DOWN));
            handleInput(&InputMessage(STOP_MOVE_DOWN));
            break;
        case LEFT:
            handleInput(&InputMessage(START_MOVE_LEFT));
            handleInput(&InputMessage(STOP_MOVE_LEFT));
            break;
        case RIGHT:
            handleInput(&InputMessage(START_MOVE_RIGHT));
            handleInput(&InputMessage(STOP_MOVE_RIGHT));
            break;
        default:
            break;
        }
    }
}

bool AiUnit::attackNearbyUnit() {
    for (size_t i = 0; i < NUM_DIRECTIONS; i++)
    {
        if (meleeAttackUnitInDirection(i)) {
            return true;
        }
    }
    return false;
}

bool AiUnit::meleeAttackUnitInDirection(int direction)
{
    Unit* targetUnit;
    int x, y, coords[2];
    switch (direction)
    {
    case UP_LEFT:
        x = tileLocation->x - 1;
        y = tileLocation->y - 1;
        break;
    case UP:
        x = tileLocation->x;
        y = tileLocation->y - 1;
        break;
    case UP_RIGHT:
        x = tileLocation->x + 1;
        y = tileLocation->y - 1;
        break;
    case RIGHT:
        x = tileLocation->x + 1;
        y = tileLocation->y;
        break;
    case DOWN_RIGHT:
        x = tileLocation->x + 1;
        y = tileLocation->y + 1;
        break;
    case DOWN:
        x = tileLocation->x;
        y = tileLocation->y + 1;
        break;
    case DOWN_LEFT:
        x = tileLocation->x - 1;
        y = tileLocation->y + 1;
        break;
    case LEFT:
        x = tileLocation->x - 1;
        y = tileLocation->y;
        break;
    default:
        break;
    }
    targetUnit = scene->getUnitAtLocation(zone, x, y);
    //if (targetUnit != NULL && targetUnit->type == PLAYER)
    if (targetUnit != NULL && getTeamStatus((RpgUnit*)targetUnit) == ENEMY)
    {
        scene->coordsFromTileIndex(x, y, coords);
        handleInput(&InputMessage(PERFORM_MAIN_ATTACK, coords[0], coords[1]));
        return true;
    }
    return false;
}
