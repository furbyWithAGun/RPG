#include "Weapon.h"

Weapon::Weapon() : Equipment(WEAPON)
{
    init();
}

Weapon::Weapon(SaveObject saveObject) : Equipment(saveObject)
{
    init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case WEAPON_MIN_DAMAGE:
            minDamage = stoi(saveObject.attributes[i].valueString);
            break;
        case WEAPON_MAX_DAMAGE:
            maxDamage = stoi(saveObject.attributes[i].valueString);
            break;
        case WEAPON_TWO_HANDED:
            twoHanded = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
}

std::string Weapon::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_WEAPON) + "\n";
    }
    saveString += Equipment::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), WEAPON_MIN_DAMAGE, minDamage);
    saveString += getAttributeString(getUniqueId(), WEAPON_MAX_DAMAGE, maxDamage);
    saveString += getAttributeString(getUniqueId(), WEAPON_TWO_HANDED, twoHanded);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_WEAPON) + "\n";
    }
    return saveString;
}

void Weapon::init()
{
    minDamage = 1;
    maxDamage = 2;
    twoHanded = false;
    slot = LEFT_HAND;
    weaponClass = SWORD;
}
