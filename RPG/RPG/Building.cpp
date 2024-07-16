#include "Building.h"
#include "RpgUnit.h"
#include "DooDad.h"
#include "RpgTileGridScene.h"
#include "RpgTown.h"

int uniqueBuildingId = 0;

Building::Building()
{
    init();
}

Building::Building(SaveObject saveObject)
{
    init();
    Location* savedLocation;
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case BUILDING_ID:
            id = stoi(saveObject.attributes[i].valueString);
            if (id > uniqueBuildingId) {
                uniqueBuildingId = id;
            }
            //else {
            //  id = getUniqueBuildingId();
            //}
            break;
        case BULDING_TYPE:
            type = stoi(saveObject.attributes[i].valueString);
            break;
        case BUILDING_TILE_MAP:
            setTileMap(getBuldingTileMapFromSaveString(saveObject.attributes[i].valueString));
            break;
        case BUILDING_ACTIVE:
            active = stoi(saveObject.attributes[i].valueString);
            break;
        case BUILDING_ICON_TEXTURE_ID:
            iconTextureId = stoi(saveObject.attributes[i].valueString);
            break;
        case BUILDING_GOLD_COST:
            goldCost = stoi(saveObject.attributes[i].valueString);
            break;
        case BUILDING_WOOD_COST:
            woodCost = stoi(saveObject.attributes[i].valueString);
            break;
        case BUILDING_LOCATION:
            savedLocation = getLocationFromSaveObject(SaveObject(saveObject.attributes[i].valueString));
            tileLocation->x = savedLocation->x;
            tileLocation->y = savedLocation->y;
            //tileLocation = getLocationFromSaveObject(SaveObject(saveObject.attributes[i].valueString));
            delete savedLocation;
            break;
        default:
            break;
        }
    }
}

Building::Building(int buildingType)
{
    init(buildingType);
}

Building::Building(int newWidth, int newHeight)
{
    init();
    width = newWidth;
    height = newHeight;
}

Building::Building(int buildingType, int newWidth, int newHeight)
{
    init(buildingType);
    width = newWidth;
    height = newHeight;
}

Building::Building(std::vector<std::vector<BuildingTile*>> newTileMap)
{
    init();
    setTileMap(newTileMap);
}

Building::Building(int buildingType, std::vector<std::vector<BuildingTile*>> newTileMap)
{
    init(buildingType);
    setTileMap(newTileMap);
}

int Building::getX()
{
    return tileLocation->x;
}

int Building::getY()
{
    return tileLocation->y;
}

void Building::update(RpgTileGridScene* scene)
{
    for (auto unit : assignedUnits) {
        if (unit->isTethered() && unit->getZone() == zone->id && zone->manhattenDistance(unit->tileDestination, tileLocation) > tetherUnitDistance)
        {
            unit->setTargetLocation(tileLocation->x + unitTeatherLocationOffset[0], tileLocation->y + unitTeatherLocationOffset[1]);
        }
    }

    if (spawnedUnitType != -1)
    {
        RpgTown* localTown = ((RpgZone*)scene->currentZone)->getNearestTown(tileLocation);
        if (localTown != nullptr)
        {
            unitSpawnTick++;
            if (unitSpawnTick >= unitSpawnRate)
            {
                unitSpawnTick = 0;
                /*if (localTown->getFreePop() > 0 && assignedUnits.size() < maxUnits)
                {
                    localTown->reducePopulation(1);
                    RpgUnit* newUnit = scene->createUnitAtLocation(zone, spawnedUnitType, tileLocation->x + unitTeatherLocationOffset[0], tileLocation->y + unitTeatherLocationOffset[1]);
                    assignUnit(newUnit);
                }*/
            }
        }
    }
}

BuildingTile* Building::getTileAtMapLocation(int x, int y)
{
    if (x < 0 + tileLocation->x || y < 0 + tileLocation->y || x > tileLocation->x + width || y > tileLocation->y + height)
    {
        return nullptr;
    }

    return tileMap[x - tileLocation->x][y - tileLocation->y];
}

int Building::onActionAssignedUnit(RpgUnit* unit)
{
    return 0;
}

int Building::onActionAssignedDooDad(DooDad* dooDad)
{
    return 0;
}


