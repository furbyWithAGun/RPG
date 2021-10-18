#pragma once
#include "Equipment.h"
class Armour : public Equipment
{
public:
    //attributes
    int armour;

    //constructors
    Armour();

private:
    //methods
    void init();
};

