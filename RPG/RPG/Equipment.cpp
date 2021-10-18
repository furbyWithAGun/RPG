#include "Equipment.h"

Equipment::Equipment() : Item()
{
    init();
}

Equipment::Equipment(int itemType) : Item(itemType)
{
    init();
}

void Equipment::init()
{
    slot = -1;
    equipable = true;
}
