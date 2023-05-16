#include "Orchard.h"
#include "RpgUnit.h"
#include "SelectPrompt.h"
#include "RpgTileGridScene.h"

Orchard::Orchard() : Building()
{
    init();
}

Orchard::Orchard(SaveObject saveObject) : Building(saveObject)
{
    init();
}

Orchard::Orchard(int newWidth, int newHeight) : Building(newWidth, newHeight)
{
    init();
}

Orchard::Orchard(std::vector<std::vector<BuildingTile*>> newTileMap) : Building(newTileMap)
{
    init();
}

Orchard::Orchard(int entranceDirection) : Building()
{
    init();
    switch (entranceDirection)
    {
    case LEFT:
        setTileMap({
        {new BuildingTile(false, TEXTURE_PICKET_FENCE_TOP_LEFT), new BuildingTile(false, TEXTURE_PICKET_FENCE_LEFT), nullptr, new BuildingTile(false, TEXTURE_PICKET_FENCE_LEFT), new BuildingTile(false, TEXTURE_PICKET_FENCE_LEFT),  new BuildingTile(false, TEXTURE_PICKET_FENCE_BOTTOM_LEFT)},
        {new BuildingTile(false, TEXTURE_PICKET_FENCE_TOP), nullptr, nullptr, nullptr, nullptr, new BuildingTile(false, TEXTURE_PICKET_FENCE_BOTTOM) },
        {new BuildingTile(false, TEXTURE_PICKET_FENCE_TOP), nullptr, nullptr, nullptr, nullptr, new BuildingTile(false, TEXTURE_PICKET_FENCE_BOTTOM) },
        {new BuildingTile(false, TEXTURE_PICKET_FENCE_TOP), nullptr, nullptr, nullptr, nullptr, new BuildingTile(false, TEXTURE_PICKET_FENCE_BOTTOM) },
        {new BuildingTile(false, TEXTURE_PICKET_FENCE_TOP), nullptr, nullptr, nullptr, nullptr, new BuildingTile(false, TEXTURE_PICKET_FENCE_BOTTOM) },
        {new BuildingTile(false, TEXTURE_PICKET_FENCE_TOP), nullptr, nullptr, nullptr, nullptr, new BuildingTile(false, TEXTURE_PICKET_FENCE_BOTTOM) },
        {new BuildingTile(false, TEXTURE_BUILDING_HOUSE), new BuildingTile(false, TEXTURE_PICKET_FENCE_RIGHT), new BuildingTile(false, TEXTURE_PICKET_FENCE_RIGHT), new BuildingTile(false, TEXTURE_PICKET_FENCE_RIGHT), new BuildingTile(false, TEXTURE_PICKET_FENCE_RIGHT), new BuildingTile(false, TEXTURE_PICKET_FENCE_BOTTOM_RIGHT) },
            });

        break;
    case RIGHT:
        setTileMap({
        {new BuildingTile(false, TEXTURE_PICKET_FENCE_BOTTOM_LEFT), new BuildingTile(false, TEXTURE_PICKET_FENCE_LEFT), new BuildingTile(false, TEXTURE_PICKET_FENCE_LEFT), new BuildingTile(false, TEXTURE_PICKET_FENCE_LEFT), new BuildingTile(false, TEXTURE_PICKET_FENCE_LEFT), new BuildingTile(false, TEXTURE_PICKET_FENCE_TOP_LEFT) },
        {new BuildingTile(false, TEXTURE_PICKET_FENCE_BOTTOM), nullptr, nullptr, nullptr, nullptr, new BuildingTile(false, TEXTURE_PICKET_FENCE_TOP) },
        {new BuildingTile(false, TEXTURE_PICKET_FENCE_BOTTOM), nullptr, nullptr, nullptr, nullptr, new BuildingTile(false, TEXTURE_PICKET_FENCE_TOP) },
        {new BuildingTile(false, TEXTURE_PICKET_FENCE_BOTTOM), nullptr, nullptr, nullptr, nullptr, new BuildingTile(false, TEXTURE_PICKET_FENCE_TOP) },
        {new BuildingTile(false, TEXTURE_PICKET_FENCE_BOTTOM), nullptr, nullptr, nullptr, nullptr, new BuildingTile(false, TEXTURE_PICKET_FENCE_TOP) },
        {new BuildingTile(false, TEXTURE_PICKET_FENCE_BOTTOM), nullptr, nullptr, nullptr, nullptr, new BuildingTile(false, TEXTURE_PICKET_FENCE_TOP) },
        {new BuildingTile(false, TEXTURE_PICKET_FENCE_BOTTOM_RIGHT), new BuildingTile(false, TEXTURE_PICKET_FENCE_RIGHT), nullptr, new BuildingTile(false, TEXTURE_PICKET_FENCE_RIGHT), new BuildingTile(false, TEXTURE_PICKET_FENCE_RIGHT), new BuildingTile(false, TEXTURE_PICKET_FENCE_TOP_RIGHT) },
            });

        break;
    default:
        break;
    }
}

int Orchard::onActionAssignedUnit(RpgUnit* unit)
{
    return 0;
}

void Orchard::update(RpgTileGridScene* scene)
{

}


void Orchard::init()
{
    buildingName = "Orchard";
    productionOutputs.push_back({ ITEM_APPLE, 4 });
    type = BUILDING_APPLE_ORCHARD;
    iconTextureId = BUILDING_ICON_WOODCUTTER;
    goldCost = 100;
    woodCost = 100;
    popCost = 5;
    doodadsOnConstruct.push_back({ DOODAD_APPLE_TREE , 2, 2 });
    doodadsOnConstruct.push_back({ DOODAD_APPLE_TREE , 4, 2 });
    doodadsOnConstruct.push_back({ DOODAD_APPLE_TREE , 2, 4 });
    doodadsOnConstruct.push_back({ DOODAD_APPLE_TREE , 4, 4 });
}
