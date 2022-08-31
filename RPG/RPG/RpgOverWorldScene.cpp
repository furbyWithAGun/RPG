#include "RpgOverWorldScene.h"
#include "DooDad.h"
#include "ItemShop.h"
#include "Player.h"
#include "Rat.h"
#include "RatKing.h"
#include "WhiteRat.h"
#include "Soldier.h"
#include "TownsPerson.h"
#include "DooDadFactory.h"

RpgOverWorldScene::RpgOverWorldScene() : RpgTileGridScene()
{
    init();
}

RpgOverWorldScene::RpgOverWorldScene(BaseGameEngine* gameEngine) : RpgTileGridScene(gameEngine)
{
    init();
}

void RpgOverWorldScene::init() {

    buildCraftingRecipes();
    controllerInterface = new RpgKeysMouseController();
    testUnit = nullptr;
    displayHud = true;
    for (size_t i = 1; i < MAX_NUM_SQUAD_UNITS; i++)
    {
        squadUnits[i] = nullptr;
    }
    saveGameName = NEW_GAME_SAVE_FILE;
    pathfindThreadActive = false;
    aggroThreadActive = false;
}

void RpgOverWorldScene::pickUpItem(RpgUnit* unit, Item* item)
{
}

int RpgOverWorldScene::getUnitTypeByDifficulty(int difficulty)
{
    return engine->pickElementByProbability(monsterTable[difficulty]);
}

void RpgOverWorldScene::setUpMonsterTable()
{
    monsterTable[1] = { {1.0, RAT} };
    monsterTable[2] = { {0.5, RAT}, {0.5, WHITE_RAT} };
    monsterTable[3] = { {0.2, RAT}, {0.5, WHITE_RAT}, {0.3, SKELETON} };
    monsterTable[4] = { {0.05, RAT}, {0.3, WHITE_RAT}, {0.65, SKELETON} };
    monsterTable[5] = { {0.2, WHITE_RAT}, {0.8, SKELETON} };
    monsterTable[6] = { {1.0, SKELETON} };
}



void RpgOverWorldScene::saveGame()
{
    saveZones(saveGameName);
}

void RpgOverWorldScene::setCurrentZone(int zoneId)
{
    RpgTileGridScene::setCurrentZone(zoneId);
}

void RpgOverWorldScene::declareSceneAssets()
{
    RpgTileGridScene::declareSceneAssets();
}

