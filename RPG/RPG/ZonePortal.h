#pragma once
#include <string>
#include <vector>
#include "SaveFile.h"

enum ZONE_PORTAL_ATTRIBUTES {
    ZONE_PORTAL_TEXTURE_ID,
    TILE_COORDS,
    EXIT_ZONE_ID,
    EXIT_TILE_COORDS
};

class ZonePortal
{
public:
    //attributes
    int textureId;
    std::vector <int> tileCoords;
    int exitZoneId;
    std::vector <int> exitTileCoords;

    //constructors
    ZonePortal();
    ZonePortal(int newTextureId, std::vector <int> newTileCoords, int newExitZoneId, std::vector <int> newExitTileCoords);
    ZonePortal(SaveObject saveObject);

    //destructor
    ~ZonePortal();

    //methods
    std::string toSaveString();

private:
    //methods
    void init();
};

