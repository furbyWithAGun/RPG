#include "Item.h"

int uniqueItemId = 0;

Item::Item()
{
    init();
}

Item::Item(SaveObject saveObject)
{
    init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case ITEM_ID:
            id = stoi(saveObject.attributes[i].valueString);
            if (id > uniqueItemId) {
                uniqueItemId = id;
            }
            else {
                id = getUniqueItemId();
            }
            break;
        case ITEM_WEIGHT:
            weight = stoi(saveObject.attributes[i].valueString);
            break;
        case ITEM_TEXTURE_KEY:
            textureKey = stoi(saveObject.attributes[i].valueString);
            break;
        case ITEM_NAME:
            name = saveObject.attributes[i].valueString;
            break;
        case ITEM_EQUIPABLE:
            equipable = stoi(saveObject.attributes[i].valueString);
            break;
        case ITEM_TYPE:
            type = stoi(saveObject.attributes[i].valueString);
            break;
        case ITEM_VALUE:
            value = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
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

std::string Item::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_ITEM) + "\n";
    }
    saveString += getAttributeString(getUniqueId(), ITEM_ID, id);
    saveString += getAttributeString(getUniqueId(), ITEM_WEIGHT, weight);
    saveString += getAttributeString(getUniqueId(), ITEM_TEXTURE_KEY, textureKey);
    saveString += getAttributeString(getUniqueId(), ITEM_NAME, name);
    saveString += getAttributeString(getUniqueId(), ITEM_EQUIPABLE, equipable);
    saveString += getAttributeString(getUniqueId(), ITEM_TYPE, type);
    saveString += getAttributeString(getUniqueId(), ITEM_VALUE, value);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_ITEM) + "\n";
    }
    return saveString;
}

void Item::init()
{
    id = -1;
    weight = 0;
    name = "";
    textureKey = -1;
    equipable = false;
    type = ITEM_TYPE_UNKNOWN;
    value = 1;
}

int getUniqueItemId()
{
    uniqueItemId++;
    return uniqueItemId;
}
