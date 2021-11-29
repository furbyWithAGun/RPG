#include "Barracks.h"
#include "RpgUnit.h"
#include "SelectPrompt.h"
#include "RpgTileGridScene.h"

Barracks::Barracks() : Building()
{
    init();
}

Barracks::Barracks(SaveObject saveObject) : Building(saveObject)
{
    init();
}

Barracks::Barracks(int newWidth, int newHeight) : Building(newWidth, newHeight)
{
    init();
}

Barracks::Barracks(std::vector<std::vector<BuildingTile*>> newTileMap) : Building(newTileMap)
{
    init();
}

Barracks::Barracks(int entranceDirection) : Building()
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

int Barracks::onActionAssignedUnit(RpgUnit* unit)
{
    if (zone != nullptr && ((RpgZone*)zone)->zoneType == ZONE_RPG_TOWN)
    {
        SelectPrompt* barracksSelectPrompt;
        barracksSelectPrompt = new SelectPrompt(unit->scene, COLOR_BLACK, unit->scene->engine->screenWidth * 0.5, unit->scene->engine->screenHeight * 0.5, unit->scene->engine->screenWidth * 0.1, unit->scene->engine->screenHeight * 0.1);
        barracksSelectPrompt->addSelectOption("Train Soldier", 1);
        barracksSelectPrompt->addCallBack([this, barracksSelectPrompt, unit]() {
            switch (barracksSelectPrompt->getSelectedOptionValue())
            {
            case 1:
                if (unit->scene->player->gold >= 1000)
                {
                    unit->scene->player->gold -= 1000;
                    ((RpgTown*)zone)->addToTrainedSoldiers(1);
                }
                break;
            default:
                break;
            }
            unit->scene->removePrompt(barracksSelectPrompt);
            });
        barracksSelectPrompt->active = true;
        barracksSelectPrompt->closeOnClickMiss = true;
        unit->scene->addPrompt(barracksSelectPrompt);
    }
    return 0;
}

void Barracks::update(RpgTileGridScene* scene)
{
    if (zone != nullptr && ((RpgZone*)zone)->zoneType == ZONE_RPG_TOWN)
    {
        troopSpawnTick++;
        if (troopSpawnTick >= troopSpawnRate)
        {
            troopSpawnTick = 0;
            if (((RpgTown*)zone)->getNumTrainedSoldiers() > 0)
            {
                ((RpgTown*)zone)->subtractFromTrainedSoldiers(1);
                ((RpgTown*)zone)->addUnitToLocation(new Soldier(zone->id, SOLDIER, scene, tileLocation->x + 1, tileLocation->y + 1), tileLocation->x + 1, tileLocation->y + 1);
            }
        }
    }
}


void Barracks::init()
{
    type = BUILDING_BARRACKS;
    iconTextureId = BUILDING_ICON_BLACKSMITH;
    goldCost = 100;
    woodCost = 10;
    troopSpawnTick = 0;
    troopSpawnRate = 1000;
}
