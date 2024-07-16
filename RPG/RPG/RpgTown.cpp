#include "RpgTown.h"
#include "RpgTileGridScene.h"


RpgTown::RpgTown(int newId, std::vector<std::vector<int>> tiles, RpgTileGridScene* gameScene) : RpgZone(newId, tiles, gameScene)
{
    init();
}

RpgTown::RpgTown(int newId, RpgTileGridScene* gameScene) : RpgZone(newId, gameScene)
{
    init();
}

RpgTown::RpgTown(SaveObject saveObject, RpgTileGridScene* gameScene) : RpgZone(saveObject, gameScene)
{
    init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case RPG_TOWN_POPULATION:
            population = stoi(saveObject.attributes[i].valueString);
            break;
        case RPG_TOWN_TICKS_SINCE_TOWN_PRODUCTION:
            ticksSinceTownProduction = stoi(saveObject.attributes[i].valueString);
            break;
        case RPG_TOWN_GOLD:
            townGold = stoi(saveObject.attributes[i].valueString);
            break;
        case RPG_TOWN_TRAINED_SOLDIERS:
            trainedSoldiers = stoi(saveObject.attributes[i].valueString);
            break;
        case RPG_TOWN_TICKS_SINCE_TOWN_UPDATE_POP_CAP:
            ticksSinceTownUpdatePopCap = stoi(saveObject.attributes[i].valueString);
            break;
        case RPG_TOWN_INVENTORY:
            townInventory = getItemVectorFromSaveString(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
}

RpgTown::RpgTown(const RpgTown& oldMap) : RpgZone(oldMap)
{
    init();
    population = oldMap.population;
    ticksSinceTownProduction = oldMap.ticksSinceTownProduction;
    townGold = oldMap.townGold;
    townInventory = oldMap.townInventory;
    townArmoury = oldMap.townArmoury;
    townGranary = oldMap.townGranary;
    trainedSoldiers = oldMap.trainedSoldiers;
}

RpgTown::RpgTown() : RpgZone()
{
    init();
}

void RpgTown::update()
{
    RpgZone::update();
    ticksSinceTownProduction++;
    ticksSinceTownUpdatePopCap++;
    if (ticksSinceTownProduction > TICKS_PER_TOWN_PRODUCTION)
    {
        processTownCycle();
        ticksSinceTownProduction = 0;
    }
}

std::vector<Item*>& RpgTown::getTownInventory()
{
    return townInventory;
}

int RpgTown::getTownGold()
{
    return townGold;
}

void RpgTown::setTownGold(int goldAmount)
{
    townGold = goldAmount;
}

bool RpgTown::subtractFromTownGold(int goldAmount)
{
    townGold -= goldAmount;
    if (townGold < 0)
    {
        townGold = 0;
        return false;
    }
    return true;
}

void RpgTown::addToTownGold(int goldAmount)
{
    townGold += goldAmount;
}

int RpgTown::getNumTrainedSoldiers()
{
    return trainedSoldiers;
}

void RpgTown::addToTrainedSoldiers(int amountToAdd)
{
    trainedSoldiers += amountToAdd;
}

void RpgTown::subtractFromTrainedSoldiers(int amountToSubtract)
{
    trainedSoldiers -= amountToSubtract;
    if (trainedSoldiers < 0)
    {
        trainedSoldiers = 0;
    }
}

std::string RpgTown::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_RPG_TOWN) + "\n";
    }
    saveString += RpgZone::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), RPG_TOWN_POPULATION, population);
    saveString += getAttributeString(getUniqueId(), RPG_TOWN_TICKS_SINCE_TOWN_PRODUCTION, ticksSinceTownProduction);
    saveString += getAttributeString(getUniqueId(), RPG_TOWN_TICKS_SINCE_TOWN_UPDATE_POP_CAP, ticksSinceTownUpdatePopCap);
    saveString += getAttributeString(getUniqueId(), RPG_TOWN_GOLD, townGold);
    saveString += getAttributeString(getUniqueId(), RPG_TOWN_TRAINED_SOLDIERS, trainedSoldiers);
    saveString += getAttributeString(getUniqueId(), RPG_TOWN_INVENTORY, getItemVectorSaveString(townInventory));
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_RPG_TOWN) + "\n";
    }
    return saveString;
}

