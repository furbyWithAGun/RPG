#include "LinenPants.h"

LinenPants::LinenPants() : Armour()
{
    init();
}

void LinenPants::init()
{
    name = "Linen Pants";
    textureKey = ITEM_LINEN_PANTS;
    armour = 2;
    slot = LEGS_SLOT;
    value = 100;
}
