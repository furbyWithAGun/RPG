#pragma once
#include "Equipment.h"

enum WEAPON_SAVE_ATTRIBUTES {
    WEAPON_MIN_DAMAGE = NUM_EQUIPMENT_ATTRIBUTES,
    WEAPON_MAX_DAMAGE,
    WEAPON_TWO_HANDED
};

class Weapon : public Equipment
{
public:
    //attributes
    int minDamage;
    int maxDamage;
    int weaponClass;
    bool twoHanded;

    //constructors
    Weapon();
    Weapon(SaveObject saveObject);

    //methods
    std::string toSaveString(bool withHeaderAndFooter = true) override;

private:
    //methods
    void init();
};

