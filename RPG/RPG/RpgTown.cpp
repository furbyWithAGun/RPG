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

void RpgTown::init()
{
    scene = nullptr;
    townZoneMap = nullptr;
}
