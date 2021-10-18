#include "TileGridScene.h"
#include "BaseGameEngine.h"
#include "Unit.h"
#include "Player.h"
#include "Rat.h"
#include "RatKing.h"
#include "BlueRat.h"
#include "Soldier.h"
#include "TownsPerson.h"

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
    texturesToLoad.insert({ WATER, "images/water2.png" });
    texturesToLoad.insert({ TREE, "images/tree2.png" });
    texturesToLoad.insert({ GRASS, "images/grass2.png" });
    texturesToLoad.insert({ MOUNTAIN, "images/mountain2.png" });
    texturesToLoad.insert({ PORTAL_CAVE_HILL, "images/caveEntrance.png" });
    texturesToLoad.insert({ ENCAMPMENT, "images/encampment2.png" });
    texturesToLoad.insert({ BLANK_PORTAL, "images/blank2.png" });
    texturesToLoad.insert({ WOOD_WALL_ONE, "images/woodWallOne2.png" });
    texturesToLoad.insert({ WOOD_WALL_TWO, "images/woodWallTwo2.png" });
    texturesToLoad.insert({ CAVE_FILL, "images/caveFill.png" });
    texturesToLoad.insert({ CAVE_PATH, "images/cavePath.png" });
    texturesToLoad.insert({ CAVE_WALL_TOP, "images/caveWallTop.png" });
    texturesToLoad.insert({ CAVE_WALL_BOTTOM, "images/caveWallBottom.png" });
    texturesToLoad.insert({ CAVE_STAIRS_UP, "images/caveStairsUp.png" });
}

void TileGridScene::setUpScene()
{
    createTiles();
    zonePortalImages.push_back(ENCAMPMENT);
    zonePortalImages.push_back(BLANK_PORTAL);
    zonePortalImages.push_back(PORTAL_CAVE_HILL);
    zonePortalImages.push_back(CAVE_STAIRS_UP);
    loadZones();
    
}

void TileGridScene::loadZones()
{
    //load zones from file
    SaveFile zonesFile = SaveFile("zones.txt");
    zonesFile.loadFile();
    for (auto zone : zonesFile.objects) {
        ZoneMap* newZone = new ZoneMap(zone.rawString);
        newZone->setupGraph(this);
        zones[newZone->id] = newZone;
        if (newZone->id >= nextZoneId)
        {
            nextZoneId = newZone->id + 1;
        }
    }
    currentZone = zones[0];
    xOffset = 0;
    yOffset = 0;
}

void TileGridScene::loadZone(int zoneId)
{
    //loadZones();
    currentZone = zones[zoneId];
    clearCommandQueue();
}

void TileGridScene::createNewZone()
{
    //loadZones();
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
    int numUnits = 0;
    for (auto zone : zones)
    {
        zone.second->update();
        for (auto unit : zone.second->units) {
            numUnits++;
        }
    }
    printf(std::to_string(numUnits).c_str());
    printf("\n");
    updateCombatMessages();
}

void TileGridScene::renderScene()
{
    currentZone->draw(this);
    
    //cover Left side
    engine->renderRectangle(0, 0, mainCanvasStartX, engine->screenHeight, 0, 0, 0);

    drawCombatMessages();
}

void TileGridScene::desiredPlayerDrawLocation(int desiredCoords[2])
{
    
    desiredCoords[0] = (engine->screenWidth - mainCanvasStartX) / 2 + mainCanvasStartX;
    desiredCoords[1] = (engine->screenHeight / 2);
}

void TileGridScene::coordsFromTileIndex(int x, int y, int returnCoords[2]) {
    returnCoords[0] = x * tileWidth + mainCanvasStartX + xOffset;
    returnCoords[1] = y * tileHeight + yOffset;
}

void TileGridScene::addCombatMessage(std::string text, int tileX, int tileY) {
    combatMessages.push_back(CombatText(text, tileX, tileY));
}

