#include "Building.h"
#include "RpgUnit.h"
#include "DooDad.h"

int uniqueBuildingId = 0;

Building::Building()
{
    init();
}

Building::Building(SaveObject saveObject)
{
    init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case BUILDING_ID:
            id = stoi(saveObject.attributes[i].valueString);
            if (id > uniqueBuildingId) {
                uniqueBuildingId = id;
            }
            else {
                id = getUniqueBuildingId();
            }
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
        case BUILDING_LOCATION:
            tileLocation = getLocationFromSaveObject(SaveObject(saveObject.attributes[i].valueString));
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
}

void Building::unAssignUnit(RpgUnit* unit)
{
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

void Building::assignDooDad(DooDad* dooDad)
{
    assignedDooDads.push_back(dooDad);
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

    /*for (std::string::size_type i = 0; i < saveString.size(); i++)
    {
        if (saveString[i] == '\n')
        {
            index2 = i;
            break;
        }
    }
    outerSize = stoi(saveString.substr(index1, index2 - index1));
    index1 = index2 + 1;

    for (int i = 0; i < outerSize; i++)
    {
        for (int j = index1; j < saveString.size(); j++)
        {
            if (saveString[j] == '\n')
            {
                index2 = j;
                if (!gotInnerSize)
                {
                    innerSize = stoi(saveString.substr(index1, index2 - index1));
                    gotInnerSize = true;
                }
                else if (innerCount < innerSize) {
                    innerCount += 1;
                }
                if (innerCount == innerSize) {
                    std::string substring = saveString.substr(index1, index2 - index1);
                    returnVector.push_back(getBuldingTileVectorFromSaveString(saveString.substr(index1, index2 - index1 + 1)));
                    innerCount = 0;
                    gotInnerSize = false;
                    index1 = index2 + 1;
                    break;
                }
            }
        }
    }*/


    return returnVector;
}

std::vector<BuildingTile*> Building::getBuldingTileVectorFromSaveString(std::string saveString) {
    std::vector<BuildingTile*> returnVector;
    
    return returnVector;
}


void Building::init()
{
    id = -1;
    type = -1;
    width = height = 0;
    tileLocation = new Location{ -1, -1 };
    active = true;
    iconTextureId = -1;
}

void Building::init(int buildingType)
{
    init();
    type = buildingType;
}

int getUniqueBuildingId()
{
    uniqueBuildingId++;
    return uniqueBuildingId;
}
