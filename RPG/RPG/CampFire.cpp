#include "CampFire.h"

#include "Unit.h"
#include "TransferItemsMenu.h"
#include "RpgOverWorldScene.h"
#include "RpgTown.h"

CampFire::CampFire() : DooDad()
{

}

CampFire::CampFire(TileGridScene* gameScene, int textureKey, int tileX, int tileY) : DooDad(gameScene, textureKey, tileX, tileY)
{
    init();
}

CampFire::CampFire(TileGridScene* gameScene, int tileX, int tileY) : DooDad(gameScene, tileX, tileY)
{
    init();
}

CampFire::CampFire(TileGridScene* gameScene) : DooDad(gameScene)
{
    init();
}

CampFire::CampFire(SaveObject saveObject, TileGridScene* gameScene) : DooDad(saveObject, gameScene)
{
    init();
}

void CampFire::actionOn(Unit* unit, int actionType)
{
    if (unit == ((RpgTileGridScene*)unit->scene)->player)
    {
        ((CraftingMenu*)scene->menus[CRAFTING_MENU])->open(((RpgTileGridScene*)unit->scene)->player, CRAFTING_STATION_CAMP_FIRE);
    }
}

void CampFire::init()
{
    type = DOODAD_CAMP_FIRE;
    textureKey = TEXTURE_CAMP_FIRE;
    passable = false;
}
