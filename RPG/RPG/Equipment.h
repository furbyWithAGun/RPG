#pragma once
#include "Item.h"
#include "RpgGameConstants.h"

class RpgUnit;

enum EQUIPMENT_SAVE_ATTRIBUTES {
    EQUIPMENT_SLOT = NUM_ITEM_ATTRIBUTES,
    NUM_EQUIPMENT_ATTRIBUTES
};


class Equipment : public Item
{
public:
    //attributes
    int slot;

    //constructors
    Equipment();
    Equipment(SaveObject saveObject);
    Equipment(int itemType);

    //methods
    virtual void onEquip(RpgUnit* unit) {};
    virtual void onUnequip(RpgUnit* unit) {};
    virtual std::string toSaveString(bool withHeaderAndFooter = true) override;

private:
    //methods
    void init();
};