void Building::assignUnit(RpgUnit* unit)
{
    assignedUnits.push_back(unit);
    unit->assignedToBuilding = this;
    unit->canGoThroughPortal = false;
    unit->setTethered(true);
    if (unit->type != PLAYER)
    {
        ((AiUnit*)unit)->doesRandomMovement = unitRandomMovement;
    }
}

void Building::houseUnit(RpgUnit* unit)
{
    housedUnits.push_back(unit);
    unit->unitHouse = this;
}

void Building::unAssignUnit(RpgUnit* unit)
{
    unit->setTethered(false);
    unit->assignedToBuilding = nullptr;
    auto unitIterator = assignedUnits.begin();
    while (unitIterator != assignedUnits.end())
    {
        if ((*unitIterator) == unit) {
            unitIterator = assignedUnits.erase(unitIterator);
            break;
        }
        else {
            unitIterator++;
        }
    }
}

void Building::unHouseUnit(RpgUnit* unit)
{
    unit->unitHouse = nullptr;
    auto unitIterator = housedUnits.begin();
    while (unitIterator != housedUnits.end())
    {
        if ((*unitIterator) == unit) {
            unitIterator = housedUnits.erase(unitIterator);
            break;
        }
        else {
            unitIterator++;
        }
    }
}

void Building::assignDooDad(DooDad* dooDad)
{
    assignedDooDads.push_back(dooDad);
    dooDad->assignedToBuilding = this;
}

void Building::unAssignDooDad(DooDad* dooDad)
{
    auto dooDadIterator = assignedDooDads.begin();
    while (dooDadIterator != assignedDooDads.end())
    {
        if ((*dooDadIterator) == dooDad) {
            dooDadIterator = assignedDooDads.erase(dooDadIterator);
            break;
        }
        else {
            dooDadIterator++;
        }
    }
    dooDad->assignedToBuilding = nullptr;
}

void Building::setTileMap(std::vector<std::vector<BuildingTile*>> newTileMap)
{
    tileMap = newTileMap;
    width = newTileMap.size();
    height = newTileMap[0].size();
}

std::string Building::toSaveString()
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_BUILDING) + "\n";
    saveString += getAttributeString(getUniqueId(), BULDING_TYPE, type);
    saveString += getAttributeString(getUniqueId(), BUILDING_ID, id);
    saveString += getAttributeString(getUniqueId(), BUILDING_TILE_MAP, getBuildingTileMapSaveString());
    saveString += getAttributeString(getUniqueId(), BUILDING_LOCATION, getLocationSaveString(tileLocation));
    saveString += getAttributeString(getUniqueId(), BUILDING_ACTIVE, active);
    saveString += getAttributeString(getUniqueId(), BUILDING_GOLD_COST, goldCost);
    saveString += getAttributeString(getUniqueId(), BUILDING_WOOD_COST, woodCost);
    saveString += getAttributeString(getUniqueId(), BUILDING_ICON_TEXTURE_ID, iconTextureId);
    saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_BUILDING) + "\n";

    return saveString;
}

std::string Building::getBuildingTileMapSaveString()
{
    std::string returnString;
    returnString += std::to_string(tileMap.size()) + "\n";
    for (int i = 0; i < tileMap.size(); i++)
    {
        returnString += std::to_string(tileMap[i].size()) + "\n";
        for (int j = 0; j < tileMap[i].size(); j++)
        {
            if (tileMap[i][j] != nullptr)
            {
                returnString += tileMap[i][j]->toSaveString();
            }
            else {
                int uniqueObjectId = getUniqueId();
                returnString += BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_BULIDING_TILE) + "\n";
                returnString += getAttributeString(getUniqueId(), MAP_TILE_PASSABLE, true);
                returnString += getAttributeString(getUniqueId(), MAP_TILE_TEXTURE_KEY, -1);
                returnString += getAttributeString(getUniqueId(), MAP_TILE_WIDTH, -1);
                returnString += getAttributeString(getUniqueId(), MAP_TILE_HEIGHT, -1);
                returnString += getAttributeString(getUniqueId(), BUILDING_TILE_DESTRUCTABLE, false);
                returnString += getAttributeString(getUniqueId(), BUILDING_TILE_HEALTH, -1);
                returnString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_BULIDING_TILE) + "\n";
            }
        }
    }

    return returnString;
}

