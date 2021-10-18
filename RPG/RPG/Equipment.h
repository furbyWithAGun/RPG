#pragma once
#include "Item.h"
#include "RpgGameConstants.h"

class Unit;

class Equipment : public Item
{
public:
    //attributes
    int slot;

    //constructors
    Equipment();
    Equipment(int itemType);

    //methods
    virtual void statModifier(Unit* unit) {};

private:
    //methods
    void init();
};

