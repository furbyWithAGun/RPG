#include "LinenHat.h"

LinenHat::LinenHat() : Armour()
{
    init();
}

void LinenHat::init()
{
    name = "Linen Hat";
    textureKey = ITEM_LINEN_HAT;
    armour = 2;
    slot = HEAD_SLOT;
    value = 100;
}

