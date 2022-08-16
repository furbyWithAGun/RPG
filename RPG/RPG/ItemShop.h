#pragma once
#include "Building.h"
#include "RpgGameConstants.h"

class Item;
class RpgTown;
class ItemShop : public Building
{
public:
    //attributes
    std::vector<Item*> itemsForSale;

    //constructors
    ItemShop();
    ItemShop(SaveObject saveObject);
    ItemShop(int newWidth, int newHeight);
    ItemShop(std::vector< std::vector<BuildingTile*> > newTileMap);
    ItemShop(int entranceDirection);

    //methods
    int onActionAssignedUnit(RpgUnit* unit) override;
    void setItemsForSale(RpgTown* town);
    //void setItemsForSale(std::vector<Item*> newItemsForSale);

private:
    void init();
    void clearItemsForSale();
};

