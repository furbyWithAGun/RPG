#include "TileGridScene.h"
#include "BaseGameEngine.h"
#include "Unit.h"

//constants
const int DEFAULT_TILE_HEIGHT = 50;
const int DEFAULT_TILE_WIDTH = 50;
const double LEFT_MENU_SIZE = 0.1;
//const int DEFAULT_DESIRED_TILES_DOWN = 15;
const int DEFAULT_DESIRED_TILES_DOWN = 12;
const int DEFAULT_DESIRED_TILES_ACROSS = 20;
//const int DEFAULT_DESIRED_TILES_ACROSS = 30;

//constructors
TileGridScene::TileGridScene() : GameScene() {
    init();
}

TileGridScene::TileGridScene(BaseGameEngine* gameEngine) : GameScene((BaseGameEngine*) gameEngine) {
    init();
}

void TileGridScene::init() {
    tileHeight = DEFAULT_TILE_HEIGHT;
    tileWidth = DEFAULT_TILE_WIDTH;
    xOffset = 0;
    yOffset = 0;
    mainCanvasStartX = engine->screenWidth * LEFT_MENU_SIZE;
    desiredTilesAcross = DEFAULT_DESIRED_TILES_ACROSS;
    desiredTilesDown = DEFAULT_DESIRED_TILES_DOWN;
    nextZoneId = 0;
}

void TileGridScene::declareSceneAssets()
{
    
}

void TileGridScene::setUpScene()
{
    loadZones();
}

void TileGridScene::loadZones()
{
    ////load zones from file
    //SaveFile zonesFile = SaveFile("zones.txt");
    //zonesFile.loadFile();
    //for (auto zone : zonesFile.objects) {
    //    ZoneMap* newZone = new ZoneMap(zone.rawString, this);
    //    newZone->setupGraph(this);
    //    zones[newZone->id] = newZone;
    //    if (newZone->id >= nextZoneId)
    //    {
    //        nextZoneId = newZone->id + 1;
    //    }
    //}
    //currentZone = zones[0];
    //xOffset = 0;
    //yOffset = 0;
}

void TileGridScene::loadZone(int zoneId)
{
    currentZone = zones[zoneId];
    clearCommandQueue();
}

void TileGridScene::createNewZone()
{
    currentZone = new ZoneMap();
    currentZone->id = nextZoneId;
    currentZone->zoneName = std::to_string(currentZone->id);
    nextZoneId++;
}

void TileGridScene::deleteZone(int zoneId)
{
    delete zones[zoneId];
    zones.erase(zoneId);
}

void TileGridScene::saveZones()
{
    SaveFile zonesFile = SaveFile("zones.txt");
    for (auto zone : zones) {
        if (zone.second->zoneName.length() > 0)
        {
            zonesFile.addSaveObjectString(zone.second->toSaveString());
        }
    }
    zonesFile.saveFile();
}

void TileGridScene::handleInput()
{
    GameScene::handleInput();
}

void TileGridScene::sceneLogic()
{
    for (auto zone : zones)
    {
        zone.second->update();
    }
}

void TileGridScene::renderScene()
{
    currentZone->draw(this);
    //cover Left side
    engine->renderRectangle(0, 0, mainCanvasStartX, engine->screenHeight, 0, 0, 0);
}


void TileGridScene::coordsFromTileIndex(int x, int y, int returnCoords[2]) {
    returnCoords[0] = x * tileWidth + mainCanvasStartX + xOffset;
    returnCoords[1] = y * tileHeight + yOffset;
}

ZonePortal* TileGridScene::getPortalAtLocation(ZoneMap* zoneMap, int xpos, int ypos)
{
    return zoneMap->getPortalAtLocation(xpos, ypos);
}

DooDad* TileGridScene::getDooDadAtLocation(ZoneMap* zoneMap, int xpos, int ypos)
{
    return zoneMap->getDooDadAtLocation(xpos, ypos);
}

void TileGridScene::removePortalAtLocation(int zoneId, int xpos, int ypos)
{
    zones[zoneId]->removePortalAtLocation(xpos, ypos);
}


void TileGridScene::removeUnit(Unit* unit)
{

}

void TileGridScene::addItemsToMap(int zone, int x, int y, std::vector<Item*> items)
{
    for (auto item : items)
    {
        zones[zone]->itemMap[x][y].push_back(item);
    }
}

//protected methods
void TileGridScene::getTileIndexFromScreenCoords(int x, int y, int tileIndices[2]) {
    tileIndices[0] = floor(((x - xOffset - mainCanvasStartX)) / tileWidth);
    tileIndices[1] = floor((y - yOffset) / tileHeight);
}


bool TileGridScene::coordsAreOnDisplayedMapTile(int x, int y) {
    int k[2];
    getTileIndexFromScreenCoords(x, y, k);
    return ((mainCanvasStartX <= x) && (k[0] >= 0) && (k[0] < currentZone->tileMap[0].size()) && (k[1] >= 0) && (k[1] < currentZone->tileMap.size()));
}

bool TileGridScene::tileCoordsAreOnDisplayedMapTile(int x, int y) {
    return ((x >= 0) && (x < currentZone->tileMap[0].size()) && (y >= 0) && (y < currentZone->tileMap.size()));
}

bool TileGridScene::tileCoordsAreDisplayedMapTile(int x, int y) {
    return ((x >= 0) && (x < currentZone->tileMap[0].size()) && (y >= 0) && (y < currentZone->tileMap.size()));
}

Unit* TileGridScene::getUnitAtLocation(int zoneId, int x, int y)
{
    return zones[zoneId]->getUnitAtLocation(x, y);
}

//Unit* TileGridScene::createUnitAtLocation(int zoneId, int unitType, int x, int y)
//{
//    return new Unit(zoneId, unitType, this, x, y);
//}

bool TileGridScene::isTilePassable(int zoneId, int x, int y) {
    return zones[zoneId]->isTilePassable(this, x, y);
}

//private methods
void TileGridScene::createTiles() {
    //resize tiles depending on screen size
    int tilesImpliedWidth = engine->screenWidth / desiredTilesAcross;
    int tilesImpliedHeight = engine->screenHeight / desiredTilesDown;
    if (tilesImpliedHeight >= tilesImpliedWidth) {
        tileHeight = tilesImpliedHeight;
        tileWidth = tilesImpliedHeight;
    }
    else {
        tileHeight = tilesImpliedWidth;
        tileWidth = tilesImpliedWidth;
    }
}




