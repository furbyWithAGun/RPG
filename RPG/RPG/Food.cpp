#include "Food.h"

Food::Food() : Item(FOOD)
{
    init();
}

Food::Food(SaveObject saveObject) : Item(saveObject)
{
    init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case FOOD_HUNGER_GAIN:
            hungerGain = stoi(saveObject.attributes[i].valueString);
            break;
        case FOOD_HEALTH_REGEN:
            healthRegen = stoi(saveObject.attributes[i].valueString);
            break;
        case FOOD_HEALTH_REGEN_DURATION:
            healthRegenDuration = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
}

Food::Food(int itemType) : Item(itemType)
{
    init();
}

std::string Food::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_EQUIPMENT) + "\n";
    }
    saveString += Item::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), FOOD_HUNGER_GAIN, hungerGain);
    saveString += getAttributeString(getUniqueId(), FOOD_HEALTH_REGEN, healthRegen);
    saveString += getAttributeString(getUniqueId(), FOOD_HEALTH_REGEN_DURATION, healthRegenDuration);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_EQUIPMENT) + "\n";
    }
    return saveString;
}

void Food::init()
{
}