void RpgOverWorldScene::setUpScene()
{
    Building::resetUid();
    Unit::resetUid();
    RpgTileGridScene::setUpScene(saveGameName);
    if (saveGameName == SAVES_FILE_PATH + NEW_GAME_SAVE_FILE)
    {
        player = (Player*)createUnitAtLocation(0, PLAYER, 104, 23);
        //addItemsToMap(0, 104, 23, { createNewItem(ITEM_BRONZE_BODY) });
        //addItemsToMap(0, 104, 23, { createNewItem(ITEM_BRONZE_HELM) });
        //addItemsToMap(0, 104, 23, { createNewItem(ITEM_BRONZE_GLOVES) });
        //addItemsToMap(0, 104, 23, { createNewItem(ITEM_BRONZE_BOOTS) });
        //addItemsToMap(0, 104, 23, { createNewItem(ITEM_BRONZE_PANTS) });
        //player = (Player*)createUnitAtLocation(4, PLAYER, 18, 14);
        //squadUnits[1] = (AiUnit*)createUnitAtLocation(currentZone->id, SOLDIER, 9, 25);
        //squadUnits[1]->doesRandomMovement = false;
        //createUnitAtLocation(currentZone->id, SOLDIER, 10, 27);
        //createUnitAtLocation(currentZone->id, SOLDIER, 15, 27);
        //createUnitAtLocation(currentZone->id, SOLDIER, 16, 27);
        //createUnitAtLocation(1, SOLDIER, 3, 8);
        //getZones()[currentZone->id]->addDooDadToLocation(createNewUnitSpawner(this, RAT, currentZone->id), 9, 11);
        //getZones()[currentZone->id]->addDooDadToLocation(createNewUnitSpawner(this, RAT, currentZone->id), 48, 23);
        //getZones()[currentZone->id]->addDooDadToLocation(createNewUnitSpawner(this, RAT, currentZone->id), 29, 36);
        //createUnitAtLocation(2, RAT_KING, 29, 1);
        //createUnitAtLocation(3, SKELETON_KING, 28, 28);
    }

    currentZone = getZone(player->getZone());
    setUpMonsterTable();
    //set up teams
    teamRelations[PLAYER_TEAM][MONSTER_TEAM] = ENEMY;
    teamRelations[MONSTER_TEAM][PLAYER_TEAM] = ENEMY;

    //make units
    //createUnitAtLocation(currentZone->id, RAT, desiredTilesAcross / 2 - 3, desiredTilesDown / 2);
    //createUnitAtLocation(currentZone->id, RAT, desiredTilesAcross / 2 - 4, desiredTilesDown / 2);
    
    //
    
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_SHORT_SWORD)});
   // addItemsToMap(0, 5, 6, {createNewItem(ITEM_RAG_HAT)});
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_RAG_BODY)});
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_RAG_BOOTS)});
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_RAG_GLOVES)});
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_RAG_PANTS)});
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_LEATHER_BODY)});
    

    //createUnitAtLocation(currentZone->id, RAT, 8, 8);
    
    
    //build menus
    menus[RPG_OVERWORLD_MENU] = new OverWorldSceneMenu(this, RPG_OVERWORLD_MENU, mainCanvasStartX, engine->screenHeight * 0.8, 0, engine->screenHeight * 0.2);
    menus[TOWN_BUILD_MENU] = new TownBuildMenu(this, TOWN_BUILD_MENU, mainCanvasStartX, engine->screenHeight * 0.8, 0, engine->screenHeight * 0.2);
    //menus[ITEM_SELL_MENU] = new ItemSellMenu(this, ITEM_SELL_MENU, engine->screenWidth * 0.25, engine->screenHeight * 0.5, mainCanvasStartX + engine->screenWidth * 0.01, engine->screenHeight * 0.15);
    //menus[ITEM_BUY_MENU] = new ItemBuyMenu(this, ITEM_SELL_MENU, engine->screenWidth * 0.35, engine->screenHeight * 0.5, mainCanvasStartX + engine->screenWidth * 0.01, engine->screenHeight * 0.15);
    menus[ITEM_SHOP_MENU] = new ItemShopMenu(this, ITEM_SHOP_MENU, engine->screenWidth * 0.35, engine->screenHeight * 0.5, mainCanvasStartX + engine->screenWidth * 0.3, engine->screenHeight * 0.2);
    menus[TRANSFER_ITEMS_MENU] = new TransferItemsMenu(this, ITEM_SHOP_MENU, engine->screenWidth * 0.35, engine->screenHeight * 0.5, mainCanvasStartX + engine->screenWidth * 0.3, engine->screenHeight * 0.2);
    menus[INVENTORY_MENU] = new InventoryMenu(this, INVENTORY_MENU);
    menus[OTHER_UNIT_INVENTORY_MENU] = new OtherUnitInventoryMenu(this, OTHER_UNIT_INVENTORY_MENU);
    //menus[EQUIPPED_MENU] = new EquippedMenu(this, EQUIPPED_MENU, engine->screenWidth * 0.3, engine->screenHeight * 0.5, mainCanvasStartX + engine->screenWidth * 0.30, engine->screenHeight * 0.15);
    menus[SAVE_GAME_MENU] = new SaveGameMenu(this, SAVE_GAME_MENU, engine->screenWidth * 0.3, engine->screenHeight * 0.5, mainCanvasStartX + engine->screenWidth * 0.30, engine->screenHeight * 0.15);
    menus[CRAFTING_MENU] = new CraftingMenu(this, CRAFTING_MENU);


    //setup town
    ((RpgZone*)getZones()[1])->zoneType = ZONE_RPG_TOWN;
    //aggroThread = SDL_CreateThread(updateAggroThread, "updateAggroThread", (void*)this);

    //h4x
    ((RpgTown*)getZones()[1])->addPopulation(30);
    //addItemToContainer(createNewItem(ITEM_APPLE), ((RpgTown*)getZones()[1])->getTownInventory());
    //addItemToContainer(createNewItem(ITEM_APPLE), ((RpgTown*)getZones()[1])->getTownInventory());
    //addItemToContainer(createNewItem(ITEM_APPLE), ((RpgTown*)getZones()[1])->getTownInventory());
    //addItemToContainer(createNewItem(ITEM_APPLE), ((RpgTown*)getZones()[1])->getTownInventory());
    //Item* itemToDrop = createNewItem(ITEM_WOOD);
    //itemToDrop->stackSize = 1000;
    //addItemsToMap(0, 10, 26, { itemToDrop });
    //itemToDrop = createNewItem(ITEM_APPLE);
    //itemToDrop->stackSize = 10000;
    //addItemsToMap(0, 10, 26, { itemToDrop });

    //player->gold = 5000;
    //player->gold = 100000;
    //player->addExp(COMBAT_EXPERIENCE, 250);
    //player->addExp(SKILL_COMBAT, 999999999);
    //player->health = 9999999;
    //player->maxHealth = 9999999;
    //((RpgTown*)getZones()[1])->addPopulation(1000);
}

