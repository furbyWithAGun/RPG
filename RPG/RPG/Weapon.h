#pragma once
#include "Equipment.h"

class Weapon : public Equipment
{
public:
    //attributes
    int minDamage;
    int maxDamage;
    bool twoHanded;

    //constructors
    Weapon();

private:
    //methods
    void init();
};

