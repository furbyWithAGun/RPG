#include "RpgTileGridScene.h"
#include "BaseGameEngine.h"
#include "Player.h"
#include "Rat.h"
#include "RatKing.h"
#include "WhiteRat.h"
#include "Soldier.h"
#include "TownsPerson.h"
#include "Skeleton.h"
#include "SkeletonKing.h"

const int SCROLL_SPEED = 4;

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
    texturesToLoad.insert({ TREE, "images/treeTim.png" });
    texturesToLoad.insert({ TREE_2, "images/treeTim2.png" });
    texturesToLoad.insert({ TREE_3, "images/treeTim3.png" });
    //texturesToLoad.insert({ TREE, "images/tree2.png" });
    texturesToLoad.insert({ TEXTURE_TREE_STUMP, "images/treeStumpTim.png" });
    //texturesToLoad.insert({ GRASS, "images/tallGrass.png" });
    texturesToLoad.insert({ GRASS, "images/grass2.png" });
    texturesToLoad.insert({ MOUNTAIN, "images/mountain2.png" });
    texturesToLoad.insert({ PORTAL_CAVE_HILL, "images/caveEntrance.png" });
    texturesToLoad.insert({ ENCAMPMENT, "images/encampment2.png" });
    texturesToLoad.insert({ BLANK_PORTAL, "images/blank.png" });
    texturesToLoad.insert({ WOOD_WALL_ONE, "images/woodWallOne2.png" });
    texturesToLoad.insert({ WOOD_WALL_TWO, "images/woodWallTwo2.png" });
    texturesToLoad.insert({ CAVE_FILL, "images/caveFill.png" });
    texturesToLoad.insert({ CAVE_PATH, "images/cavePath.png" });
    texturesToLoad.insert({ CAVE_WALL_TOP, "images/caveWallTop.png" });
    texturesToLoad.insert({ CAVE_WALL_BOTTOM, "images/caveWallBottom.png" });
    texturesToLoad.insert({ CAVE_STAIRS_UP, "images/caveStairsUp.png" });
    texturesToLoad.insert({ TILE_DIRT_ROAD, "images/DirtRoadFilled.png" });

    //UI textures
    texturesToLoad.insert({ BUTTON_BACKGROUND, "images/buttonBackground.png" });
    //texturesToLoad.insert({ TEXTURE_EQUIPPED_MENU_SILHOUETTE, "images/silhouetteGrey.png" });
    texturesToLoad.insert({ TEXTURE_EQUIPPED_MENU_SILHOUETTE, "images/silhouette.png" });
    //player textures
    //movement
    texturesToLoad.insert({ PLAYER_IDLE_UP_LEFT_SHEET, "images/playerIdleUp2.png" });
    texturesToLoad.insert({ PLAYER_IDLE_UP_SHEET, "images/playerIdleUp2.png" });
    texturesToLoad.insert({ PLAYER_IDLE_UP_RIGHT_SHEET, "images/playerIdleUp2.png" });
    texturesToLoad.insert({ PLAYER_IDLE_RIGHT_SHEET, "images/playerIdleRight2.png" });
    texturesToLoad.insert({ PLAYER_IDLE_DOWN_RIGHT_SHEET, "images/playerIdleDown2.png" });
    texturesToLoad.insert({ PLAYER_IDLE_DOWN_SHEET, "images/playerIdleDown2.png" });
    texturesToLoad.insert({ PLAYER_IDLE_DOWN_LEFT_SHEET, "images/playerIdleDown2.png" });
    texturesToLoad.insert({ PLAYER_IDLE_LEFT_SHEET, "images/playerIdleLeft2.png" });
    texturesToLoad.insert({ PLAYER_MOVE_DOWN_SHEET, "images/playerMoveDown2.png" });
    texturesToLoad.insert({ PLAYER_MOVE_UP_SHEET, "images/playerMoveUp2.png" });
    texturesToLoad.insert({ PLAYER_MOVE_RIGHT_SHEET, "images/playerMoveRight2.png" });
    texturesToLoad.insert({ PLAYER_MOVE_LEFT_SHEET, "images/playerMoveLeft2.png" });
    //attack
    //texturesToLoad.insert({ BASIC_MELEE_ATTACK_SHEET, "images/playerAttack2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_DOWN_SHEET, "images/playerAttackDown2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_UP_SHEET, "images/playerAttackUp2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_LEFT_SHEET, "images/playerAttackLeft2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_RIGHT_SHEET, "images/playerAttackRight2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_UP_LEFT_SHEET, "images/playerAttackUp2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_UP_RIGHT_SHEET, "images/playerAttackUp2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_DOWN_LEFT_SHEET, "images/playerAttackDown2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_DOWN_RIGHT_SHEET, "images/playerAttackDown2.png" });
    /*texturesToLoad.insert({ BASIC_MELEE_ATTACK_SHEET, "images/basicMeleeAttack2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_DOWN_SHEET, "images/basicMeleeAttackDown2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_UP_SHEET, "images/basicMeleeAttackUp2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_LEFT_SHEET, "images/baiscMeleeAttackLeft.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_RIGHT_SHEET, "images/basicMeleeAttackRight2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_UP_LEFT_SHEET, "images/basicMeleeAttackUp.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_UP_RIGHT_SHEET, "images/basicMeleeAttackUp.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_DOWN_LEFT_SHEET, "images/basicMeleeAttackDown2.png" });
    texturesToLoad.insert({ BASIC_MELEE_ATTACK_DOWN_RIGHT_SHEET, "images/basicMeleeAttackDown2.png" });*/
    //enemy textures
    //Rat
    texturesToLoad.insert({ RAT_IDLE_DOWN, "images/ratIdleDown.png" });
    texturesToLoad.insert({ RAT_IDLE_LEFT, "images/ratIdleLeft.png" });
    texturesToLoad.insert({ RAT_IDLE_RIGHT, "images/ratIdleRight.png" });
    texturesToLoad.insert({ RAT_IDLE_UP, "images/ratIdleUp.png" });
    texturesToLoad.insert({ RAT_MOVE_DOWN, "images/ratMoveDown.png" });
    texturesToLoad.insert({ RAT_MOVE_UP, "images/ratMoveUp.png" });
    texturesToLoad.insert({ RAT_MOVE_LEFT, "images/ratMoveLeft.png" });
    texturesToLoad.insert({ RAT_MOVE_RIGHT, "images/ratMoveRight.png" });
    texturesToLoad.insert({ RAT_ATTACK_UP, "images/ratAttackUp.png" });
    texturesToLoad.insert({ RAT_ATTACK_DOWN, "images/ratAttackDown.png" });
    texturesToLoad.insert({ RAT_ATTACK_LEFT, "images/ratAttackLeft.png" });
    texturesToLoad.insert({ RAT_ATTACK_RIGHT, "images/ratAttackRight.png" });
    //White Rat
    texturesToLoad.insert({ WHITE_RAT_IDLE_DOWN, "images/whiteRatIdleDown.png" });
    texturesToLoad.insert({ WHITE_RAT_IDLE_LEFT, "images/whiteRatIdleLeft.png" });
    texturesToLoad.insert({ WHITE_RAT_IDLE_RIGHT, "images/whiteRatIdleRight.png" });
    texturesToLoad.insert({ WHITE_RAT_IDLE_UP, "images/whiteRatIdleUp.png" });
    texturesToLoad.insert({ WHITE_RAT_MOVE_DOWN, "images/whiteRatMoveDown.png" });
    texturesToLoad.insert({ WHITE_RAT_MOVE_UP, "images/whiteRatMoveUp.png" });
    texturesToLoad.insert({ WHITE_RAT_MOVE_LEFT, "images/whiteRatMoveLeft.png" });
    texturesToLoad.insert({ WHITE_RAT_MOVE_RIGHT, "images/whiteRatMoveRight.png" });
    texturesToLoad.insert({ WHITE_RAT_ATTACK_UP, "images/whiteRatAttackUp.png" });
    texturesToLoad.insert({ WHITE_RAT_ATTACK_DOWN, "images/whiteRatAttackDown.png" });
    texturesToLoad.insert({ WHITE_RAT_ATTACK_LEFT, "images/whiteRatAttackLeft.png" });
    texturesToLoad.insert({ WHITE_RAT_ATTACK_RIGHT, "images/whiteRatAttackRight.png" });
    //Skeleton
    texturesToLoad.insert({ SKELETON_IDLE_DOWN, "images/skeletonIdleDown.png" });
    texturesToLoad.insert({ SKELETON_IDLE_LEFT, "images/skeletonIdleLeft.png" });
    texturesToLoad.insert({ SKELETON_IDLE_RIGHT, "images/skeletonIdleRight.png" });
    texturesToLoad.insert({ SKELETON_IDLE_UP, "images/skeletonIdleUp.png" });
    texturesToLoad.insert({ SKELETON_MOVE_DOWN, "images/skeletonMoveDown.png" });
    texturesToLoad.insert({ SKELETON_MOVE_UP, "images/skeletonMoveUp.png" });
    texturesToLoad.insert({ SKELETON_MOVE_LEFT, "images/skeletonMoveLeft.png" });
    texturesToLoad.insert({ SKELETON_MOVE_RIGHT, "images/skeletonMoveRight.png" });
    texturesToLoad.insert({ SKELETON_ATTACK_UP, "images/skeletonAttackUp.png" });
    texturesToLoad.insert({ SKELETON_ATTACK_DOWN, "images/skeletonAttackDown.png" });
    texturesToLoad.insert({ SKELETON_ATTACK_LEFT, "images/skeletonAttackLeft.png" });
    texturesToLoad.insert({ SKELETON_ATTACK_RIGHT, "images/skeletonAttackRight.png" });
    //ratKing
    texturesToLoad.insert({ RAT_KING_IDLE_DOWN, "images/ratKingIdleDown.png" });
    texturesToLoad.insert({ RAT_KING_IDLE_UP, "images/ratKingIdleUp.png" });
    texturesToLoad.insert({ RAT_KING_IDLE_LEFT, "images/ratKingIdleLeft.png" });
    texturesToLoad.insert({ RAT_KING_IDLE_RIGHT, "images/ratKingIdleRight.png" });
    texturesToLoad.insert({ RAT_KING_MOVE_UP, "images/ratKingMoveUp.png" });
    texturesToLoad.insert({ RAT_KING_MOVE_DOWN, "images/ratKingMoveDown.png" });
    texturesToLoad.insert({ RAT_KING_MOVE_LEFT, "images/ratKingMoveLeft.png" });
    texturesToLoad.insert({ RAT_KING_MOVE_RIGHT, "images/ratKingMoveRight.png" });
    texturesToLoad.insert({ RAT_KING_ATTACK_UP, "images/ratKingAttackUp.png" });
    texturesToLoad.insert({ RAT_KING_ATTACK_DOWN, "images/ratKingAttackDown.png" });
    texturesToLoad.insert({ RAT_KING_ATTACK_LEFT, "images/ratKingAttackLeft.png" });
    texturesToLoad.insert({ RAT_KING_ATTACK_RIGHT, "images/ratKingAttackRight.png" });
    //Skeleton King
    texturesToLoad.insert({ SKELETON_KING_IDLE_DOWN, "images/skeletonKing.png" });
    texturesToLoad.insert({ SKELETON_KING_IDLE_LEFT, "images/skeletonKing.png" });
    texturesToLoad.insert({ SKELETON_KING_IDLE_RIGHT, "images/skeletonKing.png" });
    texturesToLoad.insert({ SKELETON_KING_IDLE_UP, "images/skeletonKing.png" });
    texturesToLoad.insert({ SKELETON_KING_MOVE_DOWN, "images/skeletonKing.png" });
    texturesToLoad.insert({ SKELETON_KING_MOVE_UP, "images/skeletonKing.png" });
    texturesToLoad.insert({ SKELETON_KING_MOVE_LEFT, "images/skeletonKing.png" });
    texturesToLoad.insert({ SKELETON_KING_MOVE_RIGHT, "images/skeletonKing.png" });
    texturesToLoad.insert({ SKELETON_KING_ATTACK_UP, "images/skeletonKing.png" });
    texturesToLoad.insert({ SKELETON_KING_ATTACK_DOWN, "images/skeletonKing.png" });
    texturesToLoad.insert({ SKELETON_KING_ATTACK_LEFT, "images/skeletonKing.png" });
    texturesToLoad.insert({ SKELETON_KING_ATTACK_RIGHT, "images/skeletonKing.png" });
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
    texturesToLoad.insert({ ITEM_LEATHER_HAT, "images/leatherHat.png" });
    texturesToLoad.insert({ ITEM_LEATHER_BODY, "images/leatherBody.png" });
    texturesToLoad.insert({ ITEM_LEATHER_PANTS, "images/leatherPants.png" });
    texturesToLoad.insert({ ITEM_LEATHER_GLOVES, "images/leatherGloves.png" });
    texturesToLoad.insert({ ITEM_LEATHER_BOOTS, "images/leatherBoots.png" });
    //resources
    texturesToLoad.insert({ ITEM_LOGS, "images/logs.png" });
    //building icons
    texturesToLoad.insert({ BUILDING_ICON_WEAPON_SHOP, "images/signWeapons.png" });
    texturesToLoad.insert({ BUILDING_ICON_ARMOUR_SHOP, "images/signArmour.png" });
    texturesToLoad.insert({ BUILDING_ICON_HEALTH, "images/signHealth.png" });
    texturesToLoad.insert({ BUILDING_ICON_TAVERN, "images/signTavern.png" });
    texturesToLoad.insert({ BUILDING_ICON_BLACKSMITH, "images/signBlacksmith.png" });
    //doodad textures
    texturesToLoad.insert({ TEXTURE_TOWN_COMMAND, "images/townCommandDooDad.png" });
    texturesToLoad.insert({ TEXTURE_APPLE_TREE_WITH_FRUIT, "images/appleTreeWithFruit.png" });
    texturesToLoad.insert({ TEXTURE_APPLE_TREE_NO_FRUIT, "images/appleTreeNoFruit.png" });
    texturesToLoad.insert({ TEXTURE_RASPBERRY_BUSH_WITH_BERRIES, "images/raspberryBushWithBerries.png" });
    texturesToLoad.insert({ TEXTURE_RASPBERRY_BUSH_NO_BERRIES, "images/raspberryBushNoBerries.png" });
    texturesToLoad.insert({ TEXTURE_TOWN_COMMAND, "images/townCommandDooDad.png" });
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
    SDL_AtomicLock(&unitDestroyLock);
    destroyFlaggedUnits();
    SDL_AtomicUnlock(&unitDestroyLock);
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
            if (xToCheck < 0 || xToCheck >= zoneMap->tileMap.size() || yToCheck < 0 || yToCheck >= zoneMap->tileMap[x].size())
            {
                return false;
            }
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

