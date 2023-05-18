#include "Furnace.h"
#include "Unit.h"
#include "TransferItemsMenu.h"
#include "RpgOverWorldScene.h"
#include "RpgTown.h"

Furnace::Furnace() : DooDad()
{

}

Furnace::Furnace(TileGridScene* gameScene, int textureKey, int tileX, int tileY) : DooDad(gameScene, textureKey, tileX, tileY)
{
    init();
}

Furnace::Furnace(TileGridScene* gameScene, int tileX, int tileY) : DooDad(gameScene, tileX, tileY)
{
    init();
}

Furnace::Furnace(TileGridScene* gameScene) : DooDad(gameScene)
{
    init();
}

Furnace::Furnace(SaveObject saveObject, TileGridScene* gameScene) : DooDad(saveObject, gameScene)
{
    init();
}

void Furnace::actionOn(Unit* unit, int actionType)
{
    if (unit == ((RpgTileGridScene*)unit->scene)->player)
    {
        ((CraftingMenu*)scene->menus[CRAFTING_MENU])->open(((RpgTileGridScene*)unit->scene)->player, CRAFTING_STATION_FURNACE);
    }
}

void Furnace::init()
{
    type = DOODAD_FURNACE;
    textureKey = TEXTURE_FURNACE;
    passable = false;
}
