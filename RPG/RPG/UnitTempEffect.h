#pragma once
#include <functional>
#include <string>
#include "SaveObject.h"
#include "RpgGameConstants.h"

enum UNIT_TEMP_EFFECT_SAVE_ATTRIBUTES {
    UNIT_TEMP_EFFECT_DURATION,
    UNIT_TEMP_EFFECT_TICK,
    UNIT_TEMP_EFFECT_TYPE,
    UNIT_TEMP_EFFECT_UPDATE_ON_TICK,
    UNIT_TEMP_EFFECT_NAME,
    NUM_UNIT_TEMP_EFFECT_SAVE_ATTRIBUTES
};

class RpgUnit;

class UnitTempEffect
{
public:
    //attributes
    int duration;
    int tick;
    int updateOnTick;
    int type;
    std::string name;

    std::function<void(RpgUnit* affectedUnit)> onStart = {};
    std::function<void(RpgUnit* affectedUnit)> onEnd = {};
    std::function<void(RpgUnit* affectedUnit)> onUpdate = {};

    //constructors
    UnitTempEffect();
    UnitTempEffect(SaveObject saveObject);

    //methods
    virtual std::string toSaveString(bool withHeaderAndFooter = true);

private:
    void init();
};

