#pragma once
#include <string>
#include "RpgGameConstants.h"

class Item
{
public:
    //attributes
    int weight;
    int textureKey;
    std::string name;
    bool equipable;
    int type;
    int value;

    //constructors
    Item();
    Item(int itemType);
    Item(const Item& oldItem);

    //deconstructor
    virtual ~Item() = default;

private:
    //methods
    void init();
};

