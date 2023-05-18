#include "RpgTileGridScene.h"

const int SCROLL_SPEED = 12;

RpgTileGridScene::RpgTileGridScene() : TileGridScene()
{
    init();
}

RpgTileGridScene::RpgTileGridScene(BaseGameEngine* gameEngine) : TileGridScene((BaseGameEngine*)gameEngine)
{
    init();
}

void RpgTileGridScene::desiredPlayerDrawLocation(double desiredCoords[2])
{
    desiredCoords[0] = (engine->screenWidth - mainCanvasStartX) / 2 + mainCanvasStartX;
    desiredCoords[1] = (engine->screenHeight / 2);
}

void RpgTileGridScene::declareSceneAssets()
{
    TileGridScene::declareSceneAssets();
    //tile textures
    texturesToLoad.insert({ TEXTURE_COAST_LEFT, "images/coastLeft.png" });
    texturesToLoad.insert({ TEXTURE_COAST_RIGHT, "images/coastRight.png" });
    texturesToLoad.insert({ TEXTURE_COAST_TOP, "images/coastTop.png" });
    texturesToLoad.insert({ TEXTURE_COAST_BOTTOM, "images/coastBottom.png" });
    texturesToLoad.insert({ TEXTURE_COAST_TOP_RIGHT, "images/coastTopRight.png" });
    texturesToLoad.insert({ TEXTURE_COAST_TOP_LEFT, "images/coastTopLeft.png" });
    texturesToLoad.insert({ TEXTURE_COAST_BOTTOM_LEFT, "images/coastBottomLeft.png" });
    texturesToLoad.insert({ TEXTURE_COAST_BOTTOM_RIGHT, "images/coastBottomRight.png" });
    texturesToLoad.insert({ WATER, "images/water.png" });
    //texturesToLoad.insert({ WATER, "images/water2.png" });
    texturesToLoad.insert({ TREE, "images/treeTim.png" });
    texturesToLoad.insert({ TREE_2, "images/treeTim2.png" });
    texturesToLoad.insert({ TREE_3, "images/treeTim3.png" });
    //texturesToLoad.insert({ TREE, "images/tree2.png" });
    texturesToLoad.insert({ TEXTURE_TREE_STUMP, "images/treeStumpTim.png" });
    //texturesToLoad.insert({ GRASS, "images/tallGrass.png" });
    texturesToLoad.insert({ GRASS, "images/grass2.png" });
    texturesToLoad.insert({ TEXTURE_GRASS_2, "images/grass.png" });
    texturesToLoad.insert({ TEXTURE_GRASS_3, "images/grass3.png" });
    texturesToLoad.insert({ TEXTURE_GRASS_4, "images/grass4.png" });
    texturesToLoad.insert({ TEXTURE_GRASS_5, "images/grass5.png" });
    //texturesToLoad.insert({ GRASS, "images/grass2.png" });
    texturesToLoad.insert({ MOUNTAIN, "images/mountain2.png" });
    texturesToLoad.insert({ PORTAL_CAVE_HILL, "images/caveEntrance.png" });
    texturesToLoad.insert({ ENCAMPMENT, "images/encampmentTile.png" });
    texturesToLoad.insert({ BLANK_PORTAL, "images/blank.png" });
    texturesToLoad.insert({ WOOD_WALL_ONE, "images/woodWallOne2.png" });
    texturesToLoad.insert({ WOOD_WALL_TWO, "images/woodWallTwo2.png" });
    texturesToLoad.insert({ CAVE_FILL, "images/caveFill.png" });
    texturesToLoad.insert({ CAVE_PATH, "images/cavePath.png" });
    texturesToLoad.insert({ CAVE_WALL_TOP, "images/caveWallTop.png" });
    texturesToLoad.insert({ CAVE_WALL_BOTTOM, "images/caveWallBottom.png" });
    texturesToLoad.insert({ CAVE_STAIRS_UP, "images/caveStairsUp.png" });
    texturesToLoad.insert({ TILE_DIRT_ROAD, "images/DirtRoadFilled.png" });
    texturesToLoad.insert({ TEXTURE_BACKGROUND_TREE, "images/backGroundTree.png" });

    //UI textures
    texturesToLoad.insert({ BUTTON_BACKGROUND, "images/buttonBackground.png" });
    //texturesToLoad.insert({ TEXTURE_EQUIPPED_MENU_SILHOUETTE, "images/silhouetteGrey.png" });
    texturesToLoad.insert({ TEXTURE_EQUIPPED_MENU_SILHOUETTE, "images/silhouette.png" });
    texturesToLoad.insert({ TEXTURE_LARGE_ARROW_RIGHT, "images/largeArrowRight.png" });
    
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
    texturesToLoad.insert({ MAC_WIZ_IDLE_DOWN, "images/shopKeeper.png" });
    //item textures
    texturesToLoad.insert({ TEXTURE_SHORT_SWORD, "images/itemSword.png" });
    texturesToLoad.insert({ TEXTURE_CLUB, "images/club.png" });
    texturesToLoad.insert({ TEXTURE_MACE, "images/mace.png" });
    texturesToLoad.insert({ TEXTURE_RAG_HAT, "images/RagHat.png" });
    texturesToLoad.insert({ TEXTURE_RAG_BODY, "images/RagBody.png" });
    texturesToLoad.insert({ TEXTURE_RAG_PANTS, "images/RagPants.png" });
    texturesToLoad.insert({ TEXTURE_RAG_GLOVES, "images/RagGloves.png" });
    texturesToLoad.insert({ TEXTURE_RAG_BOOTS, "images/RagBoots.png" });
    texturesToLoad.insert({ TEXTURE_LONG_SWORD, "images/longSword.png" });
    texturesToLoad.insert({ TEXTURE_LINEN_HAT, "images/LinenHat.png" });
    texturesToLoad.insert({ TEXTURE_LINEN_BODY, "images/LinenBody.png" });
    texturesToLoad.insert({ TEXTURE_LINEN_PANTS, "images/LinenPants.png" });
    texturesToLoad.insert({ TEXTURE_LINEN_GLOVES, "images/LinenGloves.png" });
    texturesToLoad.insert({ TEXTURE_LINEN_BOOTS, "images/LinenBoots.png" });
    texturesToLoad.insert({ TEXTURE_LEATHER_HAT, "images/leatherHat.png" });
    texturesToLoad.insert({ TEXTURE_LEATHER_BODY, "images/leatherBody.png" });
    texturesToLoad.insert({ TEXTURE_LEATHER_PANTS, "images/leatherPants.png" });
    texturesToLoad.insert({ TEXTURE_LEATHER_GLOVES, "images/leatherGloves.png" });
    texturesToLoad.insert({ TEXTURE_LEATHER_BOOTS, "images/leatherBoots.png" });
    texturesToLoad.insert({ TEXTURE_BRONZE_HELM, "images/bronzeHelm.png" });
    texturesToLoad.insert({ TEXTURE_BRONZE_BODY, "images/bronzeBody.png" });
    texturesToLoad.insert({ TEXTURE_BRONZE_PANTS, "images/bronzeLegs.png" });
    texturesToLoad.insert({ TEXTURE_BRONZE_GLOVES, "images/bronzeGloves.png" });
    texturesToLoad.insert({ TEXTURE_BRONZE_BOOTS, "images/bronzeBoots.png" });
    //resources
    texturesToLoad.insert({ TEXTURE_LOGS, "images/logs.png" });
    texturesToLoad.insert({ TEXTURE_CRUDE_HIDE, "images/crudeHide.png" });
    texturesToLoad.insert({ TEXTURE_SCRAP_MEAT, "images/scrapMeat.png" });
    texturesToLoad.insert({ TEXTURE_STONE, "images/stone.png" });
    texturesToLoad.insert({ TEXTURE_COAL, "images/coal.png" });
    texturesToLoad.insert({ TEXTURE_TIN_ORE, "images/tinOre.png" });
    texturesToLoad.insert({ TEXTURE_COPPER_ORE, "images/copperOre.png" });
    texturesToLoad.insert({ TEXTURE_TIN_BAR, "images/tinBar.png" });
    texturesToLoad.insert({ TEXTURE_COPPER_BAR, "images/copperBar.png" });
    texturesToLoad.insert({ TEXTURE_BRONZE_BAR, "images/bronzeBar.png" });
    //food
    texturesToLoad.insert({ TEXTURE_APPLE, "images/apple.png" });
    texturesToLoad.insert({ TEXTURE_RASPBERRY, "images/raspberries.png" });
    texturesToLoad.insert({ TEXTURE_COOKED_SCRAP_MEAT, "images/cookedScrapMeat.png" });
    //building
    texturesToLoad.insert({ TEXTURE_BUILDING_WOODCUTTER, "images/woodCutter.png" });
    texturesToLoad.insert({ TEXTURE_BUILDING_HOUSE, "images/house.png" });
    texturesToLoad.insert({ TEXTURE_GUARDHOUSE_BOTTOM, "images/guardHouseBottom.png" });
    texturesToLoad.insert({ TEXTURE_GUARDHOUSE_TOP, "images/guardHouseTop.png" });
    //building icons
    texturesToLoad.insert({ BUILDING_ICON_WEAPON_SHOP, "images/signWeapons.png" });
    texturesToLoad.insert({ BUILDING_ICON_ARMOUR_SHOP, "images/signArmour.png" });
    texturesToLoad.insert({ BUILDING_ICON_HEALTH, "images/signHealth.png" });
    texturesToLoad.insert({ BUILDING_ICON_TAVERN, "images/signTavern.png" });
    texturesToLoad.insert({ BUILDING_ICON_BLACKSMITH, "images/signBlacksmith.png" });
    texturesToLoad.insert({ BUILDING_ICON_WOODCUTTER, "images/signTreeCutter.png" });
    texturesToLoad.insert({ BUILDING_ICON_HOUSE, "images/signHouse.png" });
    texturesToLoad.insert({ TEXTURE_PICKET_FENCE_BOTTOM, "images/picketFenceBottom.png" });
    texturesToLoad.insert({ TEXTURE_PICKET_FENCE_TOP, "images/picketFenceTop.png" });
    texturesToLoad.insert({ TEXTURE_PICKET_FENCE_LEFT, "images/picketFenceLeft.png" });
    texturesToLoad.insert({ TEXTURE_PICKET_FENCE_RIGHT, "images/picketFenceRight.png" });
    texturesToLoad.insert({ TEXTURE_PICKET_FENCE_BOTTOM_RIGHT, "images/picketFenceBottomRight.png" });
    texturesToLoad.insert({ TEXTURE_PICKET_FENCE_BOTTOM_LEFT, "images/picketFenceBottomLeft.png" });
    texturesToLoad.insert({ TEXTURE_PICKET_FENCE_TOP_RIGHT, "images/picketFenceTop.png" });
    texturesToLoad.insert({ TEXTURE_PICKET_FENCE_TOP_LEFT, "images/picketFenceTop.png" });
    //doodad textures
    texturesToLoad.insert({ TEXTURE_TOWN_COMMAND, "images/townCommandDooDad.png" });
    texturesToLoad.insert({ TEXTURE_APPLE_TREE_WITH_FRUIT, "images/appleTreeWithFruit.png" });
    texturesToLoad.insert({ TEXTURE_APPLE_TREE_NO_FRUIT, "images/appleTreeNoFruit.png" });
    texturesToLoad.insert({ TEXTURE_RASPBERRY_BUSH_WITH_BERRIES, "images/raspberryBushWithBerries.png" });
    texturesToLoad.insert({ TEXTURE_RASPBERRY_BUSH_NO_BERRIES, "images/raspberryBushNoBerries.png" });
    texturesToLoad.insert({ TEXTURE_TOWN_COMMAND, "images/townCommandDooDad.png" });
    texturesToLoad.insert({ TEXTURE_RAT_SPAWNER, "images/ratSpawner.png" });
    texturesToLoad.insert({ TEXTURE_CHEST_CLOSED, "images/chestClosed.png" });
    texturesToLoad.insert({ TEXTURE_CHEST_OPEN, "images/chestOpen.png" });
    texturesToLoad.insert({ TEXTURE_CAMP_FIRE, "images/campFire.png" });
    texturesToLoad.insert({ TEXTURE_MINEBLOCK, "images/mineBlock.png" });
    texturesToLoad.insert({ TEXTURE_FURNACE, "images/furnace.png" });
    //misc
    texturesToLoad.insert({ TEXTURE_TEST_PROJECTILE, "images/testProjectile.png" });
}