void RpgOverWorldScene::handleInput()
{
    RpgTileGridScene::handleInput();
    InputMessage* message = new InputMessage();
    double tileCoords[2];
    
    controllerInterface->populateMessageQueue();
    while (controllerInterface->getNextMessage(message)) {
        if (menus[TOWN_BUILD_MENU]->isActive)
        {
            switch (message->id)
            {
            case POINTER_MOVEMENT:
                //player->faceCoords(message->x, message->y);
                break;
            case END_SCENE:
                endScene();
                break;
            case SELECT_ON:
                if (placingBuilding && coordsAreOnDisplayedMapTile(message->x, message->y))
                {
                    getTileIndexFromScreenCoords(message->x, message->y, tileCoords);
                    int buildingXoffset = buildingBeingPlaced.tileMap.size() / 2;
                    int buildingYoffset = buildingBeingPlaced.tileMap[0].size() / 2;
                    if (buildingCanBePlacedAtLocation(&buildingBeingPlaced, currentZone, tileCoords[0] - buildingXoffset, tileCoords[1] - buildingYoffset)) {
                        addCommand(InputMessage(OVERWORLD_PLACE_BUILDING, tileCoords[0] - buildingXoffset, tileCoords[1] - buildingYoffset, buildingBeingPlaced.type));
                    }
                }
                break;
            default:
                break;
            }
        } 
        else
        {
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
                    RpgUnit* unitAtLocation = getUnitAtLocation(currentZone->id, tileCoords[0], tileCoords[1]);
                    if (unitAtLocation != nullptr && unitAtLocation != player)
                    {
                        if (getTeamStatus(player->team, unitAtLocation->team) == ALLY)
                        {
                            //logic for clicking on allied units
                            break;
                        }
                        addCommand(InputMessage(PERFORM_MAIN_ATTACK, message->x, message->y));
                        break;
                    }

                    DooDad* dooDadAtLocation = currentZone->getDooDadAtLocation(tileCoords[0], tileCoords[1]);
                    if (dooDadAtLocation != nullptr && dooDadAtLocation->canBeDamaged)
                    {
                        addCommand(InputMessage(PERFORM_MAIN_ATTACK, message->x, message->y));
                        break;
                    }

                    else if (tileCoordsAreDisplayedMapTile(tileCoords[0], tileCoords[1]))
                    {
                        if (currentZone->getItemsAtLocation(tileCoords[0], tileCoords[1]).size() > 0 && (std::abs(tileCoords[0] - player->tileLocation->x) <= 1) && (std::abs(tileCoords[1] - player->tileLocation->y) <= 1))
                        {
                            addCommand(InputMessage(PICK_UP_ITEM, tileCoords[0], tileCoords[1]));
                            break;
                        }
                    }
                    DooDad* targetDooDad;
                    targetDooDad = currentZone->getDooDadAtLocation(tileCoords[0], tileCoords[1]);
                    if (tileCoordsAreDisplayedMapTile(tileCoords[0], tileCoords[1]) && targetDooDad != nullptr)
                    {
                        if ((std::abs(tileCoords[0] - player->tileLocation->x) <= 1) && (std::abs(tileCoords[1] - player->tileLocation->y) <= 1))
                        {
                            addCommand(InputMessage(OVERWORLD_STRIKE, tileCoords[0], tileCoords[1]));
                            break;
                        }
                    }
                }
                addCommand(InputMessage(PERFORM_MAIN_ATTACK, message->x, message->y));
                break;
            case BUTTON_1_OFF:
                if (controllerInterface->ctrlOn)
                {
                    getTileIndexFromScreenCoords(message->x, message->y, tileCoords);
                    if (tileCoords[0] >= 0 && tileCoords[1] >= 0)
                    {
                        RpgUnit* unitAtLocation = getUnitAtLocation(currentZone->id, tileCoords[0], tileCoords[1]);
                        if (unitAtLocation != nullptr)
                        {
                            ((OtherUnitInventoryMenu*)menus[OTHER_UNIT_INVENTORY_MENU])->open(unitAtLocation);
                            menus[INVENTORY_MENU]->open();
                        }
                    }
                }
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
            case BUTTON_7_ON:
                if (!menus[INVENTORY_MENU]->isActive)
                {
                    openMenu(INVENTORY_MENU);
                }
                else {
                    closeMenu(INVENTORY_MENU);
                }
                break;
            case BUTTON_8_ON:
                getTileIndexFromScreenCoords(message->x, message->y, tileCoords);
                if (controllerInterface->ctrlOn)
                {
                    addCommand(InputMessage(OVERWORLD_ASSIGN_UNIT, tileCoords[0], tileCoords[1], 1));
                }
                else if (squadUnits[1] != nullptr) {
                    addCommand(InputMessage(OVERWORLD_COMMAND_UNIT, tileCoords[0], tileCoords[1], 1));
                }
                break;
            case BUTTON_9_ON:
                getTileIndexFromScreenCoords(message->x, message->y, tileCoords);
                if (controllerInterface->ctrlOn)
                {
                    addCommand(InputMessage(OVERWORLD_ASSIGN_UNIT, tileCoords[0], tileCoords[1], 2));
                }
                else if (squadUnits[2] != nullptr) {
                    addCommand(InputMessage(OVERWORLD_COMMAND_UNIT, tileCoords[0], tileCoords[1], 2));
                }
                break;
            case BUTTON_10_ON:
                getTileIndexFromScreenCoords(message->x, message->y, tileCoords);
                if (controllerInterface->ctrlOn)
                {
                    addCommand(InputMessage(OVERWORLD_ASSIGN_UNIT, tileCoords[0], tileCoords[1], 3));
                }
                else if (squadUnits[3] != nullptr) {
                    addCommand(InputMessage(OVERWORLD_COMMAND_UNIT, tileCoords[0], tileCoords[1], 3));
                }
                break;
            case BUTTON_11_ON:
                getTileIndexFromScreenCoords(message->x, message->y, tileCoords);
                if (controllerInterface->ctrlOn)
                {
                    addCommand(InputMessage(OVERWORLD_ASSIGN_UNIT, tileCoords[0], tileCoords[1], 4));
                }
                else if (squadUnits[4] != nullptr) {
                    addCommand(InputMessage(OVERWORLD_COMMAND_UNIT, tileCoords[0], tileCoords[1], 4));
                }
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
        
    }
    if (controllerInterface->selectOn)
    {
        getTileIndexFromScreenCoords(controllerInterface->latestXpos, controllerInterface->latestYpos, tileCoords);
        if (tileCoords[0] >= 0 && tileCoords[1] >= 0)
        {
            RpgUnit* unitAtLocation = getUnitAtLocation(currentZone->id, tileCoords[0], tileCoords[1]);
            if (unitAtLocation != nullptr && unitAtLocation != player)
            {
                if (getTeamStatus(player->team, unitAtLocation->team) == ALLY)
                {
                    //logic for allied unit hold LMB
                }
                else {
                    addCommand(InputMessage(PERFORM_MAIN_ATTACK, controllerInterface->latestXpos, controllerInterface->latestYpos));
                }
                
            }

            DooDad* dooDadAtLocation = currentZone->getDooDadAtLocation(tileCoords[0], tileCoords[1]);
            if (dooDadAtLocation != nullptr && dooDadAtLocation->canBeDamaged)
            {
                addCommand(InputMessage(PERFORM_MAIN_ATTACK, message->x, message->y));
            }
        }
    }
    delete message;
}

