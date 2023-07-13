#include "MapTile.h"

MapTile::MapTile() {
    init();
}

MapTile::MapTile(int tileIsPassable, int tileTextureKey) {
    init();
    passable = tileIsPassable;
    textureKey = tileTextureKey;
}

MapTile::MapTile(int tileIsPassable, int tileTextureKey, int newWidth, int newHeight) {
    init();
    passable = tileIsPassable;
    textureKey = tileTextureKey;
    width = newWidth;
    height = newHeight;
}

MapTile::~MapTile() {
    passable = UNPASSABLE;
    textureKey = 0;
}

void MapTile::init()
{
    passable = UNPASSABLE;
    textureKey = 0;
    width = 0;
    height = 0;
}