void RpgTileGridScene::setUpScene()
{
    createTiles();
    TileGridScene::setUpScene(NEW_GAME_SAVE_FILE);
    zonePortalImages.push_back(ENCAMPMENT);
    zonePortalImages.push_back(BLANK_PORTAL);
    zonePortalImages.push_back(PORTAL_CAVE_HILL);
    zonePortalImages.push_back(CAVE_STAIRS_UP);
}

void RpgTileGridScene::setUpScene(std::string saveFile)
{
    createTiles();
    TileGridScene::setUpScene(saveFile);
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
    //SDL_AtomicLock(&unitDestroyLock);
    destroyFlaggedUnits();
    destroyFlaggedDooDads();
    //SDL_AtomicUnlock(&unitDestroyLock);
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

void RpgTileGridScene::payBuildingCosts(Building* building, RpgTown* town) {
    player->gold -= buildingBeingPlaced.goldCost;
    int woodCostRemaining = buildingBeingPlaced.woodCost;
    for (auto item : player->inventory) {
        if (item->specificType == ITEM_WOOD)
        {
            if (item->stackSize > woodCostRemaining)
            {
                item->stackSize -= woodCostRemaining;
                woodCostRemaining = 0;
            }
            else {
                woodCostRemaining -= item->stackSize;
                player->deleteItemFromInventory(item);
            }

        }
    }

    if (woodCostRemaining > 0)
    {
        for (auto item : town->getTownInventory()) {
            if (item->specificType == ITEM_WOOD)
            {
                if (item->stackSize > woodCostRemaining)
                {
                    item->stackSize -= woodCostRemaining;
                    woodCostRemaining = 0;
                }
                else {
                    woodCostRemaining -= item->stackSize;
                    removeItemFromContainer(item, town->getTownInventory());
                }

            }
        }
    }

    menus[INVENTORY_MENU]->update();
}

bool RpgTileGridScene::townCanAffordBuilding(Building* building, RpgTown* town)
{
    if (player->gold + town->getTownGold() < building->goldCost)
    {
        return false;
    }
    int totalWood = qtyInContainer(ITEM_WOOD, player->inventory) + qtyInContainer(ITEM_WOOD, town->getTownInventory());

    if (totalWood < building->woodCost)
    {
        return false;
    }

    if (building->getPopCost() > town->getFreePop() && building->getPopCost() > 0)
    {
        return false;
    }

    return true;
}

bool RpgTileGridScene::playerCanAffordBuilding(Building* building)
{
    if (player->gold < building->goldCost)
    {
        return false;
    }
    int totalWood = qtyInContainer(ITEM_WOOD, player->inventory);

    if (totalWood < building->woodCost)
    {
        return false;
    }

    if (building->getPopCost() > 0)
    {
        return false;
    }

    return true;
}

void RpgTileGridScene::loadZone(SaveObject saveObject)
{
    RpgZone* newZone = nullptr;
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        if (saveObject.attributes[i].attributeType == RPG_ZONE_TYPE) {
            switch (std::stoi(saveObject.attributes[i].valueString))
            {
            case ZONE_RPG_TOWN:
                newZone = new RpgTown(saveObject.rawString, this);
                break;
            case ZONE_RPG_PROVINCE:
                newZone = new RpgProvinceZone(saveObject.rawString, this);
                break;
            default:
                newZone = new RpgZone(saveObject.rawString, this);
                break;
            }
        }
    }

    if (newZone == nullptr) //if the RPG_ZONE_TYPE was not recognized or not present create a basic RpgZoneObject
    {
        newZone = new RpgZone(saveObject.rawString, this);
    }
    newZone->setupGraph(this);
    addZone(newZone);
    if (newZone->id >= nextZoneId)
    {
        nextZoneId = newZone->id + 1;
    }
    for (auto* unit : newZone->getUnits())
    {
        if (((RpgUnit*)unit)->isPlayer)
        {
            player = (Player*)unit;
        }
        Building* assignedBuilding = newZone->getBuildingById(((RpgUnit*)unit)->assignedToBuildingId);
        if (assignedBuilding != nullptr)
        {
            assignedBuilding->assignUnit((RpgUnit*)unit);
        }
        else {
            ((RpgUnit*)unit)->assignedToBuildingId = -1;
        }
    }
    for (auto* dooDad : newZone->getDooDads())
    {
        Building* assignedBuilding = newZone->getBuildingById(dooDad->assignedToBuildingId);
        if (assignedBuilding != nullptr)
        {
            assignedBuilding->assignDooDad(dooDad);
        }
        else {
            dooDad->assignedToBuildingId = -1;
        }
    }
}

