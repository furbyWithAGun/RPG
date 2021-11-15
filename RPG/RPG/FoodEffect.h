#pragma once
#include "UnitTempEffect.h"
#include "Food.h"

    enum FOOD_EFFECT_EFFECT_SAVE_ATTRIBUTES {
    FOOD_EFFECT_HEALTH_REGEN = NUM_UNIT_TEMP_EFFECT_SAVE_ATTRIBUTES,
    FOOD_EFFECT_TEXTURE_KEY
};

class RpgUnit;

class FoodEffect : public UnitTempEffect
{
public:
    //attributes
    int healthRegen;
    int texture;

    std::function<void(RpgUnit* affectedUnit)> onStart = {};
    std::function<void(RpgUnit* affectedUnit)> onEnd = {};
    std::function<void(RpgUnit* affectedUnit)> onUpdate = {};

    //constructors
    FoodEffect();
    FoodEffect(Food* foodEaten);
    FoodEffect(SaveObject saveObject);

    //methods
    virtual std::string toSaveString(bool withHeaderAndFooter = true);

private:
    void init();
};