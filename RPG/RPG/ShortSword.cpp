#include "ShortSword.h"

ShortSword::ShortSword() : Weapon()
{
    init();
}

void ShortSword::init()
{
    name = "Short Sword";
    textureKey = ITEM_SHORT_SWORD;
    minDamage = 4;
    maxDamage = 10;
    value = 200;
}
