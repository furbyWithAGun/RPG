#pragma once

class RpgTileGridScene;
class ZoneMap;

class RpgTown
{
public:
    RpgTown();
    RpgTown(RpgTileGridScene* gameScene);
    RpgTown(RpgTileGridScene* gameScene, int zoneMapId);

private:
    //attributes
    RpgTileGridScene* scene;
    ZoneMap* townZoneMap;
    
    //methods
    void init();
};

