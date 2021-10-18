#pragma once
#include "Building.h"
#include "RpgGameConstants.h"

class Item;
class ItemShop : public Building
{
public:
    //attributes
    std::vector<Item*> itemsForSale;

    //constructors
    ItemShop();
    ItemShop(int newWidth, int newHeight);
    ItemShop(std::vector< std::vector<BuildingTile*> > newTileMap);

    //methods
    int onActionAssignedUnit(Unit* unit) override;
    void setItemsForSale(std::vector<Item*> newItemsForSale);
};