void RpgTileGridScene::loadZones(std::string saveFile)
{
    //load zones from file
    //SaveFile zonesFile = SaveFile("zones.txt");
    SaveFile zonesFile = SaveFile(saveFile);
    zonesFile.loadFile();
    for (auto zone : zonesFile.objects) {
        loadZone(zone);
        //RpgZone* newZone = nullptr;
        //for (int i = 0; i < zone.attributes.size(); i++)
        //{
        //    if (zone.attributes[i].attributeType == RPG_ZONE_TYPE) {
        //        switch (std::stoi(zone.attributes[i].valueString))
        //        {
        //        case ZONE_RPG_TOWN:
        //            newZone = new RpgTown(zone.rawString, this);
        //            break;
        //        case ZONE_RPG_PROVINCE:
        //            newZone = new RpgProvinceZone(zone.rawString, this);
        //            break;
        //        default:
        //            newZone = new RpgZone(zone.rawString, this);
        //            break;
        //        }
        //    }
        //}
        ////RpgZone* newZone = new RpgZone(zone.rawString, this);
        //if (newZone == nullptr)
        //{
        //    newZone = new RpgZone(zone.rawString, this);
        //}
        //newZone->setupGraph(this);
        //addZone(newZone);
        //if (newZone->id >= nextZoneId)
        //{
        //    nextZoneId = newZone->id + 1;
        //}
        //for (auto* unit : newZone->getUnits())
        //{
        //    if (((RpgUnit*)unit)->assignedToBuildingId != -1) {
        //        for (auto building : newZone->getBuildings()) {
        //            if (building->id == ((RpgUnit*)unit)->assignedToBuildingId)
        //            {
        //                building->assignUnit((RpgUnit*)unit);
        //            }
        //        }
        //    }
        //}
        //for (auto* dooDad : newZone->getDooDads())
        //{
        //    if (dooDad->assignedToBuildingId != -1) {
        //        for (auto building : newZone->getBuildings()) {
        //            if (building->id == dooDad->assignedToBuildingId)
        //            {
        //                building->assignDooDad(dooDad);
        //            }
        //        }
        //    }
        //}
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

void RpgTileGridScene::destroyFlaggedDooDads()
{
    for (auto dooDad : dooDadsToDestroy) {
        destroyDooDad(dooDad);
    }
    dooDadsToDestroy.clear();
}

void RpgTileGridScene::pickUpItemAtLocation(RpgUnit* unit, int x, int y)
{
    int itemsAtLocation = currentZone->getItemsAtLocation(x, y).size();
    if (itemsAtLocation > 0)
    {
        unit->addToInventory(currentZone->getItemsAtLocation(x, y)[itemsAtLocation - 1]);
        currentZone->removeItemAtLocation(currentZone->getItemsAtLocation(x, y)[itemsAtLocation - 1], x, y);
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
    for (auto targetingUnit : unit->getBeingTargetedBy()) {
        targetingUnit->clearTargetUnit();
    }

    //clear unit from units that are being targeted by it
    //if (unit->getTargetUnit()->getBeingTargetedBy().size() > 5)
    //{
    //    int sdf = 34435;
    //}
    unit->clearTargetUnit();
    /*if (unit->getTargetUnit())
    {
        auto targetingUnitIterator = unit->getTargetUnit()->beingTargetedBy.begin();
        while (targetingUnitIterator != unit->getTargetUnit()->beingTargetedBy.end())
        {
            if ((*targetingUnitIterator) == unit) {
                targetingUnitIterator = unit->getTargetUnit()->beingTargetedBy.erase(targetingUnitIterator);
            }
            else {
                targetingUnitIterator++;
            }
        }
    }*/


    //clear unit from pathfinding queue
    removeUnitFromPathQueue(unit);
    /*
    auto unitIterator = unitsNeedingPath.begin();
    while (unitIterator != unitsNeedingPath.end())
    {
        if ((*unitIterator) == unit) {
            unitIterator = unitsNeedingPath.erase(unitIterator);
        }
        else {
            unitIterator++;
        }
    }*/

    //unassign unit from building
    if (((RpgUnit*)unit)->assignedToBuilding != nullptr)
    {
        ((RpgUnit*)unit)->assignedToBuilding->unAssignUnit(((RpgUnit*)unit));
    }
    
    delete (unit);
}

void RpgTileGridScene::destroyFlaggedUnits()
{

    //destroyingUnits = true;
    if (!unitsToDestroy.size())
    {
        return;
    }
    SDL_AtomicLock(&unitDestroyLock);
    for (auto unit : unitsToDestroy) {
        //if (unit->deleteLock)
        //{
        //    continue;
        //}
        SDL_AtomicLock(&unit->deleteLock);
        destroyUnit((RpgUnit*)unit);
        //SDL_AtomicUnlock(&unit->deleteLock);
    }
    SDL_AtomicUnlock(&unitDestroyLock);
    unitsToDestroy.clear();
    destroyingUnits = false;
}

void RpgTileGridScene::destroyDooDad(DooDad* dooDad)
{
    getZone(dooDad->zoneId)->destroyDooDad(dooDad);
}

RpgUnit* RpgTileGridScene::createUnitAtLocation(int zoneId, int unitType, int x, int y)
{
    RpgUnit* createdUnit = (RpgUnit*)createNewUnit(getZones()[zoneId], this, unitType);
    getZones()[zoneId]->addUnitToLocation(createdUnit, x, y);
    return createdUnit;
}

RpgUnit* RpgTileGridScene::createUnitAtLocation(ZoneMap* zone, int unitType, int x, int y)
{
    return createUnitAtLocation(zone->id, unitType, x, y);
    //RpgUnit* createdUnit = (RpgUnit*)createNewUnit(zone, this, unitType);
    //createdUnit->id = getUniqueUnitId();
    //zone->addUnitToLocation(createdUnit, x, y);
    //return createdUnit;
}

RpgUnit* RpgTileGridScene::createUnitAtLocationWorldBuilder(ZoneMap* zone, int unitType, int x, int y)
{
    RpgUnit* createdUnit = (RpgUnit*)createNewUnit(zone, this, unitType);
    createdUnit->id = getUniqueUnitId();
    zone->addUnitToLocation(createdUnit, x, y);
    return createdUnit;
}

Building* RpgTileGridScene::createBuildingAtLocation(int zoneId, int buildingType, int direction, int x, int y)
{
    DooDad* newConstructDoodad;
    Building* createdBuilding = createNewBuilding(buildingType, direction);
    getZone(zoneId)->addBuildingToLocation(createdBuilding, x, y);
    for (DoodadOnConstruct newDoodad : createdBuilding->doodadsOnConstruct) {
        newConstructDoodad = createNewDooDad(newDoodad.doodadType, this, getZone(zoneId)->id);
        createdBuilding->assignDooDad(newConstructDoodad);
        getZone(zoneId)->addDooDadToLocation(newConstructDoodad, x + newDoodad.x, y + newDoodad.y);
    }
    return createdBuilding;
}

//Building* RpgTileGridScene::createBuildingAtLocation2(int zoneId, int buildingType, int direction, int x, int y)
//{
//    Building* createdBuilding;
//    TownCommand* newTownCommand;
//    DooDad* newAppleTree;
//
//    switch (buildingType)
//    {
//    case BUILDING_ITEM_SHOP:
//        createdBuilding = createNewBuilding(buildingType, direction);
//        createdBuilding->assignUnit(createUnitAtLocation(zoneId, TOWNSPERSON, x + 3, y + 2));
//        break;
//    case BUILDING_CAMP_COMMAND_CENTRE:
//        createdBuilding = createNewBuilding(buildingType, direction);
//        newTownCommand = new TownCommand(this, TEXTURE_TOWN_COMMAND, x + 2, y + 2);
//        createdBuilding->assignDooDad(newTownCommand);
//        getZone(zoneId)->addDooDadToLocation(newTownCommand, x + 2, y + 2);
//        break;
//    case BUILDING_BARRACKS:
//        createdBuilding = createNewBuilding(buildingType, direction);
//        createdBuilding->assignUnit(createUnitAtLocation(zoneId, TOWNSPERSON, x + 3, y + 2));
//        break;
//    case BUILDING_WOODCUTTER:
//        createdBuilding = createNewBuilding(buildingType, direction);
//        break;
//    case BUILDING_HOUSE:
//        createdBuilding = createNewBuilding(buildingType, direction);
//        break;
//    case BUILDING_GUARDHOUSE:
//        createdBuilding = createNewBuilding(buildingType, direction);
//        break;
//    case BUILDING_APPLE_ORCHARD:
//        createdBuilding = createNewBuilding(buildingType, direction);
//        //
//        newAppleTree = createNewDooDad(DOODAD_APPLE_TREE, this, getZone(zoneId)->id);
//        createdBuilding->assignDooDad(newAppleTree);
//        getZone(zoneId)->addDooDadToLocation(newAppleTree, x + 2, y + 2);
//        //
//        newAppleTree = createNewDooDad(DOODAD_APPLE_TREE, this, getZone(zoneId)->id);
//        createdBuilding->assignDooDad(newAppleTree);
//        getZone(zoneId)->addDooDadToLocation(newAppleTree, x + 4, y + 2);
//        //
//        newAppleTree = createNewDooDad(DOODAD_APPLE_TREE, this, getZone(zoneId)->id);
//        createdBuilding->assignDooDad(newAppleTree);
//        getZone(zoneId)->addDooDadToLocation(newAppleTree, x + 2, y + 4);
//        //
//        newAppleTree = createNewDooDad(DOODAD_APPLE_TREE, this, getZone(zoneId)->id);
//        createdBuilding->assignDooDad(newAppleTree);
//        getZone(zoneId)->addDooDadToLocation(newAppleTree, x + 4, y + 4);
//        break;
//    default:
//        createdBuilding = nullptr;
//        break;
//    }
//    getZone(zoneId)->addBuildingToLocation(createdBuilding, x, y);
//
//    return createdBuilding;
//}

    Building* RpgTileGridScene::createBuildingAtLocation(ZoneMap * zone, int buildingType, int direction, int x, int y)
    {
        return createBuildingAtLocation(zone->id, buildingType, direction, x, y);
        //Building* createdBuilding;
        //TownCommand* newTownCommand;
        //DooDad* newAppleTree;
        //switch (buildingType)
        //{
        //case BUILDING_ITEM_SHOP:
        //    createdBuilding = createNewBuilding(buildingType, direction);
        //    createdBuilding->assignUnit(createUnitAtLocation(zone, TOWNSPERSON, x + 3, y + 2));
        //    break;
        //case BUILDING_CAMP_COMMAND_CENTRE:
        //    createdBuilding = createNewBuilding(buildingType, direction);
        //    newTownCommand = new TownCommand(this, TEXTURE_TOWN_COMMAND, x + 2, y + 2);
        //    createdBuilding->assignDooDad(newTownCommand);
        //    zone->addDooDadToLocation(newTownCommand, x + 2, y + 2);
        //    break;
        //case BUILDING_BARRACKS:
        //    createdBuilding = createNewBuilding(buildingType, direction);
        //    createdBuilding->assignUnit(createUnitAtLocation(zone, TOWNSPERSON, x + 3, y + 2));
        //    break;
        //case BUILDING_WOODCUTTER:
        //    createdBuilding = createNewBuilding(buildingType, direction);
        //    break;
        //case BUILDING_HOUSE:
        //    createdBuilding = createNewBuilding(buildingType, direction);
        //    break;
        //case BUILDING_GUARDHOUSE:
        //    createdBuilding = createNewBuilding(buildingType, direction);
        //    break;
        //case BUILDING_APPLE_ORCHARD:
        //    createdBuilding = createNewBuilding(buildingType, direction);
        //    //
        //    newAppleTree = createNewDooDad(DOODAD_APPLE_TREE, this, zone->id);
        //    createdBuilding->assignDooDad(newAppleTree);
        //    zone->addDooDadToLocation(newAppleTree, x + 2, y + 2);
        //    //
        //    newAppleTree = createNewDooDad(DOODAD_APPLE_TREE, this, zone->id);
        //    createdBuilding->assignDooDad(newAppleTree);
        //    zone->addDooDadToLocation(newAppleTree, x + 4, y + 2);
        //    //
        //    newAppleTree = createNewDooDad(DOODAD_APPLE_TREE, this, zone->id);
        //    createdBuilding->assignDooDad(newAppleTree);
        //    zone->addDooDadToLocation(newAppleTree, x + 2, y + 4);
        //    //
        //    newAppleTree = createNewDooDad(DOODAD_APPLE_TREE, this, zone->id);
        //    createdBuilding->assignDooDad(newAppleTree);
        //    zone->addDooDadToLocation(newAppleTree, x + 4, y + 4);
        //    break;
        //case BUILDING_SMELTING_WORKS:
        //    createdBuilding = createNewBuilding(buildingType, direction);
        //    //newFurnace = new TownCommand(this, TEXTURE_TOWN_COMMAND, x + 2, y + 2);
        //    //createdBuilding->assignDooDad(newTownCommand);
        //    //zone->addDooDadToLocation(newTownCommand, x + 2, y + 2);
        //    break;
        //default:
        //    createdBuilding = nullptr;
        //    break;
        //}
        //zone->addBuildingToLocation(createdBuilding, x, y);

        //return createdBuilding;
    }

    Building* RpgTileGridScene::createBuildingAtLocationWorldBuilder(ZoneMap* zone, int buildingType, int direction, int x, int y)
    {
        DooDad* newConstructDoodad;
        Building* createdBuilding = createNewBuilding(buildingType, direction);
        zone->addBuildingToLocation(createdBuilding, x, y);
        for (DoodadOnConstruct newDoodad : createdBuilding->doodadsOnConstruct) {
            newConstructDoodad = createNewDooDad(newDoodad.doodadType, this, zone->id);
            createdBuilding->assignDooDad(newConstructDoodad);
            zone->addDooDadToLocation(newConstructDoodad, x + newDoodad.x, y + newDoodad.y);
        }
        return createdBuilding;
    }

void RpgTileGridScene::removeBuildingFromZone(ZoneMap* zone, Building* building)
{
    zone->removeBuildingFromZone(building);
}

void RpgTileGridScene::removeBuildingFromZone(ZoneMap zone, Building* building)
{
    removeBuildingFromZone(&zone, building);
}

void RpgTileGridScene::createTiles()
{
    //create the different tiles
    mapTiles[GRASS] = MapTile(true, GRASS);
    mapTiles[TEXTURE_GRASS_2] = MapTile(true, TEXTURE_GRASS_2);
    mapTiles[TEXTURE_GRASS_3] = MapTile(true, TEXTURE_GRASS_3);
    mapTiles[TEXTURE_GRASS_4] = MapTile(true, TEXTURE_GRASS_4);
    mapTiles[TEXTURE_GRASS_5] = MapTile(true, TEXTURE_GRASS_5);
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
    mapTiles[TEXTURE_COAST_LEFT] = MapTile(false, TEXTURE_COAST_LEFT);
    mapTiles[TEXTURE_COAST_RIGHT] = MapTile(false, TEXTURE_COAST_RIGHT);
    mapTiles[TEXTURE_COAST_TOP] = MapTile(false , TEXTURE_COAST_TOP);
    mapTiles[TEXTURE_COAST_BOTTOM] = MapTile(false, TEXTURE_COAST_BOTTOM);
    mapTiles[TEXTURE_COAST_TOP_LEFT] = MapTile(false, TEXTURE_COAST_TOP_LEFT);
    mapTiles[TEXTURE_COAST_TOP_RIGHT] = MapTile(false, TEXTURE_COAST_TOP_RIGHT);
    mapTiles[TEXTURE_COAST_BOTTOM_LEFT] = MapTile(false, TEXTURE_COAST_BOTTOM_LEFT);
    mapTiles[TEXTURE_COAST_BOTTOM_RIGHT] = MapTile(false, TEXTURE_COAST_BOTTOM_RIGHT);
    mapTiles[TEXTURE_PICKET_FENCE_BOTTOM] = MapTile(false, TEXTURE_PICKET_FENCE_BOTTOM);
    mapTiles[TEXTURE_PICKET_FENCE_BOTTOM_LEFT] = MapTile(false, TEXTURE_PICKET_FENCE_BOTTOM_LEFT);
    mapTiles[TEXTURE_PICKET_FENCE_BOTTOM_RIGHT] = MapTile(false, TEXTURE_PICKET_FENCE_BOTTOM_RIGHT);
    mapTiles[TEXTURE_PICKET_FENCE_LEFT] = MapTile(false, TEXTURE_PICKET_FENCE_LEFT);
    mapTiles[TEXTURE_PICKET_FENCE_RIGHT] = MapTile(false, TEXTURE_PICKET_FENCE_RIGHT);
    mapTiles[TEXTURE_PICKET_FENCE_TOP] = MapTile(false, TEXTURE_PICKET_FENCE_TOP);
    mapTiles[TEXTURE_BACKGROUND_TREE] = MapTile(false, TEXTURE_BACKGROUND_TREE);
    resizeTiles();
}

void RpgTileGridScene::init()
{
    destroyingUnits = false;
    player = nullptr;
    placingBuilding = false;
    placingUnit = false;
    //aggroUpdateRate = RPG_GAME_TICKS_PER_SECOND * 0.75;
    aggroUpdateRate = RPG_GAME_TICKS_PER_SECOND * 0.1;
    chestDropTable.resize(100);
    chestDropNum.resize(100);
    buildChestDropTable();
}

void RpgTileGridScene::drawCombatMessages()
{
    double displayCoords[2];
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

void RpgTileGridScene::buildChestDropTable()
{
    chestDropNum[1] = 2;
    chestDropTable[1].push_back({ 0.1, ITEM_CLUB });
    chestDropTable[1].push_back({ 0.3, ITEM_SHORT_SWORD });
    chestDropTable[1].push_back({ 0.1, ITEM_RAG_HAT });
    chestDropTable[1].push_back({ 0.1, ITEM_RAG_BODY });
    chestDropTable[1].push_back({ 0.1, ITEM_RAG_PANTS });
    chestDropTable[1].push_back({ 0.1, ITEM_RAG_BOOTS });
    chestDropTable[1].push_back({ 0.1, ITEM_RAG_GLOVES });
    chestDropTable[1].push_back({ 0.1, ITEM_LINEN_HAT });

    chestDropNum[2] = 3;
    chestDropTable[2].push_back({ 0.05, ITEM_CLUB });
    chestDropTable[2].push_back({ 0.1, ITEM_MACE });
    chestDropTable[2].push_back({ 0.25, ITEM_SHORT_SWORD });
    chestDropTable[2].push_back({ 0.1, ITEM_RAG_HAT });
    chestDropTable[2].push_back({ 0.1, ITEM_RAG_BODY });
    chestDropTable[2].push_back({ 0.1, ITEM_RAG_PANTS });
    chestDropTable[2].push_back({ 0.1, ITEM_RAG_BOOTS });
    chestDropTable[2].push_back({ 0.1, ITEM_RAG_GLOVES });
    chestDropTable[2].push_back({ 0.1, ITEM_LINEN_HAT });

    chestDropNum[3] = 3;
    chestDropTable[3].push_back({ 0.25, ITEM_MACE });
    chestDropTable[3].push_back({ 0.15, ITEM_SHORT_SWORD });
    chestDropTable[3].push_back({ 0.1, ITEM_LINEN_HAT });
    chestDropTable[3].push_back({ 0.1, ITEM_LINEN_BODY });
    chestDropTable[3].push_back({ 0.1, ITEM_LINEN_PANTS });
    chestDropTable[3].push_back({ 0.1, ITEM_LINEN_BOOTS });
    chestDropTable[3].push_back({ 0.1, ITEM_LINEN_GLOVES });
    chestDropTable[3].push_back({ 0.1, ITEM_LEATHER_HAT });

    chestDropNum[4] = 3;
    chestDropTable[4].push_back({ 0.1, ITEM_SHORT_SWORD });
    chestDropTable[4].push_back({ 0.3, ITEM_MACE });
    chestDropTable[4].push_back({ 0.1, ITEM_LONG_SWORD });
    chestDropTable[4].push_back({ 0.05, ITEM_LINEN_HAT });
    chestDropTable[4].push_back({ 0.05, ITEM_LINEN_BODY });
    chestDropTable[4].push_back({ 0.05, ITEM_LINEN_PANTS });
    chestDropTable[4].push_back({ 0.05, ITEM_LINEN_BOOTS });
    chestDropTable[4].push_back({ 0.05, ITEM_LINEN_GLOVES });
    chestDropTable[4].push_back({ 0.05, ITEM_LEATHER_HAT });
    chestDropTable[4].push_back({ 0.05, ITEM_LEATHER_BODY });
    chestDropTable[4].push_back({ 0.05, ITEM_LEATHER_PANTS });
    chestDropTable[4].push_back({ 0.05, ITEM_LEATHER_BOOTS });
    chestDropTable[4].push_back({ 0.05, ITEM_LEATHER_GLOVES });

    chestDropNum[5] = 4;
    chestDropTable[5].push_back({ 0.05, ITEM_SHORT_SWORD });
    chestDropTable[5].push_back({ 0.3, ITEM_MACE });
    chestDropTable[5].push_back({ 0.15, ITEM_LONG_SWORD });
    chestDropTable[5].push_back({ 0.04, ITEM_LINEN_HAT });
    chestDropTable[5].push_back({ 0.04, ITEM_LINEN_BODY });
    chestDropTable[5].push_back({ 0.04, ITEM_LINEN_PANTS });
    chestDropTable[5].push_back({ 0.04, ITEM_LINEN_BOOTS });
    chestDropTable[5].push_back({ 0.04, ITEM_LINEN_GLOVES });
    chestDropTable[5].push_back({ 0.05, ITEM_LEATHER_HAT });
    chestDropTable[5].push_back({ 0.05, ITEM_LEATHER_BODY });
    chestDropTable[5].push_back({ 0.05, ITEM_LEATHER_PANTS });
    chestDropTable[5].push_back({ 0.05, ITEM_LEATHER_BOOTS });
    chestDropTable[5].push_back({ 0.05, ITEM_LEATHER_GLOVES });
    chestDropTable[5].push_back({ 0.01, ITEM_BRONZE_HELM });
    chestDropTable[5].push_back({ 0.01, ITEM_BRONZE_BODY });
    chestDropTable[5].push_back({ 0.01, ITEM_BRONZE_PANTS });
    chestDropTable[5].push_back({ 0.01, ITEM_BRONZE_BOOTS });
    chestDropTable[5].push_back({ 0.01, ITEM_BRONZE_GLOVES });

    chestDropNum[6] = 4;
    chestDropTable[6].push_back({ 0.05, ITEM_SHORT_SWORD });
    chestDropTable[6].push_back({ 0.2, ITEM_MACE });
    chestDropTable[6].push_back({ 0.25, ITEM_LONG_SWORD });
    chestDropTable[6].push_back({ 0.03, ITEM_LINEN_HAT });
    chestDropTable[6].push_back({ 0.03, ITEM_LINEN_BODY });
    chestDropTable[6].push_back({ 0.03, ITEM_LINEN_PANTS });
    chestDropTable[6].push_back({ 0.03, ITEM_LINEN_BOOTS });
    chestDropTable[6].push_back({ 0.03, ITEM_LINEN_GLOVES });
    chestDropTable[6].push_back({ 0.04, ITEM_LEATHER_HAT });
    chestDropTable[6].push_back({ 0.04, ITEM_LEATHER_BODY });
    chestDropTable[6].push_back({ 0.04, ITEM_LEATHER_PANTS });
    chestDropTable[6].push_back({ 0.04, ITEM_LEATHER_BOOTS });
    chestDropTable[6].push_back({ 0.04, ITEM_LEATHER_GLOVES });
    chestDropTable[6].push_back({ 0.03, ITEM_BRONZE_HELM });
    chestDropTable[6].push_back({ 0.03, ITEM_BRONZE_BODY });
    chestDropTable[6].push_back({ 0.03, ITEM_BRONZE_PANTS });
    chestDropTable[6].push_back({ 0.03, ITEM_BRONZE_BOOTS });
    chestDropTable[6].push_back({ 0.03, ITEM_BRONZE_GLOVES });
}

void RpgTileGridScene::buildCraftingRecipes()
{
    CraftingRecipe newRecipe;

    //recipe name -------------------------------------------------------------------------------------------
    newRecipe = CraftingRecipe("Club");
    //inputs
    newRecipe.addInput(ITEM_WOOD, 5);
    //outputs
    newRecipe.addOutput(ITEM_CLUB, 1);
    //crafting stations
    newRecipe.addCraftingStation(NO_CRAFTING_STATION);
    //skills requirements
    newRecipe.addSkillRequirement(BARELY_USABLE, SKILL_WOOD_WORKING, 1);
    newRecipe.addSkillRequirement(BARELY_USABLE, SKILL_WEAPON_CRAFTING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_WOOD_WORKING, 10);
    newRecipe.addSkillExperience(SKILL_WEAPON_CRAFTING, 5);
    //add to array
    craftingRecipes.push_back(newRecipe);

    //recipe name -------------------------------------------------------------------------------------------
    newRecipe = CraftingRecipe("Rag Shirt");
    //inputs
    newRecipe.addInput(ITEM_CRUDE_HIDE, 10);
    //outputs
    newRecipe.addOutput(ITEM_RAG_BODY, 1);
    //crafting stations
    newRecipe.addCraftingStation(NO_CRAFTING_STATION);
    //skills requirements
    newRecipe.addSkillRequirement(BARELY_USABLE, SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillRequirement(BARELY_USABLE, SKILL_TAILORING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_TAILORING, 1);
    //add to array
    craftingRecipes.push_back(newRecipe);

    //recipe name -------------------------------------------------------------------------------------------
    newRecipe = CraftingRecipe("Rag Hat");
    //inputs
    newRecipe.addInput(ITEM_CRUDE_HIDE, 10);
    //outputs
    newRecipe.addOutput(ITEM_RAG_HAT, 1);
    //crafting stations
    newRecipe.addCraftingStation(NO_CRAFTING_STATION);
    //skills requirements
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_TAILORING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_TAILORING, 1);
    //add to array
    craftingRecipes.push_back(newRecipe);

    //recipe name -------------------------------------------------------------------------------------------
    newRecipe = CraftingRecipe("Rag Boots");
    //inputs
    newRecipe.addInput(ITEM_CRUDE_HIDE, 10);
    //outputs
    newRecipe.addOutput(ITEM_RAG_BOOTS, 1);
    //crafting stations
    newRecipe.addCraftingStation(NO_CRAFTING_STATION);
    //skills requirements
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_TAILORING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_TAILORING, 1);
    //add to array
    craftingRecipes.push_back(newRecipe);

    //recipe name -------------------------------------------------------------------------------------------
    newRecipe = CraftingRecipe("Rag Gloves");
    //inputs
    newRecipe.addInput(ITEM_CRUDE_HIDE, 10);
    //outputs
    newRecipe.addOutput(ITEM_RAG_GLOVES, 1);
    //crafting stations
    newRecipe.addCraftingStation(NO_CRAFTING_STATION);
    //skills requirements
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_TAILORING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_TAILORING, 1);
    //add to array
    craftingRecipes.push_back(newRecipe);

    //recipe name -------------------------------------------------------------------------------------------
    newRecipe = CraftingRecipe("Bronze Bar");
    //inputs
    newRecipe.addInput(ITEM_TIN_ORE, 5);
    newRecipe.addInput(ITEM_COPPER_ORE, 5);
    newRecipe.addInput(ITEM_COAL, 3);
    //outputs
    newRecipe.addOutput(ITEM_BRONZE_BAR, 1);
    //crafting stations
    newRecipe.addCraftingStation(CRAFTING_STATION_FURNACE);
    //skills requirements
    newRecipe.addSkillExperience(SKILL_METAL_WORKING, 1);
    newRecipe.addSkillExperience(SKILL_SMELTING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_METAL_WORKING, 1);
    newRecipe.addSkillExperience(SKILL_SMELTING, 1);
    //add to array
    craftingRecipes.push_back(newRecipe);

    //recipe name -------------------------------------------------------------------------------------------
    newRecipe = CraftingRecipe("Short Sword");
    //inputs
    newRecipe.addInput(ITEM_BRONZE_BAR, 5);
    //outputs
    newRecipe.addOutput(ITEM_SHORT_SWORD, 1);
    //crafting stations
    newRecipe.addCraftingStation(CRAFTING_STATION_FURNACE);
    //skills requirements
    newRecipe.addSkillExperience(SKILL_WEAPON_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_METAL_WORKING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_WEAPON_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_METAL_WORKING, 1);
    //add to array
    craftingRecipes.push_back(newRecipe);

    //recipe name -------------------------------------------------------------------------------------------
    newRecipe = CraftingRecipe("Long Sword");
    //inputs
    newRecipe.addInput(ITEM_BRONZE_BAR, 15);
    //outputs
    newRecipe.addOutput(ITEM_LONG_SWORD, 1);
    //crafting stations
    newRecipe.addCraftingStation(CRAFTING_STATION_FURNACE);
    //skills requirements
    newRecipe.addSkillExperience(SKILL_WEAPON_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_METAL_WORKING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_WEAPON_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_METAL_WORKING, 1);
    //add to array
    craftingRecipes.push_back(newRecipe);

    //recipe name -------------------------------------------------------------------------------------------
    newRecipe = CraftingRecipe("Bronze Armour");
    //inputs
    newRecipe.addInput(ITEM_BRONZE_BAR, 10);
    //outputs
    newRecipe.addOutput(ITEM_BRONZE_BODY, 1);
    //crafting stations
    newRecipe.addCraftingStation(CRAFTING_STATION_FURNACE);
    //skills requirements
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_METAL_WORKING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_METAL_WORKING, 1);
    //add to array
    craftingRecipes.push_back(newRecipe);

    //recipe name -------------------------------------------------------------------------------------------
    newRecipe = CraftingRecipe("Bronze Helm");
    //inputs
    newRecipe.addInput(ITEM_BRONZE_BAR, 10);
    //outputs
    newRecipe.addOutput(ITEM_BRONZE_HELM, 1);
    //crafting stations
    newRecipe.addCraftingStation(CRAFTING_STATION_FURNACE);
    //skills requirements
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_METAL_WORKING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_METAL_WORKING, 1);
    //add to array
    craftingRecipes.push_back(newRecipe);

    //recipe name -------------------------------------------------------------------------------------------
    newRecipe = CraftingRecipe("Bronze Boots");
    //inputs
    newRecipe.addInput(ITEM_BRONZE_BAR, 10);
    //outputs
    newRecipe.addOutput(ITEM_BRONZE_BOOTS, 1);
    //crafting stations
    newRecipe.addCraftingStation(CRAFTING_STATION_FURNACE);
    //skills requirements
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_METAL_WORKING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_METAL_WORKING, 1);
    //add to array
    craftingRecipes.push_back(newRecipe);

    //recipe name -------------------------------------------------------------------------------------------
    newRecipe = CraftingRecipe("Bronze Gloves");
    //inputs
    newRecipe.addInput(ITEM_BRONZE_BAR, 10);
    //outputs
    newRecipe.addOutput(ITEM_BRONZE_GLOVES, 1);
    //crafting stations
    newRecipe.addCraftingStation(CRAFTING_STATION_FURNACE);
    //skills requirements
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_METAL_WORKING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_METAL_WORKING, 1);
    //add to array
    craftingRecipes.push_back(newRecipe);

    //recipe name -------------------------------------------------------------------------------------------
    newRecipe = CraftingRecipe("Bronze Leggings");
    //inputs
    newRecipe.addInput(ITEM_BRONZE_BAR, 10);
    //outputs
    newRecipe.addOutput(ITEM_BRONZE_PANTS, 1);
    //crafting stations
    newRecipe.addCraftingStation(CRAFTING_STATION_FURNACE);
    //skills requirements
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_METAL_WORKING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_METAL_WORKING, 1);
    //add to array
    craftingRecipes.push_back(newRecipe);

    //recipe name -------------------------------------------------------------------------------------------
    newRecipe = CraftingRecipe("Rag Pants");
    //inputs
    newRecipe.addInput(ITEM_CRUDE_HIDE, 10);
    //outputs
    newRecipe.addOutput(ITEM_RAG_PANTS, 1);
    //crafting stations
    newRecipe.addCraftingStation(NO_CRAFTING_STATION);
    //skills requirements
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_TAILORING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_ARMOUR_CRAFTING, 1);
    newRecipe.addSkillExperience(SKILL_TAILORING, 1);
    //add to array
    craftingRecipes.push_back(newRecipe);

    //recipe name -------------------------------------------------------------------------------------------
    newRecipe = CraftingRecipe("Cooked Scrap Meat");
    //inputs
    newRecipe.addInput(ITEM_SCRAP_MEAT, 5);
    //outputs
    newRecipe.addOutput(ITEM_COOKED_SCRAP_MEAT, 1);
    //crafting stations
    //newRecipe.addCraftingStation(CRAFTING_STATION_CAMP_FIRE);
    newRecipe.addCraftingStation(CRAFTING_STATION_CAMP_FIRE);
    //skills requirements
    newRecipe.addSkillExperience(SKILL_COOKING, 1);
    //skill experience
    newRecipe.addSkillExperience(SKILL_COOKING, 1);
    //add to array
    craftingRecipes.push_back(newRecipe);
}

