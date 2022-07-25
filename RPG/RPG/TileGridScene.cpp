#include "TileGridScene.h"
#include "BaseGameEngine.h"
#include "Unit.h"



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
    getNewPathFailLimit = 3;
    processPathFailLimit = 30;
    TileGridUnitLock = 0;
    updatingUnits = false;
}

void TileGridScene::declareSceneAssets()
{
    
}

void TileGridScene::setUpScene()
{
    loadZones(NEW_GAME_SAVE_FILE);
}

void TileGridScene::setUpScene(std::string saveFile)
{
    loadZones(saveFile);
}

void TileGridScene::loadZones(std::string saveFile)
{
    
}

void TileGridScene::setCurrentZone(int zoneId)
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

void TileGridScene::saveZones(std::string saveName)
{
    //SaveFile zonesFile = SaveFile("zones.txt");
    SaveFile zonesFile = SaveFile(SAVES_FILE_PATH + saveName);
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
    GameScene::sceneLogic();
    for (auto zone : zones)
    {
        zone.second->update();
    }

    SDL_AtomicLock(&TileGridUnitLock);
    for (Unit* unit : currentZone->getUnits()) {
        unit->leftToMoveBuffer = unit->leftToMove;
        unit->tileLocationBuffer->x = unit->tileLocation->x;
        unit->tileLocationBuffer->y = unit->tileLocation->y;
        unit->tileDestinationBuffer->x = unit->tileDestination->x;
        unit->tileDestinationBuffer->y = unit->tileDestination->y;
    }
    setLastTickTimeStampBuffer();
    SDL_AtomicUnlock(&TileGridUnitLock);
}

void TileGridScene::renderScene()
{
    currentZone->draw(this);
    //cover Left side
    engine->renderRectangle(0, 0, mainCanvasStartX, engine->screenHeight, 0, 0, 0);
}


 
void TileGridScene::coordsFromTileIndex(int x, int y, double returnCoords[2]) {
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
        zones[zone]->addItemToLocation(item, x, y);
    }
}

void TileGridScene::getTileIndexFromScreenCoords(int x, int y, double tileIndices[2]) {
    tileIndices[0] = floor(((x - xOffset - mainCanvasStartX)) / tileWidth);
    tileIndices[1] = floor((y - yOffset) / tileHeight);
}

void TileGridScene::addZone(ZoneMap* newZone)
{
    zones[newZone->id] = newZone;
}

void TileGridScene::addZone(int zoneId, ZoneMap* newZone)
{
    newZone->id = zoneId;
    addZone(newZone);
}

std::unordered_map<int, ZoneMap*> TileGridScene::getZones()
{
    return zones;
}

ZoneMap* TileGridScene::getZone(int zoneId)
{
    return zones[zoneId];
}

ZoneMap* TileGridScene::getZoneByName(std::string zoneName)
{
    for (auto zone : zones)
    {
        if (zone.second->zoneName == zoneName) {
            return zone.second;
        }
    }
    return nullptr;
}

bool TileGridScene::isUnitToBeDestroyed(Unit* unit)
{
    for (auto unitToDestroy : unitsToDestroy) {
        if (unitToDestroy == unit)
        {
            return true;
        }
    }
    return false;
}

bool TileGridScene::isDooDadToBeDestroyed(DooDad* dooDad)
{
    for (auto dooDadToDestroy : dooDadsToDestroy) {
        if (dooDadToDestroy == dooDad)
        {
            return true;
        }
    }
    return false;
}

void TileGridScene::addUnitToDestroy(Unit* unit)
{
    if (isUnitToBeDestroyed(unit))
    {
        return;
    }
    unitsToDestroy.push_back(unit);
}

double TileGridScene::getLastTickTimeStampBuffer()
{
    return lastTickTimeStampBuffer;
}

void TileGridScene::setLastTickTimeStampBuffer()
{
    lastTickTimeStampBuffer = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

void TileGridScene::addDooDadToDestroy(DooDad* dooDad)
{
    if (isDooDadToBeDestroyed(dooDad))
    {
        return;
    }
    dooDadsToDestroy.push_back(dooDad);
}


bool TileGridScene::coordsAreOnDisplayedMapTile(int x, int y) {
    double k[2];
    getTileIndexFromScreenCoords(x, y, k);
    return ((mainCanvasStartX <= x) && (k[0] >= 0) && (k[0] < currentZone->tileMap.size()) && (k[1] >= 0) && (k[1] < currentZone->tileMap[0].size()));
}

bool TileGridScene::tileCoordsAreOnDisplayedMapTile(int x, int y) {
    return ((x >= 0) && (x < currentZone->tileMap.size()) && (y >= 0) && (y < currentZone->tileMap[0].size()));
}

bool TileGridScene::tileCoordsAreDisplayedMapTile(int x, int y) {
    return ((x >= 0) && (x < currentZone->tileMap.size()) && (y >= 0) && (y < currentZone->tileMap[0].size()));
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




