#include "Mace.h"

Mace::Mace() : Weapon()
{
    init();
}

void Mace::init()
{
    name = "Mace";
    textureKey = ITEM_MACE;
    minDamage = 4;
    maxDamage = 14;
    value = 500;
}