void RpgTileGridScene::scrollCamera() {
    int x, y, scrollSpeed;
    scrollSpeed = SCROLL_SPEED;
    if (controllerInterface->shiftOn)
    {
        scrollSpeed = scrollSpeed * 3;
    }
    x = controllerInterface->latestXpos;
    y = controllerInterface->latestYpos;

    if (x < engine->screenWidth * 0.01) {
        xOffset += scrollSpeed;
    }
    if (x > engine->screenWidth * 0.99) {
        xOffset -= scrollSpeed;
    }
    if (y < engine->screenHeight * 0.01) {
        yOffset += scrollSpeed;
    }
    if (y > engine->screenHeight * 0.99) {
        yOffset -= scrollSpeed;
    }
}

void RpgTileGridScene::setSaveGameName(std::string newSaveGameName)
{
    saveGameName = newSaveGameName;
}

std::string RpgTileGridScene::getSaveGameName()
{
    return saveGameName;
}

bool RpgTileGridScene::unitHasSkillsToCraftRecipe(RpgUnit* craftingUnit, CraftingRecipe* recipe)
{
    for (CraftingSkillRequirements skillRequirement : recipe->getSkillRequirements()[BARELY_USABLE])
    {
        if (skillRequirement.level > craftingUnit->getSkillLevel(skillRequirement.skill)) {
            return false;
        }
    }
    return true;

}

