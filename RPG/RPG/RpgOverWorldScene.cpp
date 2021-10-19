#include "RpgOverWorldScene.h"
#include "Rat.h"
#include "DooDad.h"
#include "ItemShop.h"

RpgOverWorldScene::RpgOverWorldScene() : TileGridScene()
{
    init();
}

RpgOverWorldScene::RpgOverWorldScene(BaseGameEngine* gameEngine) : TileGridScene(gameEngine)
{
    init();
}

void RpgOverWorldScene::init() {
    controllerInterface = new RpgKeysMouseController();
    new DooDad(this, 3,3,3);
}

void RpgOverWorldScene::pickUpItem(Unit* unit, Item* item)
{
}

void RpgOverWorldScene::pickUpItemAtLocation(Unit* unit, int x, int y)
{
    if (currentZone->itemMap[x][y].size() > 0)
    {
        unit->inventory.push_back(currentZone->itemMap[x][y][0]);
        currentZone->itemMap[x][y].erase(currentZone->itemMap[x][y].begin());
        menus[INVENTORY_MENU]->update();
    }
}

void RpgOverWorldScene::loadZone(int zoneId)
{
    TileGridScene::loadZone(zoneId);
}

void RpgOverWorldScene::declareSceneAssets()
{
    TileGridScene::declareSceneAssets();
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
    texturesToLoad.insert({ RAT_IDLE_DOWN, "images/rat2.png" });
    texturesToLoad.insert({ BLUE_RAT_IDLE_DOWN, "images/BlueRat2.png" });
    texturesToLoad.insert({ RAT_KING_IDLE_DOWN, "images/RatKing2.png" });
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

void RpgOverWorldScene::setUpScene()
{
    TileGridScene::setUpScene();
    //set up teams
    teamRelations[PLAYER_TEAM][MONSTER_TEAM] = ENEMY;
    teamRelations[MONSTER_TEAM][PLAYER_TEAM] = ENEMY;

    //make units
    //createUnitAtLocation(currentZone->id, RAT, desiredTilesAcross / 2 - 3, desiredTilesDown / 2);
    //createUnitAtLocation(currentZone->id, RAT, desiredTilesAcross / 2 - 4, desiredTilesDown / 2);
    player = (Player*)createUnitAtLocation(currentZone->id, PLAYER, 5, 6);
    //player->gold = 100000;
    //player->addExp(COMBAT_EXPERIENCE, 250);
    //player->addExp(COMBAT_EXPERIENCE, 999999999);

    //createUnitAtLocation(currentZone->id, RAT, 4, 2);
    createUnitAtLocation(currentZone->id, SOLDIER, 6, 8);
    //createUnitAtLocation(currentZone->id, SOLDIER, 10, 10);
    createUnitAtLocation(1, SOLDIER, 3, 8);
    testUnit = createUnitAtLocation(currentZone->id, BLUE_RAT, 19, 5);
    //Location* testLocation = new Location{ 2, 0 };
    //testUnit->pathDirections = currentZone->getPathDirections(this, testUnit->tileLocation, testLocation);
    //testUnit->setTargetLocation(testLocation);
    createUnitAtLocation(2, RAT_KING, 26, 12);
    createUnitAtLocation(1, TOWNSPERSON, 11, 2);
    std::vector<Item*> startItems;
    startItems.push_back(new LongSword());
    startItems.push_back(new LinenBody());
    startItems.push_back(new LinenBoots());
    startItems.push_back(new LinenGloves());
    startItems.push_back(new LinenHat());
    startItems.push_back(new LinenPants());
    //addItemsToMap(currentZone->id, 5, 6, startItems);

    //buildings
    ItemShop* testBuilding;
    testBuilding = new ItemShop({
        {new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), nullptr, new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), nullptr, nullptr, nullptr, new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), nullptr, nullptr, nullptr, new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), nullptr, nullptr, nullptr, new BuildingTile(false, WOOD_WALL_TWO) },
        {new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO), new BuildingTile(false, WOOD_WALL_TWO) },
        });
    testBuilding->assignUnit(createUnitAtLocation(1, TOWNSPERSON, 13, 12));
    testBuilding->setItemsForSale({new Club(), new ShortSword(), new Mace(), new LongSword(), new RagBody(), new RagBoots(), new RagGloves(), new RagHat(), new RagPants(), new LinenBody(), new LinenBoots(), new LinenGloves(), new LinenHat(), new LinenPants()});
    zones[1]->addBuildingToLocation(testBuilding, 10 , 10);

    //build menus
    menus[RPG_OVERWORLD_MENU] = new OverWorldSceneMenu(this, BUILD_MENU, mainCanvasStartX, engine->screenHeight * 0.8, 0, engine->screenHeight * 0.2);
    menus[ITEM_SELL_MENU] = new ItemSellMenu(this, ITEM_SELL_MENU, engine->screenWidth * 0.25, engine->screenHeight * 0.5, mainCanvasStartX + engine->screenWidth * 0.01, engine->screenHeight * 0.15);
    menus[ITEM_BUY_MENU] = new ItemBuyMenu(this, ITEM_SELL_MENU, engine->screenWidth * 0.35, engine->screenHeight * 0.5, mainCanvasStartX + engine->screenWidth * 0.01, engine->screenHeight * 0.15);
    menus[INVENTORY_MENU] = new InventoryMenu(this, INVENTORY_MENU, engine->screenWidth * 0.25, engine->screenHeight * 0.5, mainCanvasStartX + engine->screenWidth * 0.01, engine->screenHeight * 0.15);
    menus[EQUIPPED_MENU] = new EquippedMenu(this, EQUIPPED_MENU, engine->screenWidth * 0.3, engine->screenHeight * 0.5, mainCanvasStartX + engine->screenWidth * 0.30, engine->screenHeight * 0.15);


    SDL_CreateThread(getPathThread, "getPathThread", (void*)this);
}

