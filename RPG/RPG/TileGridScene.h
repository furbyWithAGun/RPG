#pragma once
#include "GameScene.h"
#include "MapTile.h"
#include "ZoneMap.h"
#include <deque>


class BaseGameEngine;
class Unit;
class DooDad;

//constants
const int DEFAULT_TILE_HEIGHT = 50;
const int DEFAULT_TILE_WIDTH = 50;
const double LEFT_MENU_SIZE = 0.1;
const int DEFAULT_DESIRED_TILES_DOWN = 15;
const int DEFAULT_DESIRED_TILES_ACROSS = 25;
//const int DEFAULT_DESIRED_TILES_ACROSS = 30;


class TileGridScene : public GameScene
{
public:
    //attributes
    int mainCanvasStartX;
    int xOffset, yOffset;
    ZoneMap* currentZone;
    std::unordered_map<int, MapTile> mapTiles;
    std::vector<int> zonePortalImages;
    int tileHeight;
    int tileWidth;
    int nextZoneId;
    std::deque<Unit*> unitsNeedingPath;
    int desiredTilesAcross;
    int desiredTilesDown;
    //pathfinding rates
    int getNewPathFailLimit;
    int processPathFailLimit;
    bool updatingUnits;

    //constructor
    TileGridScene();
    TileGridScene(BaseGameEngine* gameEngine);

    //methods
    void coordsFromTileIndex(int x, int y, int returnCoords[2]);
    virtual void declareSceneAssets() override;
    virtual void setUpScene() override;
    virtual void loadZones();
    virtual void setCurrentZone(int zoneId);
    virtual void createNewZone();
    void deleteZone(int zoneId);
    void saveZones(std::string saveName);
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
    void getTileIndexFromScreenCoords(int x, int y, int tileIndices[2]);
    void addZone(ZoneMap* newZone);
    void addZone(int zoneId, ZoneMap* newZone);
    std::unordered_map<int, ZoneMap*> getZones();
    ZoneMap* getZone(int zoneId);
    ZoneMap* getZoneByName(std::string zoneName);
    bool isUnitToBeDestroyed(Unit* unit);
    bool isDooDadToBeDestroyed(DooDad* dooDad);
    void addUnitToDestroy(Unit* unit);
    void addDooDadToDestroy(DooDad* dooDad);
    

protected:
    //attributes
    std::vector<Unit*> unitsToDestroy;
    std::vector<DooDad*> dooDadsToDestroy;

    //methods
    bool tileCoordsAreDisplayedMapTile(int x, int y);
    //virtual Unit* createUnitAtLocation(int zoneId, int unitType, int x, int y);
    

private:
    //attributes
    std::unordered_map<int, ZoneMap*> zones;
    //methods
    virtual void createTiles();
    void init();
};