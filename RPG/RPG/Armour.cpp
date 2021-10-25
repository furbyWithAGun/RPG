#include "Armour.h"

Armour::Armour() : Equipment(ARMOUR)
{
    init();
}

Armour::Armour(SaveObject saveObject) : Equipment(saveObject)
{
    init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case ARMOUR_ARMOUR_VALUE:
            armour = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
}

std::string Armour::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_ARMOUR) + "\n";
    }
    saveString += Equipment::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), ARMOUR_ARMOUR_VALUE, armour);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_ARMOUR) + "\n";
    }
    return saveString;
}

void Armour::init()
{
    armour = 1;
}