void RpgOverWorldScene::sceneLogic()
{
    //if (unitsNeedingPath.size() > 0 && pathfindThreadActive == false)
    //{
    //    pathFindingThread = SDL_CreateThread(getPathThread, "getPathThread", (void*)this);
    //    pathfindThreadActive = true;
    //}
    //call base class logic
    RpgTileGridScene::sceneLogic();
    //Location* soldierSpawn = new Location{ 22, 27 };
    //Location* ratSpawn = new Location{32, 11};
    //Location* ratSpawn2 = new Location{7, 34};


    //handle commands
    InputMessage* message = new InputMessage();
    while (getNextCommand(message)) {
        player->handleInput(message);
        switch (message->id)
        {
        case OVERWORLD_PLAYER_CRAFT:
            unitCraft(player, &getCraftingRecipe(message->misc), message->params[0]);
            break;
        case OVERWORLD_PLACE_BUILDING:
            if (((RpgZone*)currentZone)->zoneType == ZONE_RPG_TOWN)
            {
                if (buildingCanBePlacedAtLocation(&buildingBeingPlaced, currentZone, message->x, message->y) && townCanAffordBuilding(&buildingBeingPlaced, (RpgTown*)currentZone)) {
                    createBuildingAtLocation(currentZone, message->misc, LEFT, message->x, message->y);
                    payBuildingCosts(&buildingBeingPlaced, (RpgTown*)currentZone);
                }
                if (!townCanAffordBuilding(&buildingBeingPlaced, (RpgTown*)currentZone))
                {
                    ((TownBuildMenu*)menus[TOWN_BUILD_MENU])->cancelBuild();
                }
            }
            else if (((RpgZone*)currentZone)->zoneType == ZONE_RPG_PROVINCE) {
                if (buildingCanBePlacedAtLocation(&buildingBeingPlaced, currentZone, message->x, message->y) && playerCanAffordBuilding(&buildingBeingPlaced)) {
                    createBuildingAtLocation(currentZone, message->misc, LEFT, message->x, message->y);
                    payBuildingCosts(&buildingBeingPlaced, (RpgTown*)currentZone);
                }
                if (!playerCanAffordBuilding(&buildingBeingPlaced))
                {
                    ((TownBuildMenu*)menus[TOWN_BUILD_MENU])->cancelBuild();
                }
            }
            break;
        case OVERWORLD_COMMAND_UNIT:
            if (squadUnits[message->misc] != nullptr)
            {
                squadUnits[message->misc]->setTargetLocation(new Location{ message->x, message->y });
                if (getPortalAtLocation(currentZone, message->x, message->y))
                {
                    squadUnits[message->misc]->canGoThroughPortal = true;
                }
            }
            break;
        case OVERWORLD_ASSIGN_UNIT:
            RpgUnit* unitAtLocation;
            unitAtLocation = getUnitAtLocation(currentZone->id, message->x, message->y);
            if (unitAtLocation != nullptr && unitAtLocation->team == player->team && unitAtLocation == squadUnits[message->misc])
            {
                ((AiUnit*)squadUnits[message->misc])->doesRandomMovement = true;
                ((AiUnit*)squadUnits[message->misc])->adjustPathRate = DEFAULT_ADJUST_PATH_RATE;
                squadUnits[message->misc]= nullptr;
            }
            else if (unitAtLocation != nullptr && unitAtLocation->team == player->team && unitAtLocation != player)
            {
                if (squadUnits[message->misc] != nullptr) {
                    ((AiUnit*)squadUnits[message->misc])->doesRandomMovement = true;
                    ((AiUnit*)squadUnits[message->misc])->adjustPathRate = DEFAULT_ADJUST_PATH_RATE;
                }
                squadUnits[message->misc] = (AiUnit*)unitAtLocation;
                ((AiUnit*)unitAtLocation)->doesRandomMovement = false;
                ((AiUnit*)squadUnits[message->misc])->adjustPathRate = 0;
                ((AiUnit*)squadUnits[message->misc])->canGoThroughPortal = false;
                ((AiUnit*)squadUnits[message->misc])->canGoThroughPortal = false;
                if (squadUnits[message->misc]->assignedToBuilding) {
                    squadUnits[message->misc]->assignedToBuilding->unAssignUnit(squadUnits[message->misc]);
                }
            }
            break;
        default:
            break;
        }
    }

    for (size_t i = 1; i < MAX_NUM_SQUAD_UNITS; i++)
    {
        if (squadUnits[i] && squadUnits[i]->getZone() == currentZone->id) {
            //if (squadUnits[i]->getTargetLocation() == nullptr && currentZone->manhattenDistance(squadUnits[i]->tileLocation, player->tileLocation) > 5)
            if (currentZone->manhattenDistance(squadUnits[i]->tileLocation, player->tileLocation) > 5)
            {
                squadUnits[i]->setTargetLocation(player->tileLocation);
            }
        }
        if (squadUnits[i] && !squadUnits[i]->speedUp && currentZone->manhattenDistance(squadUnits[i]->tileLocation, player->tileLocation) > 10)
        {
            squadUnits[i]->setAttributeLevel(UNIT_STAT_SPEED, squadUnits[i]->getAttributeLevel(UNIT_STAT_SPEED) * 2);
            squadUnits[i]->speedUp = true;
        }
        else if(squadUnits[i] && squadUnits[i]->speedUp){
            squadUnits[i]->setAttributeLevel(UNIT_STAT_SPEED, squadUnits[i]->getAttributeLevel(UNIT_STAT_SPEED) / 2);
            squadUnits[i]->speedUp = false;
        }
    }

    delete message;
    message = nullptr;
    
    for (auto zoneMap : getZones())
    {
        if (!zoneMap.second)
        {
            std::cout << "\ninvalid zone in array";
            continue;
        }
        RpgZone* zone = (RpgZone*)zoneMap.second;
        if (zone->zoneType == ZONE_RPG_PROVINCE && engine->getProbFromSigmoid(zone->getDifficulty() + 1, zone->getDevelopmentLevel() + 10000 + zone->numUnitSpawners * 4000) > engine->randomDouble())
        {
            int targetCoords[2] = { 0, 0 };
            int attempts = 0;
            bool foundLocation = false;
            while (true)
            {
                attempts++;
                targetCoords[0] = engine->randomInt(0, zone->tileMap.size() - 1);
                targetCoords[1] = engine->randomInt(0, zone->tileMap[0].size() - 1);
                if (isTilePassable(zone->id, targetCoords[0], targetCoords[1]))
                {
                    foundLocation = true;
                    break;
                }
                if (attempts > 50)
                {
                    break;
                }
            }
            if (foundLocation && getUnitAtLocation(zone->id, targetCoords[0], targetCoords[1]) == nullptr)
            {
                getZones()[zone->id]->addDooDadToLocation(createNewUnitSpawner(this, getUnitTypeByDifficulty(zone->difficulty), zone->id), targetCoords[0], targetCoords[1]);
            }
        } else if (zone->zoneType == ZONE_RPG_CAVE && engine->getProbFromSigmoid(zone->getDifficulty() + 1, zone->getDevelopmentLevel() + 5000) > engine->randomDouble())
        {
            int targetCoords[2] = { 0, 0 };
            while (true)
            {
                targetCoords[0] = engine->randomInt(0, zone->tileMap.size() - 1);
                targetCoords[1] = engine->randomInt(0, zone->tileMap[0].size() - 1);
                if (mapTiles[zone->tileMap[targetCoords[0]][targetCoords[1]]].passable && getPortalAtLocation(zone, targetCoords[0], targetCoords[1]) == nullptr)
                {
                    break;
                }
            }
            if (getUnitAtLocation(zone->id, targetCoords[0], targetCoords[1]) == nullptr)
            {
                createUnitAtLocation(zone->id, getUnitTypeByDifficulty(zone->difficulty), targetCoords[0], targetCoords[1]);
            }
        }
    }

    if (!aggroThreadActive)
    {
        aggroThreadActive = true;
        SDL_CreateThread(updateAggroThread, "updateAggroThread", (void*)this);
    }
    if (!pathfindThreadActive)
    {
        pathfindThreadActive = true;
        SDL_CreateThread(getPathThread, "getPathThread", (void*)this);
    }
}

