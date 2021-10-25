#include "Equipment.h"

Equipment::Equipment() : Item()
{
    init();
}

Equipment::Equipment(SaveObject saveObject) : Item(saveObject)
{
    init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case EQUIPMENT_SLOT:
            slot = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
}

Equipment::Equipment(int itemType) : Item(itemType)
{
    init();
}

std::string Equipment::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_EQUIPMENT) + "\n";
    }
    saveString += Item::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), EQUIPMENT_SLOT, slot);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_EQUIPMENT) + "\n";
    }
    return saveString;
}

void Equipment::init()
{
    slot = -1;
    equipable = true;
}
