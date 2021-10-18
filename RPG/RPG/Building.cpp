#include "Building.h"
#include "Unit.h"

Building::Building()
{
    init();
}

Building::Building(int newWidth, int newHeight)
{
    init();
    width = newWidth;
    height = newHeight;
}

Building::Building(std::vector<std::vector<BuildingTile*>> newTileMap)
{
    init();
    tileMap = newTileMap;
    width = newTileMap.size();
    height = newTileMap[0].size();
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

int Building::onActionAssignedUnit(Unit* unit)
{
    return 0;
}

void Building::assignUnit(Unit* unit)
{
    assignedUnits.push_back(unit);
    unit->assignedToBuilding = this;
}

void Building::unAssignUnit(Unit* unit)
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


void Building::init()
{
    width = height = 0;
    tileLocation = new Location{ 0, 0 };
    active = true;
}