void RpgTileGridScene::payBuildingCosts(Building* building) {
    player->gold -= buildingBeingPlaced.goldCost;
    for (auto item : player->inventory) {
        if (item->name == "Logs")
        {
            item->stackSize -= building->woodCost;
            if (item->stackSize <= 0)
            {
                player->deleteItemFromInventory(item);
            }
        }
    }
    menus[INVENTORY_MENU]->update();
}

bool RpgTileGridScene::canAffordBuilding(Building* building)
{
    if (player->gold < building->goldCost)
    {
        return false;
    }

    Item* woodInInventory = nullptr;
    for (auto item : player->inventory) {
        if (item->name == "Logs")
        {
            woodInInventory = item;
        }
    }
    if (woodInInventory == nullptr || woodInInventory->stackSize < building->woodCost)
    {
        return false;
    }

    return true;
}

void RpgTileGridScene::loadZones()
{
    //load zones from file
    SaveFile zonesFile = SaveFile("zones.txt");
    zonesFile.loadFile();
    for (auto zone : zonesFile.objects) {
        ZoneMap* newZone = new ZoneMap(zone.rawString, this);
        newZone->setupGraph(this);
        addZone(newZone);
        if (newZone->id >= nextZoneId)
        {
            nextZoneId = newZone->id + 1;
        }
        for (auto* unit : newZone->getUnits())
        {
            if (((RpgUnit*)unit)->assignedToBuildingId != -1) {
                for (auto building : newZone->getBuildings()) {
                    if (building->id == ((RpgUnit*)unit)->assignedToBuildingId)
                    {
                        building->assignUnit((RpgUnit*)unit);
                    }
                }
            }
        }
        for (auto* dooDad : newZone->getDooDads())
        {
            if (dooDad->assignedToBuildingId != -1) {
                for (auto building : newZone->getBuildings()) {
                    if (building->id == dooDad->assignedToBuildingId)
                    {
                        building->assignDooDad(dooDad);
                    }
                }
            }
        }
    }
    currentZone = getZones()[0];
    xOffset = 0;
    yOffset = 0;
}

