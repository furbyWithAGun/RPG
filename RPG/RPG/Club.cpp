#include "Club.h"

Club::Club() : Weapon()
{
    init();
}

void Club::init()
{
    name = "Club";
    textureKey = ITEM_CLUB;
    minDamage = 2;
    maxDamage = 6;
    value = 75;
}
