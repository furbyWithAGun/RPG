#include "LongSword.h"

LongSword::LongSword() : Weapon()
{
    init();
}

void LongSword::init()
{
    name = "Long Sword";
    textureKey = TEXTURE_LONG_SWORD;
    minDamage = 3;
    maxDamage = 22;
    value = 800;
}

