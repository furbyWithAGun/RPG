#include "RpgTown.h"
#include "RpgTileGridScene.h"

RpgTown::RpgTown()
{
    init();
}

RpgTown::RpgTown(RpgTileGridScene* gameScene)
{
    init();
    scene = gameScene;
}

RpgTown::RpgTown(RpgTileGridScene* gameScene, int zoneMapId)
{
    init();
    scene = gameScene;
    townZoneMap = scene->getZone(zoneMapId);
}

void RpgTown::update()
{
    ticksSinceTownProduction++;
    if (ticksSinceTownProduction > TICKS_PER_TOWN_PRODUCTION)
    {
        processTownCycle();
        ticksSinceTownProduction = 0;
    }
}

ZoneMap* RpgTown::getZoneMap()
{
    return townZoneMap;
}

void RpgTown::init()
{
    ticksSinceTownProduction = 0;
    population = 0;
    scene = nullptr;
    townZoneMap = nullptr;
}

void RpgTown::processTownCycle()
{
    population++;
}
