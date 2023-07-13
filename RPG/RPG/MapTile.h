#pragma once

enum MAP_TILE_SAVE_ATTRIBUTES {
    MAP_TILE_PASSABLE,
    MAP_TILE_TEXTURE_KEY,
    MAP_TILE_WIDTH,
    MAP_TILE_HEIGHT,
    NUM_MAP_TILE_SAVE_ATTRIBUTES
};

enum MAP_TILE_PASSABLE {
    UNPASSABLE,
    UNIT_PASSABLE,
    PROJECTILE_PASSABLE
};

class MapTile
{
public:
    //attributes
    int passable;
    int textureKey;
    int width;
    int height;

    //constructor
    MapTile(int tileIsPassable, int tileTextureKey);
    MapTile(int tileIsPassable, int tileTextureKey, int newWidth, int newHeight);
    MapTile();

    // deconstructor
    ~MapTile();

    //methods

private:
    void init();
};