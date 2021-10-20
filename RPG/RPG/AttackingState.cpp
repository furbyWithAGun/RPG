#include "AttackingState.h"
#include "MovingState.h"
#include "IdleState.h"
#include "RpgUnit.h"
#include "RpgOverWorldScene.h"

//constructors
AttackingState::AttackingState() : UnitState() {

}

AttackingState::AttackingState(int newId, RpgUnit* controlledUnit) : UnitState(newId, controlledUnit) {
    unit = controlledUnit;
}

//public methods
int AttackingState::update() {
    UnitState::update();
    if (unit->activeAttack->cooldown - unit->activeAttack->cooldownTimeLeft >= unit->activeAttack->attackTime) {
        if (unit->movingUp) {
            //unit->startMovement(UP);
            return UNIT_MOVING;
        }
        else if (unit->movingDown) {
            //unit->startMovement(DOWN);
            return UNIT_MOVING;
        }
        else if (unit->movingRight) {
            //unit->startMovement(RIGHT);
            return UNIT_MOVING;
        }
        else if (unit->movingLeft) {
            //unit->startMovement(LEFT);
            return UNIT_MOVING;
        }
        else {
            return UNIT_IDLE;
        }
    }
    //unit->updateMovement();
    return id;
}

int AttackingState::handleInput(InputMessage* message) {
    switch (message->id)
    {
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
