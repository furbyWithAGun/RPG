#include "LinenBody.h"

LinenBody::LinenBody() : Armour()
{
    init();
}

void LinenBody::init()
{
    name = "Linen Shirt";
    textureKey = ITEM_LINEN_BODY;
    armour = 2;
    slot = BODY_SLOT;
    value = 100;
}
