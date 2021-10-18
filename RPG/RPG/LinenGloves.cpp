#include "LinenGloves.h"

LinenGloves::LinenGloves() : Armour()
{
    init();
}

void LinenGloves::init()
{
    name = "Linen Gloves";
    textureKey = ITEM_LINEN_GLOVES;
    armour = 2;
    slot = HANDS_SLOT;
    value = 100;
}
