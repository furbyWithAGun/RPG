#pragma once
#include "Item.h"
#include "RpgGameConstants.h"

enum FOOD_SAVE_ATTRIBUTES {
    FOOD_HUNGER_GAIN = NUM_ITEM_ATTRIBUTES,
    FOOD_HEALTH_REGEN,
    FOOD_HEALTH_REGEN_DURATION,
    NUM_FOOD_ATTRIBUTES
};


class Food : public Item
{
public:
    //attributes
    int hungerGain;
    int healthRegen;
    int healthRegenDuration;

    //constructors
    Food();
    Food(SaveObject saveObject);
    Food(int itemType);

    //methods
    virtual std::string toSaveString(bool withHeaderAndFooter = true) override;

private:
    //methods
    void init();
};
