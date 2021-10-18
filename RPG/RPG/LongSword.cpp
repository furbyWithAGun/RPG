#include "LongSword.h"

LongSword::LongSword() : Weapon()
{
    init();
}

void LongSword::init()
{
    name = "Long Sword";
    textureKey = ITEM_LONG_SWORD;
    minDamage = 3;
    maxDamage = 22;
    value = 800;
}

