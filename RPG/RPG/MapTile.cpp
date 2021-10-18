#include "MapTile.h"

MapTile::MapTile() {
    init();
}

MapTile::MapTile(bool tileIsPassable, int tileTextureKey) {
    init();
    passable = tileIsPassable;
    textureKey = tileTextureKey;
}

MapTile::MapTile(bool tileIsPassable, int tileTextureKey, int newWidth, int newHeight) {
    init();
    passable = tileIsPassable;
    textureKey = tileTextureKey;
    width = newWidth;
    height = newHeight;
}

MapTile::~MapTile() {
    passable = false;
    textureKey = 0;
}

void MapTile::init()
{
    passable = false;
    textureKey = 0;
    width = 0;
    height = 0;
}