void RpgTileGridScene::resizeTiles()
{


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

    for (auto zone : getZones())
    {
        for (auto unit : zone.second->getUnits()) {
            unit->resize(tileWidth * 3, tileHeight * 3);
        }
    }
}

void RpgTileGridScene::destroyUnit(RpgUnit* unit)
{
    //remove unit from zones
    for (auto zone : getZones())
    {
        zone.second->removeUnitFromZone(unit);
    }

    //clear unit from units that are targetting it
    if (unit->beingTargetedBy.size() > 0)
    {
        for (auto targetingUnit : unit->beingTargetedBy) {
            targetingUnit->targetUnit = nullptr;
        }
    }

    //clear unit from units that are being targeted by it
    if (unit->targetUnit != nullptr)
    {
        auto targetingUnitIterator = unit->targetUnit->beingTargetedBy.begin();
        while (targetingUnitIterator != unit->targetUnit->beingTargetedBy.end())
        {
            if ((*targetingUnitIterator) == unit) {
                targetingUnitIterator = unit->targetUnit->beingTargetedBy.erase(targetingUnitIterator);
            }
            else {
                targetingUnitIterator++;
            }
        }
    }

    //clear unit from pathfinding queue
    auto unitIterator = unitsNeedingPath.begin();
    while (unitIterator != unitsNeedingPath.end())
    {
        if ((*unitIterator) == unit) {
            unitIterator = unitsNeedingPath.erase(unitIterator);
        }
        else {
            unitIterator++;
        }
    }

    auto unitIterator2 = unitsNeedingPath2.begin();
    while (unitIterator2 != unitsNeedingPath2.end())
    {
        if ((*unitIterator2) == unit) {
            unitIterator2 = unitsNeedingPath2.erase(unitIterator2);
        }
        else {
            unitIterator2++;
        }
    }

    //unassign unit from building
    if (((RpgUnit*)unit)->assignedToBuilding != nullptr)
    {
        ((RpgUnit*)unit)->assignedToBuilding->unAssignUnit(((RpgUnit*)unit));
    }

    delete (unit);
}

