#include "AiUnit.h"
#include "RpgOverWorldScene.h"

//constants
const double RANDOM_MOVE_CHANCE = 0.005;

//constructors
AiUnit::AiUnit() : RpgUnit() {
    init();
}

AiUnit::AiUnit(SaveObject saveObject, RpgTileGridScene* gameScene) : RpgUnit(saveObject, gameScene)
{
    init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case AI_UNIT_IS_HOSTILE:
            isHostile = stoi(saveObject.attributes[i].valueString);
            break;
        case AI_UNIT_DOES_RANDOM_MOVEMENT:
            doesRandomMovement = stoi(saveObject.attributes[i].valueString);
            break;
        case AI_UNIT_CHANCE_TO_MOVE_EACH_TICK:
            chanceToMoveEachTick = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
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

std::string AiUnit::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_AI_UNIT) + "\n";
    }
    saveString += RpgUnit::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), AI_UNIT_IS_HOSTILE, isHostile);
    saveString += getAttributeString(getUniqueId(), AI_UNIT_DOES_RANDOM_MOVEMENT, doesRandomMovement);
    saveString += getAttributeString(getUniqueId(), AI_UNIT_CHANCE_TO_MOVE_EACH_TICK, chanceToMoveEachTick);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_AI_UNIT) + "\n";
    }
    return saveString;
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
