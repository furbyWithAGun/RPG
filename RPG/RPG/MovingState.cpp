#include "MovingState.h"
#include "RpgUnit.h"
#include "RpgOverWorldScene.h"

//constructors
MovingState::MovingState() : UnitState() {

}

MovingState::MovingState(int newId, RpgUnit* controlledUnit) : UnitState(newId, controlledUnit) {
    unit = controlledUnit;
}

//public methods
int MovingState::update() {
    UnitState::update();
    //if (unit->updateMovement()) {
    if (unit->leftToMove > 0 || unit->movingUp || unit->movingDown || unit->movingLeft || unit->movingRight) {
        return id;
    }
    else if (unit->leftToMove <= 0 && unit->pathDirections.size() > 0) {
        unit->processPath();
        return id;
    }
    else {
        return UNIT_IDLE;
    }
}

int MovingState::handleInput(InputMessage* message) {
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
        unit->movingDown = false;
        unit->movingLeft = false;
        unit->movingRight = false;
        break;
    case START_MOVE_DOWN:
        unit->movingUp = false;
        unit->movingDown = true;
        unit->movingLeft = false;
        unit->movingRight = false;
        break;
    case START_MOVE_LEFT:
        unit->movingUp = false;
        unit->movingDown = false;
        unit->movingLeft = true;
        unit->movingRight = false;
        break;
    case START_MOVE_RIGHT:
        unit->movingUp = false;
        unit->movingDown = false;
        unit->movingLeft = false;
        unit->movingRight = true;
        break;
    case STOP_MOVE_UP:
        unit->movingUp = false;
        break;
    case STOP_MOVE_DOWN:
        unit->movingDown = false;
        break;
    case STOP_MOVE_LEFT:
        unit->movingLeft = false;
        break;
    case STOP_MOVE_RIGHT:
        unit->movingRight = false;
        break;
    default:
        break;
    }
    return id;
}

//protected methods
void MovingState::updateAnimation() {
    switch (unit->directionFacing) {
    case UP:
        unit->setAnimation(MOVE_UP);
        break;
    case DOWN:
        unit->setAnimation(MOVE_DOWN);
        break;
    case RIGHT:
        unit->setAnimation(MOVE_RIGHT);
        break;
    case LEFT:
        unit->setAnimation(MOVE_LEFT);
        break;
    default:
        unit->setAnimation(MOVE_DOWN);
        break;
    }
}
