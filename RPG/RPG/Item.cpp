#include "Item.h"

Item::Item()
{
    init();
}

Item::Item(int itemType)
{
    init();
    type = itemType;
}

Item::Item(const Item& oldItem)
{
    init();
    weight = oldItem.weight;
    textureKey = oldItem.textureKey;
    name = oldItem.name;
    equipable = oldItem.equipable;
    type = oldItem.type;
    value = oldItem.value;
}

void Item::init()
{
    weight = 0;
    name = "";
    textureKey = -1;
    equipable = false;
    type = ITEM_TYPE_UNKNOWN;
    value = 1;
}
