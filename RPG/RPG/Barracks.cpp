#include "Barracks.h"
#include "RpgUnit.h"
#include "SelectPrompt.h"
#include "RpgTileGridScene.h"

const int SOLDIER_GOLD_COST = 500;

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
            TownsPerson* newSoldier = (TownsPerson*)((RpgTown*)zone)->getAnyTownsperson();
            switch (barracksSelectPrompt->getSelectedOptionValue())
            {
            case 1:
                /*if (unit->scene->player->gold >= 500 && ((RpgTown*)zone)->getFreePop() > 0)
                {
                    unit->scene->player->gold -= 500;
                    ((RpgTown*)zone)->addToTrainedSoldiers(1);
                   */ //((RpgTown*)zone)->reducePopulation(1);
                //}
                if (unit->scene->player->gold >= SOLDIER_GOLD_COST && newSoldier) { //add test for avil pop
                    unit->scene->player->gold -= SOLDIER_GOLD_COST;
                    newSoldier->convertToSoldier();
                    newSoldier->unAssignFromBuilding();
                    //((RpgTown*)zone)->reducePopulation(1);
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


void Barracks::init()
{
    type = BUILDING_BARRACKS;
    iconTextureId = BUILDING_ICON_BLACKSMITH;
    goldCost = 100;
    woodCost = 200;
    troopSpawnTick = 0;
    troopSpawnRate = 1000;
    buildingName = "Barracks";
    unitTeatherLocationOffset[0] = 3;
    unitTeatherLocationOffset[1] = 2;
    spawnedUnitType = TOWNSPERSON;
    maxUnits = 1;
    unitRandomMovement = false;
}
