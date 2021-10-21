#pragma once

enum MAP_TILE_SAVE_ATTRIBUTES {
    MAP_TILE_PASSABLE,
    MAP_TILE_TEXTURE_KEY,
    MAP_TILE_WIDTH,
    MAP_TILE_HEIGHT,
    NUM_MAP_TILE_SAVE_ATTRIBUTES
};

class MapTile
{
public:
    //attributes
    bool passable;
    int textureKey;
    int width;
    int height;

    //constructor
    MapTile(bool tileIsPassable, int tileTextureKey);
    MapTile(bool tileIsPassable, int tileTextureKey, int newWidth, int newHeight);
    MapTile();

    // deconstructor
    ~MapTile();

    //methods

private:
    void init();
};