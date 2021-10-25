#include "RpgTileGridScene.h"
#include "BaseGameEngine.h"
#include "Player.h"
#include "Rat.h"
#include "RatKing.h"
#include "BlueRat.h"
#include "Soldier.h"
#include "TownsPerson.h"

RpgTileGridScene::RpgTileGridScene() : TileGridScene()
{
    init();
}

RpgTileGridScene::RpgTileGridScene(BaseGameEngine* gameEngine) : TileGridScene((BaseGameEngine*)gameEngine)
{
    init();
}

void RpgTileGridScene::desiredPlayerDrawLocation(int desiredCoords[2])
{
    desiredCoords[0] = (engine->screenWidth - mainCanvasStartX) / 2 + mainCanvasStartX;
    desiredCoords[1] = (engine->screenHeight / 2);
}

void RpgTileGridScene::declareSceneAssets()
{
    TileGridScene::declareSceneAssets();
    //tile textures
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

    //UI textures
    texturesToLoad.insert({ BUTTON_BACKGROUND, "images/buttonBackground.png" });
    //player textures
    //movement
    texturesToLoad.insert({ PLAYER_IDLE_UP_LEFT_SHEET, "images/playerIdleUpLeft.png" });
    texturesToLoad.insert({ PLAYER_IDLE_UP_SHEET, "images/playerIdleUp2.png" });
    texturesToLoad.insert({ PLAYER_IDLE_UP_RIGHT_SHEET, "images/playerIdleUpRight.png" });
    texturesToLoad.insert({ PLAYER_IDLE_RIGHT_SHEET, "images/playerIdleRight2.png" });
    texturesToLoad.insert({ PLAYER_IDLE_DOWN_RIGHT_SHEET, "images/playerIdleDownRight.png" });
    texturesToLoad.insert({ PLAYER_IDLE_DOWN_SHEET, "images/playerIdleDown2.png" });
    texturesToLoad.insert({ PLAYER_IDLE_DOWN_LEFT_SHEET, "images/playerIdleDownLeft.png" });
    texturesToLoad.insert({ PLAYER_IDLE_LEFT_SHEET, "images/playerIdleLeft2.png" });
    texturesToLoad.insert({ PLAYER_MOVE_DOWN_SHEET, "images/playerMoveDown2.png" });
    texturesToLoad.insert({ PLAYER_MOVE_UP_SHEET, "images/playerMoveUp2.png" });
    texturesToLoad.insert({ PLAYER_MOVE_RIGHT_SHEET, "images/playerMoveRight2.png" });
    texturesToLoad.insert({ PLAYER_MOVE_LEFT_SHEET, "images/playerMoveLeft2.png" });
    //attack
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_SHEET, "images/basicMeleeAttack2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_DOWN_SHEET, "images/basicMeleeAttackDown2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_UP_SHEET, "images/basicMeleeAttackUp.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_LEFT_SHEET, "images/baiscMeleeAttackLeft.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_RIGHT_SHEET, "images/basicMeleeAttackRight2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_UP_LEFT_SHEET, "images/basicMeleeAttackUp.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_UP_RIGHT_SHEET, "images/basicMeleeAttackUp.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_DOWN_LEFT_SHEET, "images/basicMeleeAttackDown2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_DOWN_RIGHT_SHEET, "images/basicMeleeAttackDown2.png" });
    //enemy textures
    texturesToLoad.insert({ RAT_IDLE_DOWN, "images/ratIdleDown.png" });
    texturesToLoad.insert({ RAT_IDLE_LEFT, "images/ratIdleLeft.png" });
    texturesToLoad.insert({ RAT_IDLE_RIGHT, "images/ratIdleRight.png" });
    texturesToLoad.insert({ RAT_IDLE_UP, "images/ratIdleUp.png" });
    texturesToLoad.insert({ BLUE_RAT_IDLE_DOWN, "images/SkeletonDown.png" });
    //texturesToLoad.insert({ RAT_KING_IDLE_DOWN, "images/RatKing2.png" });
    texturesToLoad.insert({ RAT_KING_IDLE_DOWN, "images/skeletonKing.png" });
    //townsperson textures
    texturesToLoad.insert({ MAC_WIZ_IDLE_DOWN, "images/MacWiz2.png" });
    //item textures
    texturesToLoad.insert({ ITEM_SHORT_SWORD, "images/itemSword.png" });
    texturesToLoad.insert({ ITEM_CLUB, "images/club.png" });
    texturesToLoad.insert({ ITEM_MACE, "images/mace.png" });
    texturesToLoad.insert({ ITEM_RAG_HAT, "images/RagHat.png" });
    texturesToLoad.insert({ ITEM_RAG_BODY, "images/RagBody.png" });
    texturesToLoad.insert({ ITEM_RAG_PANTS, "images/RagPants.png" });
    texturesToLoad.insert({ ITEM_RAG_GLOVES, "images/RagGloves.png" });
    texturesToLoad.insert({ ITEM_RAG_BOOTS, "images/RagBoots.png" });
    texturesToLoad.insert({ ITEM_LONG_SWORD, "images/longSword.png" });
    texturesToLoad.insert({ ITEM_LINEN_HAT, "images/LinenHat.png" });
    texturesToLoad.insert({ ITEM_LINEN_BODY, "images/LinenBody.png" });
    texturesToLoad.insert({ ITEM_LINEN_PANTS, "images/LinenPants.png" });
    texturesToLoad.insert({ ITEM_LINEN_GLOVES, "images/LinenGloves.png" });
    texturesToLoad.insert({ ITEM_LINEN_BOOTS, "images/LinenBoots.png" });
}