std::vector<std::vector<BuildingTile*>> Building::getBuldingTileMapFromSaveString(std::string saveString)
{
    std::vector<std::vector<BuildingTile*>> returnVector;
    std::string::size_type index1 = 0, index2 = 0;
    int outerSize, innerSize, innerCount = 0;
    std::string innerSaveString = "";
    bool gotInnerSize = false;

    std::vector<std::vector<SaveObject>> saveObjectsVector = getSaveObject2dVectorFromSaveString2(saveString);

    for (int x = 0; x < saveObjectsVector.size(); x++)
    {
        std::vector<BuildingTile* > tileVector;
        for (int y = 0; y < saveObjectsVector[x].size(); y++)
        {
            BuildingTile* newTile = new BuildingTile(saveObjectsVector[x][y]);
            tileVector.push_back(newTile);
        }
        returnVector.push_back(tileVector);
    }


    return returnVector;
}

std::vector<BuildingTile*> Building::getBuldingTileVectorFromSaveString(std::string saveString) {
    std::vector<BuildingTile*> returnVector;
    
    return returnVector;
}

void Building::resetUid()
{
    uniqueBuildingId = 0;
}

std::vector<Item*> Building::production(RpgTown* town)
{
    if (townCanAfffordProduction(town))
    {
        return createOutputs(town);
    }
    return std::vector<Item*>();
}

void Building::setZone(ZoneMap* newZone)
{
    zone = newZone;
}

int Building::getPopSupported()
{
    return popSupported;
}

int Building::getPopCost()
{
    return popCost;
}

std::string Building::getBuildingName()
{
    return buildingName;
}

bool Building::canBeBuiltOnOverworld()
{
    return overworldBuildable;
}

void Building::setCanBeBuiltOnOverworld(bool newVal)
{
    overworldBuildable = newVal;
}

std::vector<ProductionInputOutput> Building::getProductionOutputs()
{
    return productionOutputs;
}

RpgUnit* Building::createHousedUnit(RpgTileGridScene* scene)
{
    RpgUnit* newUnit = scene->createUnitAtLocation(zone, spawnedUnitType, tileLocation->x + unitTeatherLocationOffset[0], tileLocation->y + unitTeatherLocationOffset[1]);
    houseUnit(newUnit);
    return newUnit;
}

void Building::init()
{
    overworldBuildable = false;
    id = -1;
    type = -1;
    width = height = 0;
    tileLocation = new Location{ -1, -1 }; // memory leak
    active = true;
    iconTextureId = -1;
    goldCost = 1;
    woodCost = 1;
    productionGoldCost = 0;
    popSupported = 0;
    popCost = 0;
    productionInputs = {};
    productionOutputs = {};
    zone = nullptr;
    buildingName = "";
    overworldBuildable = false;
    unitTeatherLocationOffset[0] = 0;
    unitTeatherLocationOffset[1] = 0;
    spawnedUnitType = -1;
    maxUnits= 0;
    unitSpawnTick = 0;
    unitSpawnRate = 0;
    unitRandomMovement = true;
    tetherUnitDistance = DEFAULT_UNIT_TETHER_DISTANCE;
}

void Building::init(int buildingType)
{
    init();
    type = buildingType;
}

bool Building::townCanAfffordProduction(RpgTown* town)
{
    if (town->getTownGold() < productionGoldCost)
    {
        return false;
    }

    for (auto item : productionInputs) {
        if (qtyInContainer(item.itemType, town->getTownInventory()) < item.qty) {
            return false;
        }
    }

    return true;
}

std::vector<Item*> Building::createOutputs(RpgTown* town)
{
    std::vector<Item*> returnItems;
    Item* newItem;
    
    for (auto item : productionInputs) {
        removeQtyFromContainer(item.itemType, item.qty, town->getTownInventory());
    }

    town->subtractFromTownGold(productionGoldCost);

    for (auto item : productionOutputs) {
        newItem = createNewItem(item.itemType);
        if (newItem->stackable)
        {
            newItem->stackSize = item.qty;
            returnItems.push_back(newItem);
        }
        else {
            for (size_t i = 0; i < (item.qty); i++)
            {
                returnItems.push_back(createNewItem(item.itemType));
            }
        }
    }
    return returnItems;
}



int getUniqueBuildingId()
{
    uniqueBuildingId++;
    return uniqueBuildingId;
}
