#include "BasicMeleeAttack.h"
#include "RpgUnit.h"
#include "RpgTileGridScene.h"

const int BASIC_MELEE_ATTACK_BASE_DMG = 1;

BasicMeleeAttack::BasicMeleeAttack() : Attack() {
    init();
}

BasicMeleeAttack::BasicMeleeAttack(int newType, RpgUnit* newOwningUnit) : Attack(newType, newOwningUnit){
    init();
}

void BasicMeleeAttack::init() {
    cooldown = 10;
    attackTime = 10;
    cooldownTimeLeft = 0;
    attackDelay = 0;
}

int BasicMeleeAttack::damageDealt()
{
    Weapon* weapon = owningUnit->getEquippedWeapon();
    //return owningUnit->scene->engine->randomInt(1, BASIC_MELEE_ATTACK_BASE_DMG * owningUnit->str + 1);
    return owningUnit->scene->engine->randomInt(weapon->minDamage + (owningUnit->getAttributeLevel(UNIT_STAT_STR) + 1) / 3, weapon->maxDamage + (owningUnit->getAttributeLevel(UNIT_STAT_STR) + 1) * 0.8);
}

bool BasicMeleeAttack::startAttack() {
    if (Attack::startAttack()) {
        switch (owningUnit->directionFacing)
        {
        case UP_LEFT:
            owningUnit->playAnimation(ATTACK_UP_LEFT, attackTime);
            owningUnit->setAnimation(IDLE_UP_LEFT);
            break;
        case UP:
            owningUnit->playAnimation(ATTACK_UP, attackTime);
            owningUnit->setAnimation(IDLE_UP);
            break;
        case UP_RIGHT:
            owningUnit->playAnimation(ATTACK_UP_RIGHT, attackTime);
            owningUnit->setAnimation(IDLE_UP_RIGHT);
            break;
        case RIGHT:
            owningUnit->playAnimation(ATTACK_RIGHT, attackTime);
            owningUnit->setAnimation(IDLE_RIGHT);
            break;
        case DOWN_RIGHT:
            owningUnit->playAnimation(ATTACK_DOWN_RIGHT, attackTime);
            owningUnit->setAnimation(IDLE_DOWN_RIGHT);
            break;
        case DOWN:
            owningUnit->playAnimation(ATTACK_DOWN, attackTime);
            owningUnit->setAnimation(IDLE_DOWN);
            break;
        case DOWN_LEFT:
            owningUnit->playAnimation(ATTACK_DOWN_LEFT, attackTime);
            owningUnit->setAnimation(IDLE_DOWN_LEFT);
            break;
        case LEFT:
            owningUnit->playAnimation(ATTACK_LEFT, attackTime);
            owningUnit->setAnimation(IDLE_LEFT);
            break;
        default:
            break;
        }
        return true;
    }
    return false;
}


void BasicMeleeAttack::processHit(RpgUnit* targetUnit) {
    if (owningUnit->scene->getTeamStatus(owningUnit->team, targetUnit->team) == ALLY)
    {
        return;
    }
    if (owningUnit->scene->engine->getProbFromSigmoid(owningUnit->getAttributeLevel(UNIT_STAT_DEX) * 2, targetUnit->getAttributeLevel(UNIT_STAT_AGI)) > owningUnit->scene->engine->randomDouble())
    {
        int damage = this->damageDealt();
        targetUnit->assignDamage(owningUnit,damage);
    }
    else if (owningUnit->zone == owningUnit->scene->currentZone->id) {
        owningUnit->scene->addCombatMessage("MISS", targetUnit->tileLocation->x, targetUnit->tileLocation->y);
    }
}

void BasicMeleeAttack::processHit(DooDad* targetDooDad) {
    if (targetDooDad->canBeDamaged)
    {
        int damage = this->damageDealt();
        targetDooDad->assignDamage(owningUnit, damage);
        if (owningUnit->zone == owningUnit->scene->currentZone->id)
        {
            owningUnit->scene->addCombatMessage(std::to_string(damage), SDL_Color{ 255, 0, 0, 0 }, targetDooDad->tileCoords[0], targetDooDad->tileCoords[1]);
        }
    }
}

void BasicMeleeAttack::processAttack() {
    int attackTargetLocation[2];
    RpgUnit* targetUnit;
    owningUnit->getLocationUnitDestinationIsFacing(attackTargetLocation);
    targetUnit = (RpgUnit*)owningUnit->scene->getUnitAtLocation(owningUnit->zone, attackTargetLocation[0], attackTargetLocation[1]);
    if (targetUnit != nullptr && targetUnit != owningUnit) {
        processHit(targetUnit);
        return;
    }
    DooDad* targetDooDad;
    targetDooDad = (DooDad*)owningUnit->scene->getDooDadAtLocation(owningUnit->scene->getZone(owningUnit->zone), attackTargetLocation[0], attackTargetLocation[1]);
    if (targetDooDad != nullptr) {
        processHit(targetDooDad);
    }
}
