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
    controllerInterface = new RpgKeysMouseController();
    new DooDad(this, 3,3,3);
    testUnit = nullptr;
    displayHud = true;
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



void RpgOverWorldScene::loadZone(int zoneId)
{
    RpgTileGridScene::loadZone(zoneId);
}

void RpgOverWorldScene::declareSceneAssets()
{
    RpgTileGridScene::declareSceneAssets();
}

void RpgOverWorldScene::setUpScene()
{
    RpgTileGridScene::setUpScene();
    Building::resetUid();
    Unit::resetUid();
    setUpMonsterTable();
    //set up teams
    teamRelations[PLAYER_TEAM][MONSTER_TEAM] = ENEMY;
    teamRelations[MONSTER_TEAM][PLAYER_TEAM] = ENEMY;

    //make units
    //createUnitAtLocation(currentZone->id, RAT, desiredTilesAcross / 2 - 3, desiredTilesDown / 2);
    //createUnitAtLocation(currentZone->id, RAT, desiredTilesAcross / 2 - 4, desiredTilesDown / 2);
    player = (Player*)createUnitAtLocation(0, PLAYER, 10, 26);
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_SHORT_SWORD)});
   // addItemsToMap(0, 5, 6, {createNewItem(ITEM_RAG_HAT)});
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_RAG_BODY)});
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_RAG_BOOTS)});
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_RAG_GLOVES)});
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_RAG_PANTS)});
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_LEATHER_BODY)});
    //Item* itemToDrop = createNewItem(ITEM_LOGS);
    //itemToDrop->stackSize = 1000;
    //addItemsToMap(0, 5, 6, { itemToDrop });
    
    //player->gold = 5000;
    //player->gold = 100000;
    //player->addExp(COMBAT_EXPERIENCE, 250);
    //player->addExp(COMBAT_EXPERIENCE, 999999999);
    //player->health = 9999999;
    //player->maxHealth = 9999999;

    //createUnitAtLocation(currentZone->id, RAT, 8, 8);
    createUnitAtLocation(currentZone->id, SOLDIER, 9, 25);
    createUnitAtLocation(currentZone->id, SOLDIER, 10, 27);
    createUnitAtLocation(1, SOLDIER, 3, 8);
    getZones()[currentZone->id]->addDooDadToLocation(createNewUnitSpawner(this, RAT, currentZone->id), 9, 11);
    getZones()[currentZone->id]->addDooDadToLocation(createNewUnitSpawner(this, RAT, currentZone->id), 48, 23);
    getZones()[currentZone->id]->addDooDadToLocation(createNewUnitSpawner(this, RAT, currentZone->id), 29, 36);
    createUnitAtLocation(2, RAT_KING, 29, 1);
    createUnitAtLocation(3, SKELETON_KING, 28, 28);

    //build menus
    menus[RPG_OVERWORLD_MENU] = new OverWorldSceneMenu(this, BUILD_MENU, mainCanvasStartX, engine->screenHeight * 0.8, 0, engine->screenHeight * 0.2);
    menus[TOWN_BUILD_MENU] = new TownBuildMenu(this, BUILD_MENU, mainCanvasStartX, engine->screenHeight * 0.8, 0, engine->screenHeight * 0.2);
    menus[ITEM_SELL_MENU] = new ItemSellMenu(this, ITEM_SELL_MENU, engine->screenWidth * 0.25, engine->screenHeight * 0.5, mainCanvasStartX + engine->screenWidth * 0.01, engine->screenHeight * 0.15);
    menus[ITEM_BUY_MENU] = new ItemBuyMenu(this, ITEM_SELL_MENU, engine->screenWidth * 0.35, engine->screenHeight * 0.5, mainCanvasStartX + engine->screenWidth * 0.01, engine->screenHeight * 0.15);
    menus[INVENTORY_MENU] = new InventoryMenu(this, INVENTORY_MENU);
    menus[EQUIPPED_MENU] = new EquippedMenu(this, EQUIPPED_MENU, engine->screenWidth * 0.3, engine->screenHeight * 0.5, mainCanvasStartX + engine->screenWidth * 0.30, engine->screenHeight * 0.15);

    SDL_CreateThread(getPathThread, "getPathThread", (void*)this);
}