void RpgOverWorldScene::handleInput()
{
    TileGridScene::handleInput();
    InputMessage* message = new InputMessage();
    int tileCoords[2];
    
    controllerInterface->populateMessageQueue();
    while (controllerInterface->getNextMessage(message)) {
        switch (message->id)
        {
        case POINTER_MOVEMENT:
            //player->faceCoords(message->x, message->y);
            break;
        case END_SCENE:
            endScene();
            break;
        case SELECT_ON:
            getTileIndexFromScreenCoords(message->x, message->y, tileCoords);
            if (tileCoords[0] >= 0 && tileCoords[1] >= 0)
            {
                Unit* unitAtLocation = getUnitAtLocation(currentZone->id, tileCoords[0], tileCoords[1]);
                if (unitAtLocation != nullptr && unitAtLocation != player)
                {
                    addCommand(InputMessage(PERFORM_MAIN_ATTACK, message->x, message->y));
                    break;
                }
                else if (tileCoordsAreDisplayedMapTile(tileCoords[0], tileCoords[1]))
                {
                    if (currentZone->itemMap[tileCoords[0]][tileCoords[1]].size() > 0 && (std::abs(tileCoords[0] - player->tileLocation->x) <= 1) && (std::abs(tileCoords[1] - player->tileLocation->y) <= 1))
                    {
                        addCommand(InputMessage(PICK_UP_ITEM, tileCoords[0], tileCoords[1]));
                        break;
                    }
                }
            }
            addCommand(InputMessage(PERFORM_MAIN_ATTACK, message->x, message->y));
            break;
        case BUTTON_2_ON:
            addCommand(InputMessage(START_MOVE_UP, message->x, message->y));
            break;
        case BUTTON_3_ON:
            addCommand(InputMessage(START_MOVE_DOWN, message->x, message->y));
            break;
        case BUTTON_4_ON:
            addCommand(InputMessage(START_MOVE_LEFT, message->x, message->y));
            break;
        case BUTTON_5_ON:
            addCommand(InputMessage(START_MOVE_RIGHT, message->x, message->y));
            break;
        case BUTTON_6_ON:
            player->getLocationUnitIsFacing(tileCoords);
            addCommand(InputMessage(USER_ACTION, tileCoords[0], tileCoords[1]));
            break;
        case BUTTON_2_OFF:
            addCommand(InputMessage(STOP_MOVE_UP, message->x, message->y));
            break;
        case BUTTON_3_OFF:
            addCommand(InputMessage(STOP_MOVE_DOWN, message->x, message->y));
            break;
        case BUTTON_4_OFF:
            addCommand(InputMessage(STOP_MOVE_LEFT, message->x, message->y));
            break;
        case BUTTON_5_OFF:
            addCommand(InputMessage(STOP_MOVE_RIGHT, message->x, message->y));
            break;
        default:
            break;
        }
    }
    delete message;
}

