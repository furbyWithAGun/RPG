#include "IdleState.h"
#include "Unit.h"
#include "RpgOverWorldScene.h"

//constructors
IdleState::IdleState() : UnitState() {

}

IdleState::IdleState(int newId, Unit* controlledUnit) : UnitState(newId, controlledUnit) {

}

//public methods
int IdleState::update() {
    UnitState::update();
    if (unit->leftToMove > 0 || unit->movingUp || unit->movingDown || unit->movingLeft || unit->movingRight) {
        return UNIT_MOVING;
    }
    if (unit->leftToMove <= 0 && unit->pathDirections.size() > 0)
    {
        unit->processPath();
        return UNIT_MOVING;
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