void RpgOverWorldScene::renderScene()
{
    double tileCoords[2], screenCoords[2];
    //SDL_AtomicLock(&TileGridUnitLock);
    if (!player->cameraFollowPlayer)
    {
        scrollCamera();
    }
    else {
        player->updateCamera();
    }
    RpgTileGridScene::renderScene();
    //SDL_AtomicUnlock(&TileGridUnitLock);
    if (displayHud)
    {
        renderHUD();
    }

    for (size_t i = 1; i < MAX_NUM_SQUAD_UNITS; i++)
    {
        if (controllerInterface->ctrlOn && squadUnits[i] != nullptr && squadUnits[i]->getZone() == currentZone->id) {
            double coords[2];
            double destCoords[2];
            coordsFromTileIndex(squadUnits[i]->tileLocation->x, squadUnits[i]->tileLocation->y, coords);
            coordsFromTileIndex(squadUnits[i]->tileDestination->x, squadUnits[i]->tileDestination->y, destCoords);
            int xpos = coords[0] + (destCoords[0] - coords[0]) * (1 - squadUnits[i]->leftToMove);
            int ypos = coords[1] + (destCoords[1] - coords[1]) * (1 - squadUnits[i]->leftToMove);
            engine->renderText(std::to_string(i), xpos, ypos, tileWidth, tileHeight);
        }
    }

    if (placingBuilding && coordsAreOnDisplayedMapTile(controllerInterface->latestXpos, controllerInterface->latestYpos) && !mouseOnAMenu())
    {
        getTileIndexFromScreenCoords(controllerInterface->latestXpos, controllerInterface->latestYpos, tileCoords);
        int buildingXoffset = buildingBeingPlaced.tileMap.size() / 2;
        int buildingYoffset = buildingBeingPlaced.tileMap[0].size() / 2;
        bool buldingCanBePlaced = buildingCanBePlacedAtLocation(&buildingBeingPlaced, currentZone, tileCoords[0] - buildingXoffset, tileCoords[1] - buildingYoffset);

        for (int x = 0; x < buildingBeingPlaced.tileMap.size(); x++)
        {
            for (int y = 0; y < buildingBeingPlaced.tileMap[x].size(); y++) {
                coordsFromTileIndex(tileCoords[0] + x - buildingXoffset, tileCoords[1] + y - buildingYoffset, screenCoords);
                if (buildingBeingPlaced.tileMap[x][y] != nullptr) {
                    if (!buldingCanBePlaced)
                    {
                        SDL_SetTextureColorMod(engine->textures[buildingBeingPlaced.tileMap[x][y]->textureKey].texture, 255, 125, 125);
                        SDL_SetTextureAlphaMod(engine->textures[buildingBeingPlaced.tileMap[x][y]->textureKey].texture, 195);
                    }
                    else {
                        SDL_SetTextureColorMod(engine->textures[buildingBeingPlaced.tileMap[x][y]->textureKey].texture, 255, 255, 255);
                        SDL_SetTextureAlphaMod(engine->textures[buildingBeingPlaced.tileMap[x][y]->textureKey].texture, 255);
                    }
                    renderTexture(buildingBeingPlaced.tileMap[x][y]->textureKey, screenCoords[0] - tileWidth, screenCoords[1] - tileWidth, tileWidth * 3, tileHeight * 3);
                    SDL_SetTextureColorMod(engine->textures[buildingBeingPlaced.tileMap[x][y]->textureKey].texture, 255, 255, 255);
                    SDL_SetTextureAlphaMod(engine->textures[buildingBeingPlaced.tileMap[x][y]->textureKey].texture, 255);
                }
            }
        }
    }
    //engine->renderRectangle(700,150,550,650, COLOR_BLUE);
}