void RpgTileGridScene::setUpScene()
{
    createTiles();
    TileGridScene::setUpScene();
    zonePortalImages.push_back(ENCAMPMENT);
    zonePortalImages.push_back(BLANK_PORTAL);
    zonePortalImages.push_back(PORTAL_CAVE_HILL);
    zonePortalImages.push_back(CAVE_STAIRS_UP);
}

void RpgTileGridScene::handleInput()
{
    TileGridScene::handleInput();
}

void RpgTileGridScene::sceneLogic()
{
    TileGridScene::sceneLogic();
    updateCombatMessages();
}

void RpgTileGridScene::renderScene()
{
    TileGridScene::renderScene();
    drawCombatMessages();
}

void RpgTileGridScene::addCombatMessage(std::string text, int tileX, int tileY)
{
    combatMessages.push_back(CombatText(text, tileX, tileY));
}

void RpgTileGridScene::addCombatMessage(std::string text, int tileX, int tileY, int duration)
{
    combatMessages.push_back(CombatText(text, tileX, tileY, duration));
}

void RpgTileGridScene::addCombatMessage(std::string text, SDL_Color colour, int tileX, int tileY)
{
    combatMessages.push_back(CombatText(text, colour, tileX, tileY));
}

void RpgTileGridScene::addCombatMessage(std::string text, SDL_Color colour, int tileX, int tileY, int duration) {
    combatMessages.push_back(CombatText(text, colour, tileX, tileY, duration));
}

void RpgTileGridScene::addDelayedCombatMessage(int delay, std::string text, int tileX, int tileY) {
    combatMessages.push_back(CombatText(delay, text, tileX, tileY));
}

void RpgTileGridScene::addDelayedCombatMessage(int delay, std::string text, int tileX, int tileY, int duration) {
    combatMessages.push_back(CombatText(delay, text, tileX, tileY, duration));
}

void RpgTileGridScene::addDelayedCombatMessage(int delay, std::string text, SDL_Color colour, int tileX, int tileY) {
    combatMessages.push_back(CombatText(delay, text, colour, tileX, tileY));
}

void RpgTileGridScene::addDelayedCombatMessage(int delay, std::string text, SDL_Color colour, int tileX, int tileY, int duration) {
    combatMessages.push_back(CombatText(delay, text, colour, tileX, tileY, duration));
}

int RpgTileGridScene::getTeamStatus(int unitTeam, int otherUnitTeam)
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

RpgUnit* RpgTileGridScene::getUnitAtLocation(int zoneId, int x, int y)
{
    return (RpgUnit*)TileGridScene::getUnitAtLocation(zoneId, x, y);
}

bool RpgTileGridScene::buildingCanBePlacedAtLocation(Building* building, ZoneMap* zoneMap, int xpos, int ypos)
{
    bool buildingCanBePlaced = true;
    for (int x = 0; x < building->tileMap.size(); x++)
    {
        for (int y = 0; y < building->tileMap[x].size(); y++) {
            int xToCheck = xpos + x;
            int yToCheck = ypos + y;
            if (xToCheck < 0 || xToCheck >= zoneMap->tileMap[y].size() || yToCheck < 0 || yToCheck >= zoneMap->tileMap.size())
            {
                return false;
            }
            //if (!mapTiles[zoneMap->tileMap[yToCheck][xToCheck]].passable)
            if (!zoneMap->isTilePassable(this, xToCheck, yToCheck))
            {
                return false;
            }
        }
    }
    return buildingCanBePlaced;
}