bool RpgTileGridScene::containerHasMatsForRecipe(std::vector<Item*>& container, CraftingRecipe* recipe)
{
    for (CraftingReagent input : recipe->getInputs())
    {
        if (!containerContainsAmount(input.item, input.qty, container)) {
            return false;
        }
    }
    return true;
}

void RpgTileGridScene::unitCraft(RpgUnit* craftingUnit, CraftingRecipe* recipe, int craftingStation)
{
    if (unitCanCraftRecipe(craftingUnit, recipe, craftingStation))
    {
        Item* crafteditem;
        for (CraftingReagent input : recipe->getInputs())
        {
            removeQtyFromContainer(input.item, input.qty, craftingUnit->inventory);
            menus[INVENTORY_MENU]->rebuildMenuElements();
            menus[CRAFTING_MENU]->rebuildMenuElements();
        }
        for (CraftingReagent output : recipe->getOutputs())
        {
            crafteditem = createNewItem(output.item);
            if (crafteditem->stackable)
            {
                crafteditem->stackSize = output.qty;
            }
            else 
            {
                for (int i = 0; i < output.qty - 1; i++)
                {
                    craftingUnit->addToInventory(createNewItem(output.item));
                }
            }
            craftingUnit->addToInventory(crafteditem);
        }
        for (auto skill : recipe->getSkillExperience()) {
            craftingUnit->addExp(skill.skill, skill.experience);
        }
    }
}