void RpgOverWorldScene::renderHUD()
{
    engine->renderText("Level: " + std::to_string(player->combatLevel), engine->screenWidth * 0.01, engine->screenHeight * 0.01, COLOR_WHITE);
    renderRectangle(engine->screenWidth * 0.01, engine->screenHeight * 0.045, engine->screenWidth * 0.05, engine->screenHeight * 0.01, COLOR_GREY);
    renderRectangle(engine->screenWidth * 0.01, engine->screenHeight * 0.045, (engine->screenWidth * 0.05) * (double) ((double) (player->combatExperience - player->combatExperienceLastLevel) / (double) (player->combatExperienceNextLevel - player->combatExperienceLastLevel)), engine->screenHeight * 0.01, COLOR_WHITE);
    engine->renderText("Health: " + std::to_string(player->getHealth()), engine->screenWidth * 0.01, engine->screenHeight * 0.06, COLOR_WHITE);
    renderRectangle(engine->screenWidth * 0.01, engine->screenHeight * 0.1, engine->screenWidth * 0.05, engine->screenHeight * 0.01, COLOR_GREY);
    renderRectangle(engine->screenWidth * 0.01, engine->screenHeight * 0.1, (engine->screenWidth * 0.05) * (double) ((double)player->getHealth() / (double)player->getAttributeLevel(UNIT_STAT_MAX_HEALTH)), engine->screenHeight * 0.01, COLOR_RED);
    engine->renderText("Mana: " + std::to_string(player->mana), engine->screenWidth * 0.01, engine->screenHeight * 0.11, COLOR_WHITE);
    renderRectangle(engine->screenWidth * 0.01, engine->screenHeight * 0.15, engine->screenWidth * 0.05, engine->screenHeight * 0.01, COLOR_GREY);
    renderRectangle(engine->screenWidth * 0.01, engine->screenHeight * 0.15, (engine->screenWidth * 0.05) * (double)((double)player->mana / (double)player->getAttributeLevel(UNIT_STAT_MAX_MANA)), engine->screenHeight * 0.01, COLOR_BLUE);
    engine->renderText("Gold: " + std::to_string(player->gold), engine->screenWidth * 0.01, engine->screenHeight * 0.16, COLOR_GOLD);

    for (size_t i = 0; i < player->foodEffects.size(); i++)
    {
        engine->renderTexture(player->foodEffects[i]->texture, mainCanvasStartX + engine->screenWidth * 0.02 * i, engine->screenHeight * 0.95);
        renderRectangle(mainCanvasStartX + engine->screenWidth * 0.02 * i + engine->screenWidth * 0.02, engine->screenHeight * 0.99, engine->screenWidth * 0.004, (engine->screenHeight * 0.05) * ((double)((double)player->foodEffects[i]->tick - (double)player->foodEffects[i]->duration) / (double)player->foodEffects[i]->duration), COLOR_WHITE);
    }
}