void RpgOverWorldScene::sceneLogic()
{
    //call base class logic
    TileGridScene::sceneLogic();
    Location* soldierSpawn = new Location{ 4, 4 };
    Location* ratSpawn = new Location{32, 19};
    Location* ratSpawn2 = new Location{32, 2};


    //handle commands
    InputMessage* message = new InputMessage();
    while (getNextCommand(message)) {
        player->handleInput(message);
        switch (message->id)
        {
        case PICK_UP_ITEM:
            if (currentZone->itemMap[message->x][message->y].size() > 0 && (std::abs(message->x - player->tileLocation->x) <= 1) && (std::abs(message->y - player->tileLocation->y) <= 1)) {
                pickUpItemAtLocation(player, message->x, message->y);
            }
            break;
        case USER_ACTION:
            Unit* actionedUnit;
            actionedUnit = getUnitAtLocation(player->zone, message->x, message->y);
            if (actionedUnit != nullptr)
            {
                if (actionedUnit->assignedToBuilding != nullptr)
                {
                    actionedUnit->assignedToBuilding->onActionAssignedUnit(actionedUnit);
                }
            }
            break;
        default:
            break;
        }
    }
    
    for (auto zone :zones)
    {
        //spawn enemy units
        /*if (engine->getProbFromSigmoid(zone.second->getDifficulty() + 1, zone.second->getDevelopmentLevel() + 500) > engine->randomDouble() && zone.second->mobSpawn)
        {
            int targetCoords[2] = { 0, 0 };
            while (true)
            {
                targetCoords[0] = engine->randomInt(0, zone.second->tileMap[0].size() - 1);
                targetCoords[1] = engine->randomInt(0, zone.second->tileMap.size() - 1);
                if (mapTiles[zone.second->tileMap[targetCoords[1]][targetCoords[0]]].passable && getPortalAtLocation(zone.second, targetCoords[0], targetCoords[1]) == nullptr)
                {
                    break;
                }
            }
            if (getUnitAtLocation(zone.second->id, targetCoords[0], targetCoords[1]) == nullptr)
            {
                createUnitAtLocation(zone.second->id, RAT, targetCoords[0], targetCoords[1]);
            }
        }*/

        if (engine->getProbFromSigmoid(zone.second->getDifficulty() + 1, zone.second->getDevelopmentLevel() + 300) > engine->randomDouble() && zone.second->mobSpawn)
        {
            if (getUnitAtLocation(zone.second->id, ratSpawn->x, ratSpawn->y) == nullptr)
            {
                createUnitAtLocation(zone.second->id, RAT, ratSpawn->x, ratSpawn->y);
            }
        }

        if (engine->getProbFromSigmoid(zone.second->getDifficulty() + 1, zone.second->getDevelopmentLevel() + 300) > engine->randomDouble() && zone.second->mobSpawn)
        {
            if (getUnitAtLocation(zone.second->id, ratSpawn2->x, ratSpawn2->y) == nullptr)
            {
                createUnitAtLocation(zone.second->id, RAT, ratSpawn2->x, ratSpawn2->y);
            }
        }

        //spawn BlueRats
        if (engine->getProbFromSigmoid(zone.second->getDifficulty() + 1, zone.second->getDevelopmentLevel() + 4000) > engine->randomDouble() && zone.second->zoneName == "CaveOne")
        {
            int targetCoords[2] = { 0, 0 };
            while (true)
            {
                targetCoords[0] = engine->randomInt(0, zone.second->tileMap[0].size() - 1);
                targetCoords[1] = engine->randomInt(0, zone.second->tileMap.size() - 1);
                if (mapTiles[zone.second->tileMap[targetCoords[1]][targetCoords[0]]].passable && getPortalAtLocation(zone.second, targetCoords[0], targetCoords[1]) == nullptr)
                {
                    break;
                }
            }
            if (getUnitAtLocation(zone.second->id, targetCoords[0], targetCoords[1]) == nullptr)
            {
                createUnitAtLocation(zone.second->id, BLUE_RAT, targetCoords[0], targetCoords[1]);
            }
        }

        //spawn troops
        if (engine->getProbFromSigmoid(zone.second->getDifficulty() + 1, zone.second->getDevelopmentLevel() + 120) > engine->randomDouble() && zone.second->mobSpawn)
        {
            /*int targetCoords[2] = { 0, 0 };
            while (true)
            {
                targetCoords[0] = engine->randomInt(0, zone.second->tileMap[0].size() - 1);
                targetCoords[1] = engine->randomInt(0, zone.second->tileMap.size() - 1);
                if (mapTiles[zone.second->tileMap[targetCoords[1]][targetCoords[0]]].passable && getPortalAtLocation(zone.second, targetCoords[0], targetCoords[1]) == nullptr)
                {
                    break;
                }
            }
            if (getUnitAtLocation(zone.second->id, targetCoords[0], targetCoords[1]) == nullptr)
            {
                createUnitAtLocation(zone.second->id, SOLDIER, targetCoords[0], targetCoords[1]);
            }*/
            if (getUnitAtLocation(zone.second->id, soldierSpawn->x, soldierSpawn->y) == nullptr)
            {
                createUnitAtLocation(zone.second->id, SOLDIER, soldierSpawn->x, soldierSpawn->y)->setTargetLocation(new Location{ 19, 5 });
            }
        }
    }
    
    delete message;
}

