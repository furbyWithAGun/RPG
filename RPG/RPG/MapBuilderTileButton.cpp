#include "MapBuilderTileButton.h"

//constants
static const int WIDTH_ADJUSTOR = 38;
static const int HEIGHT_ADJUSTOR = 20;

//constructors
MapBuilderTileButton::MapBuilderTileButton() : MenuButton() {
    init();
}

MapBuilderTileButton::MapBuilderTileButton(RpgWorldBuilderScene* gameScene, MapTile* newTile) : MenuButton(gameScene, newTile->textureKey) {
    init(gameScene, newTile);
}

MapBuilderTileButton::MapBuilderTileButton(int elementId, RpgWorldBuilderScene* gameScene, MapTile* newTile) : MenuButton(elementId, gameScene, newTile->textureKey) {
    init(gameScene, newTile);
}

//methods
void MapBuilderTileButton::onClick() {
    scene->placingTile = true;
    scene->placingPortal = false;
    scene->placingBuilding = false;
    scene->tileBeingPlaced = tile;
}

void MapBuilderTileButton::init()
{
    scene = NULL;
    engine = NULL;
    tile = NULL;
    width = -1;
    height = -1;
}

void MapBuilderTileButton::init(RpgWorldBuilderScene* gameScene, MapTile* newTile)
{
    init();
    scene = gameScene;
    engine = gameScene->engine;
    tile = newTile;
    width = engine->screenWidth / WIDTH_ADJUSTOR;
    height = engine->screenHeight / HEIGHT_ADJUSTOR;
}