void RpgOverWorldScene::destroyUnit(RpgUnit* unit)
{
    //remove unit from squad
    for (size_t i = 1; i < MAX_NUM_SQUAD_UNITS; i++)
    {
        if (squadUnits[i] == unit)
        {
            squadUnits[i] = nullptr;
        }
    }

    RpgTileGridScene::destroyUnit(unit);
}

std::unordered_map<int, AiUnit*> RpgOverWorldScene::getSquadUnits()
{
    return squadUnits;
}



//functions
//int getPathThread(void* scene) {
//    srand(time(NULL));
//    SDL_SetThreadPriority(SDL_THREAD_PRIORITY_LOW);
//    RpgOverWorldScene* rpgScene = static_cast <RpgOverWorldScene*> (scene);
//    while (rpgScene->sceneRunning)
//    {
//        if(rpgScene->unitsNeedingPath.size() > 0)
//        {
//            Unit* unit = rpgScene->unitsNeedingPath.front();
//            rpgScene->unitsNeedingPath.pop_front();
//            try {
//                std::vector<int> tempDirections;
//
//                if (unit->targetUnit != nullptr)
//                {
//                    if ((std::abs(unit->targetUnit->tileDestination->x - unit->tileDestination->x) <= 1) && (std::abs(unit->targetUnit->tileDestination->y - unit->tileDestination->y) <= 1)) {
//                        unit->pathDirections = tempDirections;
//                        unit->gettingPath = false;
//                        continue;
//                    }
//                    tempDirections = unit->scene->getZones()[unit->zone]->getPathDirectionsToUnit(rpgScene, unit->tileDestination, unit->targetUnit, unit);
//                    if (tempDirections.size() > 0)
//                    {
//                        unit->pathDirections = tempDirections;
//                        unit->gettingPath = false;
//                        continue;
//                    }
//                    unit->getNewPathFailTick++;
//                    if (unit->getNewPathFailTick >= unit->scene->getNewPathFailLimit)
//                    {
//                        unit->getNewPathFailTick = 0;
//                        unit->pathDirections = rpgScene->getZones()[unit->zone]->getPathDirectionsIgnoreAllunits(rpgScene, unit->tileDestination, unit->targetUnit->tileDestination);
//                    }
//                    unit->gettingPath = false;
//                    continue;
//                }
//                else if (unit->targetLocation != nullptr) {
//                    tempDirections = rpgScene->getZones()[unit->zone]->getPathDirections(rpgScene, unit->tileDestination, unit->targetLocation);
//                    if (tempDirections.size() > 0)
//                    {
//                        unit->pathDirections = tempDirections;
//                        unit->gettingPath = false;
//                        continue;
//                    }
//                    unit->getNewPathFailTick++;
//                    if (unit->getNewPathFailTick >= unit->scene->getNewPathFailLimit)
//                    {
//                        unit->getNewPathFailTick = 0;
//                        unit->pathDirections = rpgScene->getZones()[unit->zone]->getPathDirectionsIgnoreAllunits(rpgScene, unit->tileDestination, unit->targetLocation);
//                    }
//                    unit->gettingPath = false;
//                    continue;
//                }
//                unit->gettingPath = false;
//            }
//            catch (...) {
//                unit->gettingPath = false;
//                continue;
//            }
//            unit->gettingPath = false;
//            continue;
//        }
//        else {
//            //rpgScene->pathfindThreadActive = false;
//            //return 0;
//        }
//    }
//    //rpgScene->pathfindThreadActive = false;
//    return 0;
//}

