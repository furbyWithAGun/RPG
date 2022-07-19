#include "IdleState.h"
#include "RpgUnit.h"
#include "RpgOverWorldScene.h"

//constructors
IdleState::IdleState() : UnitState() {

}

IdleState::IdleState(int newId, RpgUnit* controlledUnit) : UnitState(newId, controlledUnit) {
    unit = controlledUnit;
}

//public methods
int IdleState::update() {
    UnitState::update();
    if (unit->leftToMove > 0 || unit->movingUp || unit->movingDown || unit->movingLeft || unit->movingRight) {
        return UNIT_MOVING;
    }
    if (unit->leftToMove <= 0 && unit->pathDirections.size() > 0)
    {
        if (unit->processPath()) {
            return UNIT_MOVING;
        }
        else {
            return id;
        }
    }
    return id;
}

int IdleState::handleInput(InputMessage* message) {
    switch (message->id)
    {
    case PERFORM_MAIN_ATTACK:
        unit->faceCoords(message->x, message->y);
        if (unit->performAttack(MAIN_ATTACK))
        {
            return UNIT_ATTACKING;
        }
        break;
    case USER_ACTION:
        RpgUnit* actionedUnit;
        actionedUnit = unit->scene->getUnitAtLocation(unit->zone, message->x, message->y);
        if (actionedUnit != nullptr)
        {
            if (actionedUnit->assignedToBuilding != nullptr)
            {
                actionedUnit->assignedToBuilding->onActionAssignedUnit(actionedUnit);
            }
        }
        DooDad* actionedDooDad;
        actionedDooDad = unit->scene->getZones()[unit->zone]->getDooDadAtLocation(message->x, message->y);
        if (actionedDooDad != nullptr)
        {
            actionedDooDad->actionOn(unit, OVERWORLD_USE);
        }
        break;
    case OVERWORLD_STRIKE:
        actionedDooDad = unit->scene->getZones()[unit->zone]->getDooDadAtLocation(message->x, message->y);
        if (actionedDooDad != nullptr && (std::abs(actionedDooDad->tileCoords[0] - unit->tileLocation->x) <= 1) && (std::abs(actionedDooDad->tileCoords[1] - unit->tileLocation->y) <= 1))
        {
            if (actionedDooDad->canBeDamaged)
            {
                double tileCoords[2];
                unit->scene->coordsFromTileIndex(message->x, message->y, tileCoords);
                unit->faceCoords(tileCoords[0], tileCoords[1]);
                if (unit->performAttack(MAIN_ATTACK))
                {
                    return UNIT_ATTACKING;
                }
                break;
            }
            actionedDooDad->actionOn(unit, OVERWORLD_STRIKE);
        }
        break;
    case PICK_UP_ITEM:
        if (unit->scene->currentZone->getItemsAtLocation(message->x, message->y).size() > 0 && (std::abs(message->x - unit->tileLocation->x) <= 1) && (std::abs(message->y - unit->tileLocation->y) <= 1)) {
            unit->scene->pickUpItemAtLocation(unit, message->x, message->y);
        }
        break;
    case START_MOVE_UP:
        unit->movingUp = true;
        unit->startMovement(UP);
        return UNIT_MOVING;
        break;
    case START_MOVE_DOWN:
        unit->movingDown = true;
        unit->startMovement(DOWN);
        return UNIT_MOVING;
        break;
    case START_MOVE_LEFT:
        unit->movingLeft = true;
        unit->startMovement(LEFT);
        return UNIT_MOVING;
        break;
    case START_MOVE_RIGHT:
        unit->movingRight = true;
        unit->startMovement(RIGHT);
        return UNIT_MOVING;
        break;
    default:
        break;
    }
    return id;
}

void IdleState::updateAnimation() {
    switch (unit->directionFacing) {
    case UP:
        unit->setAnimation(IDLE_UP);
        break;
    case DOWN:
        unit->setAnimation(IDLE_DOWN);
        break;
    case RIGHT:
        unit->setAnimation(IDLE_RIGHT);
        break;
    case LEFT:
        unit->setAnimation(IDLE_LEFT);
        break;
    case UP_RIGHT:
        unit->setAnimation(IDLE_UP_RIGHT);
        break;
    case UP_LEFT:
        unit->setAnimation(IDLE_UP_LEFT);
        break;
    case DOWN_RIGHT:
        unit->setAnimation(IDLE_DOWN_RIGHT);
        break;
    case DOWN_LEFT:
        unit->setAnimation(IDLE_DOWN_LEFT);
        break;
    default:
        unit->setAnimation(IDLE_DOWN);
        break;
    }
}
