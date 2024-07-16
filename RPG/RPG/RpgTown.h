#pragma once
#include <vector>
#include "Equipment.h"
#include "Food.h"
#include "Building.h"
#include "RpgZone.h"

class RpgTileGridScene;
class RpgZone;

enum RPG_TOWN_SAVE_ATTRIBUTES {
    RPG_TOWN_POPULATION = 2000,
    RPG_TOWN_TICKS_SINCE_TOWN_PRODUCTION,
    RPG_TOWN_GOLD,
    RPG_TOWN_INVENTORY,
    RPG_TOWN_ARMOURY,
    RPG_TOWN_GRANARY,
    RPG_TOWN_TRAINED_SOLDIERS,
    RPG_TOWN_TICKS_SINCE_TOWN_UPDATE_POP_CAP
};

const int TICKS_PER_TOWN_PRODUCTION = 4000;
const int TICKS_PER_TOWN_UPDATE_POP_CAP = 4000;


class RpgTown : public RpgZone
{
public:
    //constructors
    RpgTown(int newId, std::vector< std::vector<int> > tiles, RpgTileGridScene* gameScene);
    RpgTown(int newId, RpgTileGridScene* gameScene);
    RpgTown(SaveObject saveObject, RpgTileGridScene* gameScene);
    RpgTown(const RpgTown& oldMap);
    RpgTown();

    //methods
    void update() override;
    std::vector<Item*>& getTownInventory();
    int getTownGold();
    void setTownGold(int goldAmount);
    bool subtractFromTownGold(int goldAmount);
    void addToTownGold(int goldAmount);
    int getNumTrainedSoldiers();
    void addToTrainedSoldiers(int amountToAdd);
    void subtractFromTrainedSoldiers(int amountToSubtract);
    int getFreePop();
    void reducePopulation(int amount);
    void addPopulation(int amount);
    RpgTown* getNearestTown(Location* location) override;
    RpgTown* getNearestTown(int xpos, int ypos) override;
    int getPopulation();

    virtual std::string toSaveString(bool withHeaderAndFooter = true) override;

private:
    //attributes
    int population;
    int ticksSinceTownProduction;
    int ticksSinceTownUpdatePopCap;
    int townGold;
    int trainedSoldiers;
    std::vector<Item*> townInventory;
    std::vector<Equipment*> townArmoury;
    std::vector<Food*> townGranary;
    int freeTownsPeople;
        
    //methods
    void init();
    void processTownCycle();
    int getTownPopLimit();
    bool feedPopulace();
    RpgUnit* createTownsperson();
};