int getPathThread(void* scene) {
    SDL_SetThreadPriority(SDL_THREAD_PRIORITY_LOW);
    RpgOverWorldScene* rpgScene = static_cast <RpgOverWorldScene*> (scene);
    rpgScene->engine->seedRand();
    Unit* unit;
    Unit* targetUnit;
    //std::cout << "\n";
    //std::cout << rpgScene->unitsNeedingPath.size();
    //std::cout << "\n";
    for (int i = 0; i <= 4 && rpgScene->unitsNeedPath(); i++)
    {

        SDL_AtomicLock(&rpgScene->unitDestroyLock);
        unit = rpgScene->getUnitNeedingPath();
        if (unit == nullptr)
        {
            break;
        }
        //try {
        std::vector<int> tempDirections;
        targetUnit = unit->getTargetUnit();
        if (targetUnit != nullptr)
        {
            if ((std::abs(targetUnit->tileDestination->x - unit->tileDestination->x) <= 1) && (std::abs(targetUnit->tileDestination->y - unit->tileDestination->y) <= 1)) {
                unit->pathDirections = tempDirections;
                unit->gettingPath = false;
                SDL_AtomicUnlock(&rpgScene->unitDestroyLock);
                continue;
            }
            tempDirections = unit->scene->getZone(unit->getZone())->getPathDirectionsToUnit(rpgScene, unit->tileDestination, targetUnit, unit);
            if (tempDirections.size() > 0)
            {
                unit->pathDirections = tempDirections;
                unit->gettingPath = false;
                SDL_AtomicUnlock(&rpgScene->unitDestroyLock);
                continue;
            }
            unit->getNewPathFailTick++;
            if (unit->getNewPathFailTick >= unit->scene->getNewPathFailLimit)
            {
                unit->getNewPathFailTick = 0;
                unit->pathDirections = rpgScene->getZone(unit->getZone())->getPathDirectionsIgnoreAllunits(rpgScene, unit->tileDestination, targetUnit->tileDestination);
            }
            unit->gettingPath = false;
            SDL_AtomicUnlock(&rpgScene->unitDestroyLock);
            continue;
        }
        else if (unit->getTargetLocation() != unit->tileDestination) {
            tempDirections = rpgScene->getZone(unit->getZone())->getPathDirections(rpgScene, unit->tileDestination, unit->getTargetLocation());
            if (tempDirections.size() > 0)
            {
                unit->pathDirections = tempDirections;
                unit->gettingPath = false;
                SDL_AtomicUnlock(&rpgScene->unitDestroyLock);
                continue;
            }
            unit->getNewPathFailTick++;
            if (unit->getNewPathFailTick >= unit->scene->getNewPathFailLimit)
            {
                unit->getNewPathFailTick = 0;
                unit->pathDirections = rpgScene->getZone(unit->getZone())->getPathDirectionsIgnoreAllunits(rpgScene, unit->tileDestination, unit->getTargetLocation());
            }
            unit->gettingPath = false;
            SDL_AtomicUnlock(&rpgScene->unitDestroyLock);
            continue;
        }
        unit->gettingPath = false;
        /*}
        catch (...) {
            try {
                unit->gettingPath = false;
                SDL_AtomicUnlock(&rpgScene->unitDestroyLock);
                continue;
            }
            catch(...){
                SDL_AtomicUnlock(&rpgScene->unitDestroyLock);
                continue;
            }
        }*/
        unit->gettingPath = false;
        SDL_AtomicUnlock(&rpgScene->unitDestroyLock);
        continue;
    }
    SDL_AtomicUnlock(&rpgScene->unitDestroyLock);
    rpgScene->pathfindThreadActive = false;
    return 0;
}

int updateAggroThread(void* scene) {
    //srand(time(NULL));
    SDL_SetThreadPriority(SDL_THREAD_PRIORITY_LOW);
    RpgOverWorldScene* rpgScene = static_cast <RpgOverWorldScene*> (scene);
    rpgScene->engine->seedRand();
    for (auto zone : rpgScene->getZones())
    {
        //SDL_AtomicLock(&rpgScene->unitDestroyLock);
        for (Unit* unit : zone.second->getUnits()) {
            //try {
            if (unit->deleteLock)
            {
                continue;
            }
            SDL_AtomicLock(&unit->deleteLock);
            if (unit != rpgScene->player)
            {
                AiUnit* aiUnit = (AiUnit*)unit;
                aiUnit->updateAggro();
                if (aiUnit->currentState->id == UNIT_IDLE && !aiUnit->attackNearbyUnit() && aiUnit->doesRandomMovement && aiUnit->pathDirections.size() <= 0)
                {
                    if (!aiUnit->getTargetUnit() || !((std::abs(aiUnit->getTargetUnit()->tileDestination->x - aiUnit->tileDestination->x) <= 1) && (std::abs(aiUnit->getTargetUnit()->tileDestination->y - aiUnit->tileDestination->y) <= 1)))
                    {
                        aiUnit->randomMovement();
                    }
                }
            }
            /*}
            catch (...) {
                SDL_AtomicUnlock(&rpgScene->unitDestroyLock);
                continue;
            }*/
            SDL_AtomicUnlock(&unit->deleteLock);
        }
        //SDL_AtomicUnlock(&rpgScene->unitDestroyLock);
    }
    //SDL_AtomicLock(&rpgScene->unitDestroyLock);
    rpgScene->aggroThreadActive = false;
    return 0;
}