#include "WoodCutter.h"
#include "RpgUnit.h"
#include "SelectPrompt.h"
#include "RpgTileGridScene.h"

WoodCutter::WoodCutter() : Building()
{
    init();
}

WoodCutter::WoodCutter(SaveObject saveObject) : Building(saveObject)
{
    init();
}

WoodCutter::WoodCutter(int newWidth, int newHeight) : Building(newWidth, newHeight)
{
    init();
}

WoodCutter::WoodCutter(std::vector<std::vector<BuildingTile*>> newTileMap) : Building(newTileMap)
{
    init();
}

WoodCutter::WoodCutter(int entranceDirection) : Building()
{
    init();
    switch (entranceDirection)
    {
    case LEFT:
        setTileMap({
        {new BuildingTile(false, TEXTURE_BUILDING_WOODCUTTER)
            } });
        break;
    case RIGHT:
        setTileMap({
        {new BuildingTile(false, TEXTURE_BUILDING_WOODCUTTER)
            } });
        break;
    default:
        break;
    }
}

int WoodCutter::onActionAssignedUnit(RpgUnit* unit)
{
    return 0;
}

void WoodCutter::update(RpgTileGridScene* scene)
{

}


void WoodCutter::init()
{
    buildingName = "Wood Cutters hut";
    productionOutputs.push_back({ITEM_WOOD, 5});
    type = BUILDING_WOODCUTTER;
    iconTextureId = BUILDING_ICON_WOODCUTTER;
    goldCost = 100;
    woodCost = 10;
}
