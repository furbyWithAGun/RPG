#include "House.h"
#include "RpgUnit.h"
#include "SelectPrompt.h"
#include "RpgTileGridScene.h"

House::House() : Building()
{
    init();
}

House::House(SaveObject saveObject) : Building(saveObject)
{
    init();
}

House::House(int newWidth, int newHeight) : Building(newWidth, newHeight)
{
    init();
}

House::House(std::vector<std::vector<BuildingTile*>> newTileMap) : Building(newTileMap)
{
    init();
}

House::House(int entranceDirection) : Building()
{
    init();
    switch (entranceDirection)
    {
    case LEFT:
        setTileMap({
        {new BuildingTile(false, TEXTURE_BUILDING_HOUSE)
            } });
        break;
    case RIGHT:
        setTileMap({
        {new BuildingTile(false, TEXTURE_BUILDING_HOUSE)
            } });
        break;
    default:
        break;
    }
}

int House::onActionAssignedUnit(RpgUnit* unit)
{
    return 0;
}

void House::update(RpgTileGridScene* scene)
{

}


void House::init()
{
    type = BUILDING_HOUSE;
    iconTextureId = BUILDING_ICON_HOUSE;
    goldCost = 50;
    woodCost = 40;
    popSupported = 10;
    buildingName = "House";
}

