#include "FoodEffect.h"
#include "RpgUnit.h"

FoodEffect::FoodEffect() : UnitTempEffect()
{
    init();
}

FoodEffect::FoodEffect(Food* foodEaten) : UnitTempEffect()
{
    init();
    healthRegen = foodEaten->healthRegen;
    duration = foodEaten->healthRegenDurationInSeconds * RPG_GAME_TICKS_PER_SECOND;
    name = foodEaten->name;
    texture = foodEaten->textureKey;
}

FoodEffect::FoodEffect(SaveObject saveObject) : UnitTempEffect(saveObject)
{
    init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case FOOD_EFFECT_HEALTH_REGEN:
            healthRegen = stoi(saveObject.attributes[i].valueString);
            break;
        case FOOD_EFFECT_TEXTURE_KEY:
            texture = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
}

std::string FoodEffect::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_FOOD_EFFECT) + "\n";
    }
    saveString += UnitTempEffect::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), FOOD_EFFECT_HEALTH_REGEN, healthRegen);
    saveString += getAttributeString(getUniqueId(), FOOD_EFFECT_TEXTURE_KEY, texture);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_FOOD_EFFECT) + "\n";
    }
    return saveString;
}

void FoodEffect::init()
{
    healthRegen = 1;
    updateOnTick = RPG_GAME_TICKS_PER_SECOND;
    texture = -1;

    onUpdate = [this](RpgUnit* affectedUnit) {
        tick++;
        if (tick % updateOnTick == 0)
        {
            affectedUnit->changeHealth(healthRegen);
            if (affectedUnit->getHealth() > affectedUnit->getAttributeLevel(UNIT_STAT_MAX_HEALTH))
            {
                affectedUnit->setFullHealth();
            }
        }
    };
}
