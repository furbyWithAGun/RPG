#include "SmeltingWorks.h"
#include "RpgUnit.h"
#include "SelectPrompt.h"
#include "RpgTileGridScene.h"

SmeltingWorks::SmeltingWorks() : Building()
{
    init();
}

SmeltingWorks::SmeltingWorks(SaveObject saveObject) : Building(saveObject)
{
    init();
}

SmeltingWorks::SmeltingWorks(int newWidth, int newHeight) : Building(newWidth, newHeight)
{
    init();
}

SmeltingWorks::SmeltingWorks(std::vector<std::vector<BuildingTile*>> newTileMap) : Building(newTileMap)
{
    init();
}

SmeltingWorks::SmeltingWorks(int entranceDirection) : Building()
{
    init();
    switch (entranceDirection)
    {
    case LEFT:
        setTileMap({
        {new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), nullptr, new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), nullptr, nullptr, nullptr, nullptr, new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), nullptr, nullptr, nullptr, nullptr, new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), nullptr, nullptr, nullptr, nullptr, new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO) },
            });

        break;
    case RIGHT:
        setTileMap({
        {new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), nullptr, new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), nullptr, nullptr, nullptr, nullptr, new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), nullptr, nullptr, nullptr, nullptr, new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), nullptr, nullptr, nullptr, nullptr, new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), nullptr, new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO) },
            });

        break;
    default:
        break;
    }
}



void SmeltingWorks::init()
{
    type = BUILDING_SMELTING_WORKS;
    iconTextureId = BUILDING_ICON_BLACKSMITH;
    goldCost = 100;
    woodCost = 200;
    buildingName = "Smelting Works";
    unitTeatherLocationOffset[0] = 3;
    unitTeatherLocationOffset[1] = 2;
    spawnedUnitType = TOWNSPERSON;
    maxUnits = 1;
    doodadsOnConstruct.push_back({ DOODAD_FURNACE , 2, 1 });
    //production
    productionInputs.push_back({ ITEM_TIN_ORE, 5 });
    productionInputs.push_back({ ITEM_COPPER_ORE, 5 });
    productionInputs.push_back({ ITEM_COAL, 3 });
    productionOutputs.push_back({ ITEM_BRONZE_BAR, 1 });
}
