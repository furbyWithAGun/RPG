#include "LinenBoots.h"
LinenBoots::LinenBoots() : Armour()
{
    init();
}

void LinenBoots::init()
{
    name = "Linen Boots";
    textureKey = ITEM_LINEN_BOOTS;
    armour = 2;
    slot = FEET_SLOT;
    value = 100;
}
