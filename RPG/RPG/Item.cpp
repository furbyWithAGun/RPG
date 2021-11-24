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
        case ITEM_GENERAL_TYPE:
            generalType = stoi(saveObject.attributes[i].valueString);
            break;
        case ITEM_VALUE:
            value = stoi(saveObject.attributes[i].valueString);
            break;
        case ITEM_STACKABLE:
            stackable = stoi(saveObject.attributes[i].valueString);
            break;
        case ITEM_STACK_SIZE:
            stackSize = stoi(saveObject.attributes[i].valueString);
            break;
        case ITEM_SPECIFIC_TYPE:
            specificType = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
}

Item::Item(int newGeneralType)
{
    init();
    generalType = newGeneralType;
}

Item::Item(const Item& oldItem)
{
    init();
    weight = oldItem.weight;
    textureKey = oldItem.textureKey;
    name = oldItem.name;
    equipable = oldItem.equipable;
    generalType = oldItem.generalType;
    specificType = oldItem.specificType;
    value = oldItem.value;
    stackable = oldItem.stackable;
    stackSize = oldItem.stackSize;
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
    saveString += getAttributeString(getUniqueId(), ITEM_GENERAL_TYPE, generalType);
    saveString += getAttributeString(getUniqueId(), ITEM_VALUE, value);
    saveString += getAttributeString(getUniqueId(), ITEM_STACKABLE, stackable);
    saveString += getAttributeString(getUniqueId(), ITEM_STACK_SIZE, stackSize);
    saveString += getAttributeString(getUniqueId(), ITEM_SPECIFIC_TYPE, specificType);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_ITEM) + "\n";
    }
    return saveString;
}

void Item::init()
{
    id = -1;
    specificType = -1;
    weight = 0;
    name = "";
    textureKey = -1;
    equipable = false;
    generalType = ITEM_TYPE_UNKNOWN;
    value = 1;
    stackSize = 1;
    stackable = false;
}

int getUniqueItemId()
{
    uniqueItemId++;
    return uniqueItemId;
}
