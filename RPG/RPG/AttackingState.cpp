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
        //if (unit->movingUp) {
        //    //unit->startMovement(UP);
        //    return UNIT_MOVING;
        //}
        //else if (unit->movingDown) {
        //    //unit->startMovement(DOWN);
        //    return UNIT_MOVING;
        //}
        //else if (unit->movingRight) {
        //    //unit->startMovement(RIGHT);
        //    return UNIT_MOVING;
        //}
        //else if (unit->movingLeft) {
        //    //unit->startMovement(LEFT);
        //    return UNIT_MOVING;
        //}
        //else {
        //    return UNIT_IDLE;
        //}
        return UNIT_IDLE;
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

void AttackingState::updateAnimation()
{
    switch (unit->directionFacing) {
    case UP:
        //unit->playAnimation(ATTACK_UP);
        unit->setAnimation(IDLE_UP);
        break;
    case DOWN:
        //unit->playAnimation(ATTACK_DOWN);
        unit->setAnimation(IDLE_DOWN);
        break;
    case RIGHT:
        //unit->playAnimation(ATTACK_RIGHT);
        unit->setAnimation(IDLE_RIGHT);
        break;
    case LEFT:
        //unit->playAnimation(ATTACK_LEFT);
        unit->setAnimation(IDLE_LEFT);
        break;
    case UP_RIGHT:
        //unit->playAnimation(ATTACK_UP_RIGHT);
        unit->setAnimation(IDLE_UP_RIGHT);
        break;
    case UP_LEFT:
        //unit->playAnimation(ATTACK_UP_LEFT);
        unit->setAnimation(IDLE_UP_LEFT);
        break;
    case DOWN_RIGHT:
        //unit->playAnimation(ATTACK_DOWN_RIGHT);
        unit->setAnimation(IDLE_DOWN_RIGHT);
        break;
    case DOWN_LEFT:
        //unit->playAnimation(ATTACK_DOWN_LEFT);
        unit->setAnimation(IDLE_DOWN_LEFT);
        break;
    default:
        //unit->playAnimation(ATTACK_DOWN);
        unit->setAnimation(IDLE_DOWN);
        break;
    }
}
