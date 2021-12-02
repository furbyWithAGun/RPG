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
    for (auto building : getBuildings())
    {
        building->update(scene);
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
    population++;
    std::vector<Item*> producedItems;
    for (auto building : getBuildings()){
        for (auto item : building->production(this)) {
            producedItems.push_back(item);
        }
    }
    for (auto item : producedItems)
    {
        addItemToContainer(item, getTownInventory());
    }
    scene->menus[TRANSFER_ITEMS_MENU]->rebuildElements();
}
