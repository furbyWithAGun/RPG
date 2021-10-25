#pragma once
#include "Equipment.h"

enum ARMOUR_SAVE_ATTRIBUTES {
    ARMOUR_ARMOUR_VALUE = NUM_EQUIPMENT_ATTRIBUTES
};

class Armour : public Equipment
{
public:
    //attributes
    int armour;

    //constructors
    Armour();
    Armour(SaveObject saveObject);

    //methods
    std::string toSaveString(bool withHeaderAndFooter = true) override;

private:
    //methods
    void init();
};