void RpgOverWorldScene::renderScene()
{
    int tileCoords[2], screenCoords[2];
    TileGridScene::renderScene();
    renderHUD();
    //testUnit->updateAggro2();
    //getTileIndexFromScreenCoords(controllerInterface->latestXpos, controllerInterface->latestYpos, tileCoords);
    /*if (currentZone->isTilePassable(this, tileCoords[0], tileCoords[1]))
    {
        Location* testLocation;
        testLocation = new Location{ tileCoords[0], tileCoords[1] };
        for (auto location : currentZone->getPath(this, player->tileDestination, testLocation))
        {
            coordsFromTileIndex(location->x, location->y, screenCoords);
            engine->renderText("O", screenCoords[0], screenCoords[1], tileWidth, tileHeight, COLOR_BLUE);
        }
        delete testLocation;
    }*/
}

void RpgOverWorldScene::renderHUD()
{
    engine->renderText("Level: " + std::to_string(player->combatLevel), engine->screenWidth * 0.01, engine->screenHeight * 0.01, COLOR_WHITE);
    renderRectangle(engine->screenWidth * 0.01, engine->screenHeight * 0.045, engine->screenWidth * 0.05, engine->screenHeight * 0.01, COLOR_GREY);
    renderRectangle(engine->screenWidth * 0.01, engine->screenHeight * 0.045, (engine->screenWidth * 0.05) * (double) ((double) (player->combatExperience - player->combatExperienceLastLevel) / (double) (player->combatExperienceNextLevel - player->combatExperienceLastLevel)), engine->screenHeight * 0.01, COLOR_WHITE);
    engine->renderText("Health: " + std::to_string(player->health), engine->screenWidth * 0.01, engine->screenHeight * 0.06, COLOR_WHITE);
    renderRectangle(engine->screenWidth * 0.01, engine->screenHeight * 0.1, engine->screenWidth * 0.05, engine->screenHeight * 0.01, COLOR_GREY);
    renderRectangle(engine->screenWidth * 0.01, engine->screenHeight * 0.1, (engine->screenWidth * 0.05) * (double) ((double)player->health / (double)player->maxHealth), engine->screenHeight * 0.01, COLOR_RED);
    engine->renderText("Mana: " + std::to_string(player->mana), engine->screenWidth * 0.01, engine->screenHeight * 0.11, COLOR_WHITE);
    renderRectangle(engine->screenWidth * 0.01, engine->screenHeight * 0.15, engine->screenWidth * 0.05, engine->screenHeight * 0.01, COLOR_GREY);
    renderRectangle(engine->screenWidth * 0.01, engine->screenHeight * 0.15, (engine->screenWidth * 0.05) * (double)((double)player->mana / (double)player->maxMana), engine->screenHeight * 0.01, COLOR_BLUE);
    engine->renderText("Gold: " + std::to_string(player->gold), engine->screenWidth * 0.01, engine->screenHeight * 0.16, COLOR_GOLD);

}