bool RpgTileGridScene::unitCanCraftRecipe(RpgUnit* craftingUnit, CraftingRecipe* recipe, int craftingStation)
{
    if (recipe->canBeCraftedAtStation(craftingStation) && containerHasMatsForRecipe(craftingUnit->inventory, recipe) && unitHasSkillsToCraftRecipe(craftingUnit, recipe))
    {
        return true;
    }
    return false;
}

std::vector<CraftingRecipe> RpgTileGridScene::getCraftingRecipes()
{
    return craftingRecipes;
}

CraftingRecipe RpgTileGridScene::getCraftingRecipe(int recipeIndex)
{
    if (recipeIndex == -1)
    {
        return CraftingRecipe();
    }
    return craftingRecipes[recipeIndex];
}


void addItemToContainer(Item* itemToAdd, std::vector<Item*>& container)
{
    if (itemToAdd->stackable)
    {
        bool itemAlreadyInInventory = false;
        for (auto item : container)
        {
            if (item->name == itemToAdd->name)
            {
                itemAlreadyInInventory = true;
                item->stackSize += itemToAdd->stackSize;
                break;
            }
        }
        if (!itemAlreadyInInventory)
        {
            container.push_back(itemToAdd);
        }
    }
    else {
        container.push_back(itemToAdd);
    }
}



