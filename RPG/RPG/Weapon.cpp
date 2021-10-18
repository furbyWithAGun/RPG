#include "Weapon.h"

Weapon::Weapon() : Equipment(WEAPON)
{
    init();
}

void Weapon::init()
{
    minDamage = 1;
    maxDamage = 2;
    twoHanded = false;
    slot = LEFT_HAND;
}