//void RpgOverWorldScene::unitEntersTile(Unit* unit, int x, int y)
//{
//    zones[unit->zone]->unitEntersTile(unit, x, y);
//    if (unit->canGoThroughPortal)
//    {
//        ZonePortal* currentPortal = getPortalAtLocation(zones[unit->zone], unit->tileLocation->x, unit->tileLocation->y);
//        if (currentPortal != nullptr)
//        {
//            portalUnit(currentPortal, unit);
//        }
//
//        DooDad* currentDooDad = getDooDadAtLocation(zones[unit->zone], unit->tileLocation->x, unit->tileLocation->y);
//        if (currentDooDad != nullptr)
//        {
//            currentDooDad->walkOn(unit);
//        }
//    }
//}


//functions
int getPathThread(void* scene) {
    srand(time(NULL));
    SDL_SetThreadPriority(SDL_THREAD_PRIORITY_LOW);
    RpgOverWorldScene* rpgScene = static_cast <RpgOverWorldScene*> (scene);
    while (rpgScene->sceneRunning)
    {
        if(rpgScene->unitsNeedingPath.size() > 0)
        {
            Unit* unit = rpgScene->unitsNeedingPath.front();
            rpgScene->unitsNeedingPath.pop_front();
            try {
                std::vector<int> tempDirections;

                if (unit->targetUnit != nullptr)
                {
                    tempDirections = unit->scene->zones[unit->zone]->getPathDirectionsToUnit(rpgScene, unit->tileDestination, unit->targetUnit, unit);
                    if (tempDirections.size() > 0)
                    {
                        unit->pathDirections = tempDirections;
                        continue;
                    }
                    unit->getNewPathFailTick++;
                    if (unit->getNewPathFailTick >= unit->getNewPathFailLimit)
                    {
                        unit->getNewPathFailTick = 0;
                        unit->pathDirections = rpgScene->zones[unit->zone]->getPathDirectionsIgnoreAllunits(rpgScene, unit->tileDestination, unit->targetUnit->tileDestination);
                    }
                    continue;
                }
                else if (unit->targetLocation != nullptr) {
                    tempDirections = rpgScene->zones[unit->zone]->getPathDirections(rpgScene, unit->tileDestination, unit->targetLocation);
                    if (tempDirections.size() > 0)
                    {
                        unit->pathDirections = tempDirections;
                        continue;
                    }
                    unit->getNewPathFailTick++;
                    if (unit->getNewPathFailTick >= unit->getNewPathFailLimit)
                    {
                        unit->getNewPathFailTick = 0;
                        unit->pathDirections = rpgScene->zones[unit->zone]->getPathDirectionsIgnoreAllunits(rpgScene, unit->tileDestination, unit->targetLocation);
                    }
                    continue;
                }
            }
            catch (...) {
                continue;
            }
            continue;
        }
    }
    return 0;
}