void removeQtyFromContainer(int itemType, int qty, std::vector<Item*>& container)
{
    int qtyRemoved = 0;
    std::vector<Item*> itemsTodelete;
    for (auto item : container) {
        if (item->specificType == itemType)
        {
            item->stackSize -= (qty - qtyRemoved);
            if (item->stackSize > 0)
            {
                qtyRemoved += (qty - qtyRemoved);
                break;
            }
            else {
                itemsTodelete.push_back(item);
                qtyRemoved += (qty - qtyRemoved) + item->stackSize;
            }
        }
    }
    for (auto itemToDelete : itemsTodelete) {
        removeItemFromContainer(itemToDelete, container);
    }
}

bool containerContainsAmount(int itemSpecificType, int qty, std::vector<Item*>& container)
{
    int qtyInContainer = 0;

    for (auto item : container) {
        if (item->specificType == itemSpecificType) {
            qtyInContainer += item->stackSize;
            if (qtyInContainer >= qty)
            {
                return true;
            }
        }
    }

    return false;
}

Food* getSomeFoodFromContainer(std::vector<Item*>& container)
{
    Food* foodToReturn = nullptr;
    for (Item* item : container) {
        if (item->generalType == FOOD)
        {
            foodToReturn = (Food*) createNewItem(item->specificType);
            removeQtyFromContainer(item->specificType, 1, container);
            return foodToReturn;
        }
    }
    return foodToReturn;
}

