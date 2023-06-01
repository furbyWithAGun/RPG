#include "BasicRangedAttack.h"
#include "RpgUnit.h"
#include "RpgTileGridScene.h"

const int BASIC_MELEE_ATTACK_BASE_DMG = 1;

std::unordered_map<int, int> directionTextureMap = {
    {UP, TEXTURE_ARROW_UP},
    {DOWN, TEXTURE_ARROW_DOWN},
    {LEFT, TEXTURE_ARROW_LEFT},
    {RIGHT, TEXTURE_ARROW_RIGHT},
    {UP_RIGHT, TEXTURE_ARROW_UP_RIGHT},
    {UP_LEFT, TEXTURE_ARROW_UP_LEFT},
    {DOWN_RIGHT, TEXTURE_ARROW_DOWN_RIGHT},
    {DOWN_LEFT, TEXTURE_ARROW_DOWN_LEFT},
};

BasicRangedAttack::BasicRangedAttack() : Attack() {
    init();
}

BasicRangedAttack::BasicRangedAttack(int newType, RpgUnit* newOwningUnit) : Attack(newType, newOwningUnit) {
    init();
}

void BasicRangedAttack::init() {
    cooldown = 15;
    attackTime = 15;
    cooldownTimeLeft = 0;
    attackDelay = 0;
    xTarget = -1;
    yTarget = -1;
}

int BasicRangedAttack::damageDealt()
{
    Weapon* weapon = owningUnit->getEquippedWeapon();
    //return owningUnit->scene->engine->randomInt(1, BASIC_MELEE_ATTACK_BASE_DMG * owningUnit->str + 1);
    return owningUnit->scene->engine->randomInt(weapon->minDamage + (owningUnit->getAttributeLevel(UNIT_STAT_STR) + 1) / 3, weapon->maxDamage + (owningUnit->getAttributeLevel(UNIT_STAT_STR) + 1) * 0.8);
}

bool BasicRangedAttack::startAttack(int x, int y) {
    //if (Attack::startAttack(x, y) && owningUnit->mana >= 10) {
    if (Attack::startAttack(x, y)) {
        xTarget = x;
        yTarget = y;
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


void BasicRangedAttack::processHit(RpgUnit* targetUnit) {
    if (owningUnit->scene->getTeamStatus(owningUnit->team, targetUnit->team) == ALLY)
    {
        return;
    }
    if (owningUnit->scene->engine->getProbFromSigmoid(owningUnit->getAttributeLevel(UNIT_STAT_DEX) * 2, targetUnit->getAttributeLevel(UNIT_STAT_AGI)) > owningUnit->scene->engine->randomDouble())
    {
        int damage = this->damageDealt();
        targetUnit->assignDamage(owningUnit, damage);
    }
    else if (owningUnit->getZone() == owningUnit->scene->currentZone->id) {
        owningUnit->scene->addCombatMessage("MISS", targetUnit->tileLocation->x, targetUnit->tileLocation->y);
    }
}

void BasicRangedAttack::processHit(DooDad* targetDooDad) {
    if (targetDooDad->canBeDamaged)
    {
        int damage = this->damageDealt();
        targetDooDad->assignDamage(owningUnit, damage);
        if (owningUnit->getZone() == owningUnit->scene->currentZone->id)
        {
            owningUnit->scene->addCombatMessage(std::to_string(damage), SDL_Color{ 255, 0, 0, 0 }, targetDooDad->tileCoords[0], targetDooDad->tileCoords[1]);
        }
    }
}

void BasicRangedAttack::processAttack() {
    Weapon* arrows = (Weapon*)owningUnit->equippedItems[RIGHT_HAND];
    if (owningUnit->getEquippedWeapon()->weaponClass == BOW && arrows != nullptr && arrows->weaponClass == ARROW && arrows->stackSize > 0)
    //if (owningUnit->mana >= 0)
    {
        //owningUnit->mana -= 10;
        arrows->stackSize -= 1;
        if (arrows->stackSize <= 0)
        {
            owningUnit->equippedItems[RIGHT_HAND] = nullptr;
            delete arrows;
        }
        Projectile* newProjectile = new Projectile(owningUnit, directionTextureMap[owningUnit->getDirectionOfCoordsRelativeToUnit(xTarget, yTarget)]);
        newProjectile->setTarget(xTarget, yTarget);
        int dex = owningUnit->getAttributeLevel(UNIT_STAT_DEX);
        newProjectile->addOnCollide([this, newProjectile, dex](RpgUnit* collidedUnit) {
            if (newProjectile->active && collidedUnit != owningUnit)
            {
                //collidedUnit->scene->addCombatMessage("hit", SDL_Color{ 255, 0, 0, 0 }, collidedUnit->tileLocation->x, collidedUnit->tileLocation->y);
                if (newProjectile->getTeam() != collidedUnit->team)
                {
                    collidedUnit->assignDamage(owningUnit, collidedUnit->scene->engine->randomInt(1,5) + collidedUnit->scene->engine->randomInt(dex));
                    newProjectile->active = false;
                }
            }
            });
        ((RpgZone*)owningUnit->scene->getZone(owningUnit->getZone()))->addToProjectileVector(newProjectile);
    }
}