bool RpgTileGridScene::buildingCanBePlacedAtLocation(Building* building, ZoneMap* zoneMap, Location* location)
{
    return buildingCanBePlacedAtLocation(building, zoneMap, location->x, location->y);
}

void RpgTileGridScene::loadZones()
{
    //load zones from file
    SaveFile zonesFile = SaveFile("zones.txt");
    zonesFile.loadFile();
    for (auto zone : zonesFile.objects) {
        ZoneMap* newZone = new ZoneMap(zone.rawString, this);
        newZone->setupGraph(this);
        zones[newZone->id] = newZone;
        if (newZone->id >= nextZoneId)
        {
            nextZoneId = newZone->id + 1;
        }
        for (auto* unit : newZone->units)
        {
            if (((RpgUnit*)unit)->assignedToBuildingId != -1) {
                for (auto building : newZone->buildings) {
                    if (building->id == ((RpgUnit*)unit)->assignedToBuildingId)
                    {
                        building->assignUnit((RpgUnit*)unit);
                    }
                }
            }
        }
    }
    currentZone = zones[0];
    xOffset = 0;
    yOffset = 0;
}

RpgUnit* RpgTileGridScene::createUnitAtLocation(int zoneId, int unitType, int x, int y)
{
    RpgUnit* createdUnit;
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
        createdUnit = new TownsPerson(zoneId, TOWNSPERSON, this, x, y);
        break;
    default:
        createdUnit = NULL;
        break;
    }

    zones[zoneId]->addUnitToLocation(createdUnit, x, y);
    return createdUnit;
}

RpgUnit* RpgTileGridScene::createUnitAtLocation(ZoneMap* zone, int unitType, int x, int y)
{
    RpgUnit* createdUnit;
    switch (unitType)
    {
    case PLAYER:
        createdUnit = new Player(zone->id, PLAYER, this, x, y);
        break;
    case RAT:
        createdUnit = new Rat(zone->id, RAT, this, x, y);
        break;
    case RAT_KING:
        createdUnit = new RatKing(zone->id, RAT_KING, this, x, y);
        break;
    case BLUE_RAT:
        createdUnit = new BlueRat(zone->id, BLUE_RAT, this, x, y);
        break;
    case SOLDIER:
        createdUnit = new Soldier(zone->id, SOLDIER, this, x, y);
        break;
    case TOWNSPERSON:
        createdUnit = new TownsPerson(zone->id, TOWNSPERSON, this, x, y);
        break;
    default:
        createdUnit = new RpgUnit();
        break;
    }
    createdUnit->id = getUniqueUnitId();
    zone->addUnitToLocation(createdUnit, x, y);
    return createdUnit;
}

Building* RpgTileGridScene::createBuildingAtLocation(int zoneId, int buildingType, int direction, int x, int y)
{
    Building* createdBuilding;
    switch (buildingType)
    {
    case BUILDING_ITEM_SHOP:
        createdBuilding = createNewBuilding(buildingType, direction);
        createdBuilding->assignUnit(createUnitAtLocation(zoneId, TOWNSPERSON, x + 3, y + 2));
        break;
    default:
        createdBuilding = nullptr;
        break;
    }
    zones[zoneId]->addBuildingToLocation(createdBuilding, x, y);
    return createdBuilding;
}

Building* RpgTileGridScene::createBuildingAtLocation(ZoneMap* zone, int buildingType, int direction, int x, int y)
{
    Building* createdBuilding;
    switch (buildingType)
    {
    case BUILDING_ITEM_SHOP:
        createdBuilding = createNewBuilding(buildingType, direction);
        createdBuilding->assignUnit(createUnitAtLocation(zone, TOWNSPERSON, x + 3, y + 2));
        break;
    default:
        createdBuilding = nullptr;
        break;
    }
    zone->addBuildingToLocation(createdBuilding, x, y);
    return createdBuilding;
}

void RpgTileGridScene::createTiles()
{
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
}

void RpgTileGridScene::init()
{
    player = nullptr;
}

void RpgTileGridScene::drawCombatMessages()
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

void RpgTileGridScene::updateCombatMessages() {
    for (size_t i = 0; i < combatMessages.size(); i++)
    {
        combatMessages[i].tickCount++;
    }
    combatMessages.erase(std::remove_if(begin(combatMessages), end(combatMessages), [](CombatText const& u)
        {
            return u.tickCount >= u.duration;
        }), end(combatMessages));
}