void TileGridScene::addCombatMessage(std::string text, int tileX, int tileY, int duration) {
    combatMessages.push_back(CombatText(text, tileX, tileY, duration));
}

void TileGridScene::addCombatMessage(std::string text, SDL_Color colour, int tileX, int tileY) {
    combatMessages.push_back(CombatText(text, colour, tileX, tileY));
}

void TileGridScene::addCombatMessage(std::string text, SDL_Color colour, int tileX, int tileY, int duration) {
    combatMessages.push_back(CombatText(text, colour, tileX, tileY, duration));
}

void TileGridScene::addDelayedCombatMessage(int delay, std::string text, int tileX, int tileY) {
    combatMessages.push_back(CombatText(delay, text, tileX, tileY));
}

void TileGridScene::addDelayedCombatMessage(int delay, std::string text, int tileX, int tileY, int duration) {
    combatMessages.push_back(CombatText(delay, text, tileX, tileY, duration));
}

void TileGridScene::addDelayedCombatMessage(int delay, std::string text, SDL_Color colour, int tileX, int tileY) {
    combatMessages.push_back(CombatText(delay, text, colour, tileX, tileY));
}

void TileGridScene::addDelayedCombatMessage(int delay, std::string text, SDL_Color colour, int tileX, int tileY, int duration) {
    combatMessages.push_back(CombatText(delay, text, colour, tileX, tileY, duration));
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
//
//void TileGridScene::portalUnit(ZonePortal* portal, Unit* unit)
//{
//    //moveUnitTo(unit, portal->exitZoneId, portal->exitTileCoords[0], portal->exitTileCoords[1]);
//    //unit->portalTo(portal->exitZoneId, portal->exitTileCoords[0], portal->exitTileCoords[1]);
//    //remove unit from current zone
//    /*zones[unit->zone]->unitMap[unit->tileLocation->x][unit->tileLocation->y] = nullptr;
//    zones[unit->zone]->unitMap[unit->tileDestination->x][unit->tileDestination->y] = nullptr;
//    auto unitIterator = zones[unit->zone]->units.begin();
//    while (unitIterator != zones[unit->zone]->units.end())
//    {
//        if ((*unitIterator) == unit) {
//            unitIterator = zones[unit->zone]->units.erase(unitIterator);
//            break;
//        }
//        else {
//            unitIterator++;
//        }
//    }*/
//
//    ////add unit to new zone
//    //zones[portal->exitZoneId]->units.push_back(unit);
//
//    ////set units location
//    //unit->zone = portal->exitZoneId;
//    //zones[portal->exitZoneId]->unitEntersTile(unit, portal->exitTileCoords[0], portal->exitTileCoords[1]);
//
//    //if unit if player switch zone
//    if (unit == player)
//    {
//        //unit->health = unit->maxHealth;
//        loadZone(portal->exitZoneId);
//    }
//}


//void TileGridScene::moveUnitTo(Unit* unit, int zone, int x, int y)
//{
//    //remove unit from current zone
//    zones[unit->zone]->unitMap[unit->tileLocation->x][unit->tileLocation->y] = nullptr;
//    zones[unit->zone]->unitMap[unit->tileDestination->x][unit->tileDestination->y] = nullptr;
//    auto unitIterator = zones[unit->zone]->units.begin();
//    while (unitIterator != zones[unit->zone]->units.end())
//    {
//        if ((*unitIterator) == unit) {
//            unitIterator = zones[unit->zone]->units.erase(unitIterator);
//            break;
//        }
//        else {
//            unitIterator++;
//        }
//    }
//    //add unit to new zone
//    zones[zone]->units.push_back(unit);
//
//    //set units location
//    unit->zone = zone;
//    zones[zone]->unitEntersTile(unit, x, y);
//
//}

int TileGridScene::getTeamStatus(int unitTeam, int otherUnitTeam)
{
    if (unitTeam == otherUnitTeam)
    {
        return ALLY;
    }
    if (teamRelations[unitTeam].find(otherUnitTeam) == teamRelations[unitTeam].end())
    {
        return UNKNOWN_DISPOSITION;
    }
    return teamRelations[unitTeam][otherUnitTeam];
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
    //return ((mainCanvasStartX <= x) && (x >= 0) && (x < currentZone->tileMap[0].size()) && (y >= 0) && (y < currentZone->tileMap.size()));
    return ((x >= 0) && (x < currentZone->tileMap[0].size()) && (y >= 0) && (y < currentZone->tileMap.size()));
}

bool TileGridScene::tileCoordsAreDisplayedMapTile(int x, int y) {
    return ((x >= 0) && (x < currentZone->tileMap[0].size()) && (y >= 0) && (y < currentZone->tileMap.size()));
}

Unit* TileGridScene::getUnitAtLocation(int zoneId, int x, int y)
{
    return zones[zoneId]->getUnitAtLocation(x, y);
}

Unit* TileGridScene::createUnitAtLocation(int zoneId, int unitType, int x, int y)
{
    Unit* createdUnit;
    switch (unitType)
    {
    case PLAYER:
        createdUnit = new Player(zoneId, PLAYER, this, x, y);
        break;
    case RAT:
        createdUnit = new Rat(zoneId, RAT, this, x, y);
        break;
    case RAT_KING:
        createdUnit = new RatKing(zoneId, RAT_KING, this, x, y);
        break;
    case BLUE_RAT:
        createdUnit = new BlueRat(zoneId, BLUE_RAT, this, x, y);
        break;
    case SOLDIER:
        createdUnit = new Soldier(zoneId, SOLDIER, this, x, y);
        break;
    case TOWNSPERSON:
        createdUnit = new TownsPerson(zoneId, SOLDIER, this, x, y);
        break;
    default:
        createdUnit = NULL;
        break;
    }

    zones[zoneId]->addUnitToLocation(createdUnit, x, y);
    return createdUnit;
}

bool TileGridScene::isTilePassable(int zoneId, int x, int y) {
    return zones[zoneId]->isTilePassable(this, x, y);
}

//private methods
void TileGridScene::createTiles() {
    //create the different tiles
    mapTiles[GRASS] = MapTile(true, GRASS);
    mapTiles[TREE] = MapTile(false, TREE);
    mapTiles[WATER] = MapTile(false, WATER);
    mapTiles[MOUNTAIN] = MapTile(false, MOUNTAIN);
    mapTiles[WOOD_WALL_ONE] = MapTile(false, WOOD_WALL_ONE);
    mapTiles[WOOD_WALL_TWO] = MapTile(false, WOOD_WALL_TWO);
    mapTiles[CAVE_FILL] = MapTile(false, CAVE_FILL);
    mapTiles[CAVE_PATH] = MapTile(true, CAVE_PATH);
    mapTiles[CAVE_WALL_TOP] = MapTile(false, CAVE_WALL_TOP);
    mapTiles[CAVE_WALL_BOTTOM] = MapTile(false, CAVE_WALL_BOTTOM);

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
    for (auto tile: mapTiles)
    {
        //SDL_Resize();
    }
}


void TileGridScene::drawCombatMessages()
{
    int displayCoords[2];
    for (CombatText combatText : combatMessages)
    {
        if (combatText.tickCount >= combatText.delay)
        {
            coordsFromTileIndex(combatText.tileX, combatText.tileY, displayCoords);
            engine->renderText(combatText.text, displayCoords[0] + (tileWidth / 4), displayCoords[1] + (tileHeight / 4) - (combatText.tickCount - combatText.delay) * combatText.ySpeed, combatText.colour);
        }
    }
}

void TileGridScene::updateCombatMessages() {
    for (size_t i = 0; i < combatMessages.size(); i++)
    {
        combatMessages[i].tickCount++;
    }
    combatMessages.erase(std::remove_if(begin(combatMessages), end(combatMessages), [](CombatText const& u)
        {
            return u.tickCount >= u.duration;
        }), end(combatMessages));
}