void RpgTileGridScene::destroyFlaggedUnits()
{
    updatingUnits = true;
    for (auto unit : unitsToDestroy) {
        destroyUnit((RpgUnit*)unit);
    }
    unitsToDestroy.clear();
    updatingUnits = false;
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
    case WHITE_RAT:
        createdUnit = new WhiteRat(zoneId, WHITE_RAT, this, x, y);
        break;
    case SOLDIER:
        createdUnit = new Soldier(zoneId, SOLDIER, this, x, y);
        break;
    case TOWNSPERSON:
        createdUnit = new TownsPerson(zoneId, TOWNSPERSON, this, x, y);
        break;
    case SKELETON:
        createdUnit = new Skeleton(zoneId, SKELETON, this, x, y);
        break;
    case SKELETON_KING:
        createdUnit = new SkeletonKing(zoneId, SKELETON_KING, this, x, y);
        break;
    default:
        createdUnit = NULL;
        break;
    }

    getZones()[zoneId]->addUnitToLocation(createdUnit, x, y);
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
    case WHITE_RAT:
        createdUnit = new WhiteRat(zone->id, WHITE_RAT, this, x, y);
        break;
    case SOLDIER:
        createdUnit = new Soldier(zone->id, SOLDIER, this, x, y);
        break;
    case TOWNSPERSON:
        createdUnit = new TownsPerson(zone->id, TOWNSPERSON, this, x, y);
        break;
    case SKELETON:
        createdUnit = new Skeleton(zone->id, SKELETON, this, x, y);
        break;
    case SKELETON_KING:
        createdUnit = new SkeletonKing(zone->id, SKELETON_KING, this, x, y);
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
    TownCommand* newTownCommand;
    switch (buildingType)
    {
    case BUILDING_ITEM_SHOP:
        createdBuilding = createNewBuilding(buildingType, direction);
        createdBuilding->assignUnit(createUnitAtLocation(zoneId, TOWNSPERSON, x + 3, y + 2));
        break;
    case BUILDING_CAMP_COMMAND_CENTRE:
        createdBuilding = createNewBuilding(buildingType, direction);
        newTownCommand = new TownCommand(this, TEXTURE_TOWN_COMMAND, x + 2, y + 2);
        createdBuilding->assignDooDad(newTownCommand);
        getZone(zoneId)->addDooDadToLocation(newTownCommand, x + 2, y + 2);
        break;
    default:
        createdBuilding = nullptr;
        break;
    }
    getZone(zoneId)->addBuildingToLocation(createdBuilding, x, y);
    return createdBuilding;
}