Equipment* getItemForSlotFromContainer(std::vector<Item*>& container, int itemSlot)
{
    Equipment* itemToReturn = nullptr;
    for (Item* item : container) {
        if (item->equipable && ((Equipment*)item)->slot == itemSlot)
        {
            itemToReturn = (Equipment*)createNewItem(item->specificType);
            removeQtyFromContainer(item->specificType, 1, container);
            return itemToReturn;
        }
    }
    return itemToReturn;
}

int qtyInContainer(int itemType, std::vector<Item*>& container)
{
    int qtyInContainer = 0;
    for (auto item : container) {
        if (item->specificType == itemType)
        {
            qtyInContainer += item->stackSize;
        }
    }
    return qtyInContainer;
}

void removeItemFromContainer(int index, std::vector<Item*>& container)
{
    container.erase(container.begin() + index);
}

void removeItemFromContainer(Item* item, std::vector<Item*>& container)
{
    int remIndex = -1;
    for (size_t i = 0; i < container.size(); i++)
    {
        if (container[i] == item) {
            remIndex = i;
            break;
        }
    }
    if (remIndex == -1)
    {
        return;
    }
    removeItemFromContainer(remIndex, container);
}

void deleteItemFromContainer(int index, std::vector<Item*>& container)
{
    delete container[index];
    container.erase(container.begin() + index);
}

void deleteItemFromContainer(Item* item, std::vector<Item*>& container)
{
    int delIndex = -1;
    for (size_t i = 0; i < container.size(); i++)
    {
        if (container[i] == item) {
            delIndex = i;
            break;
        }
    }
    if (delIndex == -1)
    {
        return;
    }
    deleteItemFromContainer(delIndex, container);
}