void RpgOverWorldScene::handleInput()
{
    RpgTileGridScene::handleInput();
    InputMessage* message = new InputMessage();
    int tileCoords[2];
    
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
                    Unit* unitAtLocation = getUnitAtLocation(currentZone->id, tileCoords[0], tileCoords[1]);
                    if (unitAtLocation != nullptr && unitAtLocation != player)
                    {
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
            Unit* unitAtLocation = getUnitAtLocation(currentZone->id, tileCoords[0], tileCoords[1]);
            if (unitAtLocation != nullptr && unitAtLocation != player)
            {
                addCommand(InputMessage(PERFORM_MAIN_ATTACK, controllerInterface->latestXpos, controllerInterface->latestYpos));
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
    //call base class logic
    RpgTileGridScene::sceneLogic();
    Location* soldierSpawn = new Location{ 7, 7 };
    //Location* ratSpawn = new Location{32, 11};
    //Location* ratSpawn2 = new Location{7, 34};


    //handle commands
    InputMessage* message = new InputMessage();
    while (getNextCommand(message)) {
        player->handleInput(message);
        switch (message->id)
        {
        case OVERWORLD_PLACE_BUILDING:
            if (buildingCanBePlacedAtLocation(&buildingBeingPlaced, currentZone, message->x, message->y) && canAffordBuilding(&buildingBeingPlaced)) {
                createBuildingAtLocation(currentZone, message->misc, LEFT, message->x, message->y);
                payBuildingCosts(&buildingBeingPlaced);
            }
            break;
        default:
            break;
        }
    }
    
    for (auto zone : getZones())
    {
        if (engine->getProbFromSigmoid(zone.second->getDifficulty() + 1, zone.second->getDevelopmentLevel() + 8000 + zone.second->numUnitSpawners * 2000) > engine->randomDouble() && zone.second->zoneName == "zoneOne")
        {
            int targetCoords[2] = { 0, 0 };
            int attempts = 0;
            bool foundLocation = false;
            while (true)
            {
                attempts++;
                targetCoords[0] = engine->randomInt(0, zone.second->tileMap.size() - 1);
                targetCoords[1] = engine->randomInt(0, zone.second->tileMap[0].size() - 1);
                if (isTilePassable(zone.second->id, targetCoords[0], targetCoords[1]))
                {
                    foundLocation = true;
                    break;
                }
                if (attempts > 50)
                {
                    break;
                }
            }
            if (foundLocation && getUnitAtLocation(zone.second->id, targetCoords[0], targetCoords[1]) == nullptr)
            {
                getZones()[zone.second->id]->addDooDadToLocation(createNewUnitSpawner(this, getUnitTypeByDifficulty(zone.second->difficulty), zone.second->id), targetCoords[0], targetCoords[1]);
            }
        }

        //spawn WhiteRats
        if (engine->getProbFromSigmoid(zone.second->getDifficulty() + 1, zone.second->getDevelopmentLevel() + 3500) > engine->randomDouble() && zone.second->zoneName == "caveOne")
        {
            int targetCoords[2] = { 0, 0 };
            while (true)
            {
                targetCoords[0] = engine->randomInt(0, zone.second->tileMap.size() - 1);
                targetCoords[1] = engine->randomInt(0, zone.second->tileMap[0].size() - 1);
                if (mapTiles[zone.second->tileMap[targetCoords[0]][targetCoords[1]]].passable && getPortalAtLocation(zone.second, targetCoords[0], targetCoords[1]) == nullptr)
                {
                    break;
                }
            }
            if (getUnitAtLocation(zone.second->id, targetCoords[0], targetCoords[1]) == nullptr)
            {
                createUnitAtLocation(zone.second->id, WHITE_RAT, targetCoords[0], targetCoords[1]);
            }
        }

        //spawn skeletons
        if (engine->getProbFromSigmoid(zone.second->getDifficulty() + 1, zone.second->getDevelopmentLevel() + 5000) > engine->randomDouble() && zone.second->zoneName == "caveTwo")
        {
            int targetCoords[2] = { 0, 0 };
            while (true)
            {
                targetCoords[0] = engine->randomInt(0, zone.second->tileMap.size() - 1);
                targetCoords[1] = engine->randomInt(0, zone.second->tileMap[0].size() - 1);
                if (mapTiles[zone.second->tileMap[targetCoords[0]][targetCoords[1]]].passable && getPortalAtLocation(zone.second, targetCoords[0], targetCoords[1]) == nullptr)
                {
                    break;
                }
            }
            if (getUnitAtLocation(zone.second->id, targetCoords[0], targetCoords[1]) == nullptr)
            {
                createUnitAtLocation(zone.second->id, SKELETON, targetCoords[0], targetCoords[1]);
            }
        }

        //spawn troops
        if (engine->getProbFromSigmoid(zone.second->getDifficulty() + 1, zone.second->getDevelopmentLevel() + 24000) > engine->randomDouble() && zone.second->mobSpawn && zone.second->zoneName == "zoneOne")
        {
            if (getUnitAtLocation(zone.second->id, soldierSpawn->x, soldierSpawn->y) == nullptr)
            {
                createUnitAtLocation(zone.second->id, SOLDIER, soldierSpawn->x, soldierSpawn->y)->setTargetLocation(new Location{ 11, 26 });
            }
        }
    }
    
    delete message;
}

void RpgOverWorldScene::renderScene()
{
    int tileCoords[2], screenCoords[2];
    if (!player->cameraFollowPlayer)
    {
        scrollCamera();
    }
    else {
        player->updateCamera();
    }
    RpgTileGridScene::renderScene();
    if (displayHud)
    {
        renderHUD();
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
    engine->renderText("Health: " + std::to_string(player->health), engine->screenWidth * 0.01, engine->screenHeight * 0.06, COLOR_WHITE);
    renderRectangle(engine->screenWidth * 0.01, engine->screenHeight * 0.1, engine->screenWidth * 0.05, engine->screenHeight * 0.01, COLOR_GREY);
    renderRectangle(engine->screenWidth * 0.01, engine->screenHeight * 0.1, (engine->screenWidth * 0.05) * (double) ((double)player->health / (double)player->maxHealth), engine->screenHeight * 0.01, COLOR_RED);
    engine->renderText("Mana: " + std::to_string(player->mana), engine->screenWidth * 0.01, engine->screenHeight * 0.11, COLOR_WHITE);
    renderRectangle(engine->screenWidth * 0.01, engine->screenHeight * 0.15, engine->screenWidth * 0.05, engine->screenHeight * 0.01, COLOR_GREY);
    renderRectangle(engine->screenWidth * 0.01, engine->screenHeight * 0.15, (engine->screenWidth * 0.05) * (double)((double)player->mana / (double)player->maxMana), engine->screenHeight * 0.01, COLOR_BLUE);
    engine->renderText("Gold: " + std::to_string(player->gold), engine->screenWidth * 0.01, engine->screenHeight * 0.16, COLOR_GOLD);

    for (size_t i = 0; i < player->foodEffects.size(); i++)
    {
        engine->renderTexture(player->foodEffects[i]->texture, mainCanvasStartX + engine->screenWidth * 0.02 * i, engine->screenHeight * 0.95);
        renderRectangle(mainCanvasStartX + engine->screenWidth * 0.02 * i + engine->screenWidth * 0.02, engine->screenHeight * 0.99, engine->screenWidth * 0.004, (engine->screenHeight * 0.05) * ((double)((double)player->foodEffects[i]->tick - (double)player->foodEffects[i]->duration) / (double)player->foodEffects[i]->duration), COLOR_WHITE);
    }
}

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
                    if ((std::abs(unit->targetUnit->tileDestination->x - unit->tileDestination->x) <= 1) && (std::abs(unit->targetUnit->tileDestination->y - unit->tileDestination->y) <= 1)) {
                        unit->pathDirections = tempDirections;
                        unit->gettingPath = false;
                        continue;
                    }
                    tempDirections = unit->scene->getZones()[unit->zone]->getPathDirectionsToUnit(rpgScene, unit->tileDestination, unit->targetUnit, unit);
                    if (tempDirections.size() > 0)
                    {
                        unit->pathDirections = tempDirections;
                        unit->gettingPath = false;
                        continue;
                    }
                    unit->getNewPathFailTick++;
                    if (unit->getNewPathFailTick >= unit->scene->getNewPathFailLimit)
                    {
                        unit->getNewPathFailTick = 0;
                        unit->pathDirections = rpgScene->getZones()[unit->zone]->getPathDirectionsIgnoreAllunits(rpgScene, unit->tileDestination, unit->targetUnit->tileDestination);
                    }
                    unit->gettingPath = false;
                    continue;
                }
                else if (unit->targetLocation != nullptr) {
                    tempDirections = rpgScene->getZones()[unit->zone]->getPathDirections(rpgScene, unit->tileDestination, unit->targetLocation);
                    if (tempDirections.size() > 0)
                    {
                        unit->pathDirections = tempDirections;
                        unit->gettingPath = false;
                        continue;
                    }
                    unit->getNewPathFailTick++;
                    if (unit->getNewPathFailTick >= unit->scene->getNewPathFailLimit)
                    {
                        unit->getNewPathFailTick = 0;
                        unit->pathDirections = rpgScene->getZones()[unit->zone]->getPathDirectionsIgnoreAllunits(rpgScene, unit->tileDestination, unit->targetLocation);
                    }
                    unit->gettingPath = false;
                    continue;
                }
                unit->gettingPath = false;
            }
            catch (...) {
                unit->gettingPath = false;
                continue;
            }
            unit->gettingPath = false;
            continue;
        }
    }
    return 0;
}
