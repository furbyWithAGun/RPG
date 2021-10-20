#pragma once
#include "GameScene.h"
#include "MapTile.h"
#include "ZoneMap.h"
#include "GameMenu.h"
#include <deque>


class BaseGameEngine;
class Unit;
class DooDad;


class TileGridScene : public GameScene
{
public:
    //attributes
    int mainCanvasStartX;
    int xOffset, yOffset;
    std::unordered_map<int, ZoneMap*> zones;
    ZoneMap* currentZone;
    std::unordered_map<int, MapTile> mapTiles;
    std::vector<int> zonePortalImages;
    int tileHeight;
    int tileWidth;
    int nextZoneId;
    std::deque<Unit*> unitsNeedingPath;

    //constructor
    TileGridScene();
    TileGridScene(BaseGameEngine* gameEngine);

    //methods
    void coordsFromTileIndex(int x, int y, int returnCoords[2]);
    virtual void declareSceneAssets() override;
    virtual void setUpScene() override;
    virtual void loadZones();
    virtual void loadZone(int zoneId);
    virtual void createNewZone();
    void deleteZone(int zoneId);
    void saveZones();
    void handleInput() override;
    void sceneLogic() override;
    void renderScene() override;
    Unit* getUnitAtLocation(int zoneId, int x, int y);
    bool isTilePassable(int zoneId, int x, int y);
    ZonePortal* getPortalAtLocation(ZoneMap* zoneMap, int xpos, int ypos);
    DooDad* getDooDadAtLocation(ZoneMap* zoneMap, int xpos, int ypos);
    void removePortalAtLocation(int zoneId, int xpos, int ypos);
    void removeUnit(Unit* unit);
    void addItemsToMap(int zone, int x, int y, std::vector<Item*> items);
    bool coordsAreOnDisplayedMapTile(int x, int y);
    bool tileCoordsAreOnDisplayedMapTile(int x, int y);
    

protected:
    //attributes
    int desiredTilesAcross;
    int desiredTilesDown;
    
    //methods
    void getTileIndexFromScreenCoords(int x, int y, int tileIndices[2]);
    bool tileCoordsAreDisplayedMapTile(int x, int y);
    //virtual Unit* createUnitAtLocation(int zoneId, int unitType, int x, int y);
    

private:
    //methods
    virtual void createTiles();
    void init();
};