void RpgTown::init()
{
    zoneType = ZONE_RPG_TOWN;
    townGold = 0;
    ticksSinceTownProduction = 0;
    ticksSinceTownUpdatePopCap = 0;
    population = 0;
    trainedSoldiers = 0;
}

void RpgTown::processTownCycle()
{
    int townPopLimit = getTownPopLimit();
    int totalPopulation = getPopulation();
    if (totalPopulation <= 1) {
        totalPopulation = 1;
    }
    //if (feedPopulace() && totalPopulation + trainedSoldiers < townPopLimit)
    if (feedPopulace())
    {
        int foodToPopRatio;
        int totalFoodPower = 0;
        for (auto item : townInventory) {
            if (item->generalType == FOOD)
            {
                totalFoodPower += ((Food*)item)->hungerGain * item->stackSize;
            }
        }

        foodToPopRatio = floor(totalFoodPower / totalPopulation);
        if (foodToPopRatio > townPopLimit - (totalPopulation + trainedSoldiers))
        {
            foodToPopRatio = townPopLimit - (totalPopulation + trainedSoldiers);
        }
        if (foodToPopRatio < 1)
        {
            foodToPopRatio = 1;
        }
        for (size_t i = 0; i < foodToPopRatio; i++)
        {
            createTownsperson();
        }
        //population += foodToPopRatio;
    }
    std::vector<Item*> producedItems;
    for (auto building : getBuildings()){
        for (auto item : building->production(this)) {
            producedItems.push_back(item);
        }
        if (building->type == BUILDING_ITEM_SHOP)
        {
            ((ItemShop*)building)->setItemsForSale(this);
        }
    }
    for (auto item : producedItems)
    {
        addItemToContainer(item, getTownInventory());
    }
    scene->menus[TRANSFER_ITEMS_MENU]->rebuildMenuElements();
}

int RpgTown::getTownPopLimit()
{
    int popLimit = 0;
    for (auto building : getBuildings()) {
        popLimit += building->getPopSupported();
    }
    return popLimit;
}

bool RpgTown::feedPopulace()
{
    bool returnValue = false;
    int hungerToSatisfy = getPopulation() + trainedSoldiers;
    std::vector<Item*> itemsToDelete;
    for (auto item : townInventory) {
        if (item->generalType == FOOD)
        {
            if (((Food*)item)->hungerGain * item->stackSize > hungerToSatisfy) {
                removeQtyFromContainer(item->specificType, hungerToSatisfy/ ((Food*)item)->hungerGain + (hungerToSatisfy % ((Food*)item)->hungerGain != 0), townInventory);
                hungerToSatisfy = 0;
                returnValue = true;
                goto endOfFunction;
            }
            else {
                hungerToSatisfy -= ((Food*)item)->hungerGain * item->stackSize;
                itemsToDelete.push_back(item);
            }
        }
    }
    for (auto item : itemsToDelete) {
        deleteItemFromContainer(item, townInventory);
    }
    endOfFunction:
    return returnValue;
}

RpgUnit* RpgTown::createTownsperson()
{
    RpgUnit* returnUnit = nullptr;
    for (Building* building : getBuildings())
    {
        if (building->housedUnits.size() < building->getPopSupported()) {
            returnUnit = building->createHousedUnit(scene);
            return returnUnit;
        }
    }

    return returnUnit;
}

int RpgTown::getFreePop()
{
    int popCost = 0;
    for (auto building : getBuildings()) {
        popCost += building->getPopCost();
    }
    return population - popCost - trainedSoldiers;
}

void RpgTown::reducePopulation(int amount)
{
    population -= amount;
}

void RpgTown::addPopulation(int amount)
{
    population += amount;
}

RpgTown* RpgTown::getNearestTown(Location* location)
{
    return this;
}

RpgTown* RpgTown::getNearestTown(int xpos, int ypos)
{
    return this;
}

int RpgTown::getPopulation()
{
    int totalPop = 0;
    for (Building* building : getBuildings())
    {
        totalPop += building->housedUnits.size();
    }
    return totalPop;
}
