#include "UnitTempEffect.h"

UnitTempEffect::UnitTempEffect()
{
    init();
}

UnitTempEffect::UnitTempEffect(SaveObject saveObject)
{
    init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case UNIT_TEMP_EFFECT_DURATION:
            duration = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_TEMP_EFFECT_TICK:
            tick = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_TEMP_EFFECT_TYPE:
            type = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_TEMP_EFFECT_UPDATE_ON_TICK:
            updateOnTick = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_TEMP_EFFECT_NAME:
            name = saveObject.attributes[i].valueString;
            break;
        default:
            break;
        }
    }
}

std::string UnitTempEffect::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_UNIT_TEMP_EFFECT) + "\n";
    }
    saveString += getAttributeString(getUniqueId(), UNIT_TEMP_EFFECT_DURATION, duration);
    saveString += getAttributeString(getUniqueId(), UNIT_TEMP_EFFECT_TICK, tick);
    saveString += getAttributeString(getUniqueId(), UNIT_TEMP_EFFECT_TYPE, type);
    saveString += getAttributeString(getUniqueId(), UNIT_TEMP_EFFECT_UPDATE_ON_TICK, updateOnTick);
    saveString += getAttributeString(getUniqueId(), UNIT_TEMP_EFFECT_NAME, name);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_UNIT_TEMP_EFFECT) + "\n";
    }
    return saveString;
}

void UnitTempEffect::init()
{
    duration = 1;
    tick = 0;
    type = -1;
    updateOnTick = 1;
    name = "";
}
