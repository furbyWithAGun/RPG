#include "Attack.h"
#include "RpgUnit.h"

Attack::Attack() {
    init();
}

Attack::Attack(int newType, RpgUnit* newOwningUnit){
    init();
    type = newType;
    owningUnit = newOwningUnit;
}

void Attack::init() {
    range = 1;
    damage = 1;
    cooldown = 1;
    attackTime = 1;
    cooldownTimeLeft = 0;
    attackDelay = 0;
    type = MELEE;
    owningUnit = NULL;
}

bool Attack::startAttack(int x, int y) {
    if (cooldownTimeLeft <= 0) {
        cooldownTimeLeft = cooldown;
        return true;
    }
    return false;
}

void Attack::update() {
    if (cooldown - cooldownTimeLeft == attackDelay) {
        processAttack();
    }
    if (cooldown > 0)
    {
        cooldownTimeLeft -= 1;
    }
}