Building* RpgTileGridScene::createBuildingAtLocation(ZoneMap* zone, int buildingType, int direction, int x, int y)
{
    Building* createdBuilding;
    TownCommand* newTownCommand;
    switch (buildingType)
    {
    case BUILDING_ITEM_SHOP:
        createdBuilding = createNewBuilding(buildingType, direction);
        createdBuilding->assignUnit(createUnitAtLocation(zone, TOWNSPERSON, x + 3, y + 2));
        break;
    case BUILDING_CAMP_COMMAND_CENTRE:
        createdBuilding = createNewBuilding(buildingType, direction);
        newTownCommand = new TownCommand(this, TEXTURE_TOWN_COMMAND, x + 2, y + 2);
        createdBuilding->assignDooDad(newTownCommand);
        zone->addDooDadToLocation(newTownCommand, x + 2, y + 2);
        break;
    default:
        createdBuilding = nullptr;
        break;
    }
    zone->addBuildingToLocation(createdBuilding, x, y);
    return createdBuilding;
}

void RpgTileGridScene::removeBuildingFromZone(ZoneMap* zone, Building* building)
{
    zone->removeBuildingFromZone(building);
}

void RpgTileGridScene::removeBuildingFromZone(ZoneMap zone, Building* building)
{
    zone.removeBuildingFromZone(building);
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
    mapTiles[TILE_DIRT_ROAD] = MapTile(true , TILE_DIRT_ROAD);

    resizeTiles();
}

void RpgTileGridScene::init()
{
    player = nullptr;
    placingBuilding = false;
    aggroUpdateRate = 30;
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

void RpgTileGridScene::scrollCamera() {
    int x, y;
    x = controllerInterface->latestXpos;
    y = controllerInterface->latestYpos;

    if (x < engine->screenWidth * 0.01) {
        xOffset += SCROLL_SPEED;
    }
    if (x > engine->screenWidth * 0.99) {
        xOffset -= SCROLL_SPEED;
    }
    if (y < engine->screenHeight * 0.01) {
        yOffset += SCROLL_SPEED;
    }
    if (y > engine->screenHeight * 0.99) {
        yOffset -= SCROLL_SPEED;
    }
}