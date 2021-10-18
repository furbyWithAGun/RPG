#pragma once
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