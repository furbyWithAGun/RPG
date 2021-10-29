#pragma once
#include <string>
#include "RpgGameConstants.h"
#include "SaveObject.h"

enum ITEM_SAVE_ATTRIBUTES {
    ITEM_ID,
    ITEM_WEIGHT,
    ITEM_TEXTURE_KEY,
    ITEM_NAME,
    ITEM_EQUIPABLE,
    ITEM_TYPE,
    ITEM_VALUE,
    ITEM_STACKABLE,
    ITEM_STACK_SIZE,
    NUM_ITEM_ATTRIBUTES
};

class Item
{
public:
    //attributes
    int id;
    int weight;
    int textureKey;
    std::string name;
    bool equipable;
    int type;
    int value;
    bool stackable;
    int stackSize;

    //constructors
    Item();
    Item(SaveObject saveObject);
    Item(int itemType);
    Item(const Item& oldItem);

    //deconstructor
    virtual ~Item() = default;

    //methods
    virtual std::string toSaveString(bool withHeaderAndFooter = true);

private:
    //methods
    void init();
};

int getUniqueItemId();