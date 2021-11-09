#include "RpgOverWorldScene.h"
#include "DooDad.h"
#include "ItemShop.h"
#include "Player.h"
#include "Rat.h"
#include "RatKing.h"
#include "WhiteRat.h"
#include "Soldier.h"
#include "TownsPerson.h"

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


void RpgOverWorldScene::pickUpItemAtLocation(RpgUnit* unit, int x, int y)
{
    if (currentZone->itemMap[x][y].size() > 0)
    {
        unit->addToInventory(currentZone->itemMap[x][y][0]);
        currentZone->itemMap[x][y].erase(currentZone->itemMap[x][y].begin());
    }
}
//
//void RpgOverWorldScene::pickUpItemAtLocation(RpgUnit* unit, int x, int y)
//{
//    if (currentZone->itemMap[x][y].size() > 0)
//    {
//        if (currentZone->itemMap[x][y][0]->stackable)
//        {
//            bool itemAlreadyInInventory = false;
//            for (auto item : unit->inventory)
//            {
//                if (item->textureKey == currentZone->itemMap[x][y][0]->textureKey)
//                {
//                    itemAlreadyInInventory = true;
//                    item->stackSize += currentZone->itemMap[x][y][0]->stackSize;
//                    break;
//                }
//            }
//            if (!itemAlreadyInInventory)
//            {
//                unit->inventory.push_back(currentZone->itemMap[x][y][0]);
//            }
//        }
//        else {
//            unit->inventory.push_back(currentZone->itemMap[x][y][0]);
//        }
//        currentZone->itemMap[x][y].erase(currentZone->itemMap[x][y].begin());
//        menus[INVENTORY_MENU]->update();
//    }
//}

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
    //set up teams
    teamRelations[PLAYER_TEAM][MONSTER_TEAM] = ENEMY;
    teamRelations[MONSTER_TEAM][PLAYER_TEAM] = ENEMY;

    //make units
    //createUnitAtLocation(currentZone->id, RAT, desiredTilesAcross / 2 - 3, desiredTilesDown / 2);
    //createUnitAtLocation(currentZone->id, RAT, desiredTilesAcross / 2 - 4, desiredTilesDown / 2);
    player = (Player*)createUnitAtLocation(currentZone->id, PLAYER, 5, 6);
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_SHORT_SWORD)});
   // addItemsToMap(0, 5, 6, {createNewItem(ITEM_RAG_HAT)});
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_RAG_BODY)});
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_RAG_BOOTS)});
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_RAG_GLOVES)});
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_RAG_PANTS)});
    //addItemsToMap(0, 5, 6, {createNewItem(ITEM_SHORT_SWORD)});
    //Item* itemToDrop = createNewItem(ITEM_LOGS);
    //itemToDrop->stackSize = 1000;
    //addItemsToMap(0, 5, 6, { itemToDrop });
    
    //player->gold = 5000;
    //player->gold = 100000;
    //player->addExp(COMBAT_EXPERIENCE, 250);
    //player->addExp(COMBAT_EXPERIENCE, 999999999);
    player->health = 9999999;
    player->maxHealth = 9999999;

    //createUnitAtLocation(currentZone->id, RAT, 6, 6);
    createUnitAtLocation(currentZone->id, SOLDIER, 6, 8);
    createUnitAtLocation(currentZone->id, SOLDIER, 10, 10);
    createUnitAtLocation(1, SOLDIER, 3, 8);
    testUnit = createUnitAtLocation(currentZone->id, SKELETON, 19, 5);
    //testUnit->toSaveString();
    //Location* testLocation = new Location{ 2, 0 };
    //testUnit->pathDirections = currentZone->getPathDirections(this, testUnit->tileLocation, testLocation);
    //testUnit->setTargetLocation(testLocation);
    createUnitAtLocation(2, RAT_KING, 26, 12);
    //createUnitAtLocation(1, TOWNSPERSON, 11, 2);

    //buildings
    //ItemShop* testBuilding;
    //testBuilding = (ItemShop*)createBuildingAtLocation(1, BUILDING_ITEM_SHOP, LEFT, 10, 10);
    //testBuilding->setItemsForSale({new Club(), new ShortSword(), new Mace(), new LongSword(), new RagBody(), new RagBoots(), new RagGloves(), new RagHat(), new RagPants(), new LinenBody(), new LinenBoots(), new LinenGloves(), new LinenHat(), new LinenPants()});
    //testBuilding->setItemsForSale({ createNewItem(ITEM_CLUB), new ShortSword(), new Mace(), new LongSword(), new RagBody(), new RagBoots(), new RagGloves(), new RagHat(), new RagPants(), new LinenBody(), new LinenBoots(), new LinenGloves(), new LinenHat(), new LinenPants()});
    
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
                    else if (tileCoordsAreDisplayedMapTile(tileCoords[0], tileCoords[1]))
                    {
                        if (currentZone->itemMap[tileCoords[0]][tileCoords[1]].size() > 0 && (std::abs(tileCoords[0] - player->tileLocation->x) <= 1) && (std::abs(tileCoords[1] - player->tileLocation->y) <= 1))
                        {
                            addCommand(InputMessage(PICK_UP_ITEM, tileCoords[0], tileCoords[1]));
                            break;
                        }
                    }
                    DooDad* targetDooDad;
                    targetDooDad = currentZone->getDooDadAtLocation(tileCoords[0], tileCoords[1]);
                    if (tileCoordsAreDisplayedMapTile(tileCoords[0], tileCoords[1]) && targetDooDad != nullptr)
                    {
                        if (targetDooDad->type == DOODAD_TREE && targetDooDad->passable == false && (std::abs(tileCoords[0] - player->tileLocation->x) <= 1) && (std::abs(tileCoords[1] - player->tileLocation->y) <= 1))
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
        }
    }
    delete message;
}

void RpgOverWorldScene::sceneLogic()
{
    //call base class logic
    RpgTileGridScene::sceneLogic();
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
        case OVERWORLD_PLACE_BUILDING:
            if (buildingCanBePlacedAtLocation(&buildingBeingPlaced, currentZone, message->x, message->y) && canAffordBuilding(&buildingBeingPlaced)) {
                createBuildingAtLocation(currentZone, message->misc, LEFT, message->x, message->y);
                payBuildingCosts(&buildingBeingPlaced);
            }
            break;
        case USER_ACTION:
            RpgUnit* actionedUnit;
            actionedUnit = getUnitAtLocation(player->zone, message->x, message->y);
            if (actionedUnit != nullptr)
            {
                if (actionedUnit->assignedToBuilding != nullptr)
                {
                    actionedUnit->assignedToBuilding->onActionAssignedUnit(actionedUnit);
                }
            }
            DooDad* actionedDooDad;
            actionedDooDad = zones[player->zone]->getDooDadAtLocation(message->x, message->y);
            if (actionedDooDad != nullptr)
            {
                actionedDooDad->actionOn(player, OVERWORLD_USE);
            }
            break;
        case OVERWORLD_STRIKE:
            actionedDooDad = zones[player->zone]->getDooDadAtLocation(message->x, message->y);
            if (actionedDooDad != nullptr && (std::abs(actionedDooDad->tileCoords[0] - player->tileLocation->x) <= 1) && (std::abs(actionedDooDad->tileCoords[1] - player->tileLocation->y) <= 1))
            {
                actionedDooDad->actionOn(player, OVERWORLD_STRIKE);
            }
            break;
        default:
            break;
        }
    }
    
    for (auto zone :zones)
    {
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
                createUnitAtLocation(zone.second->id, WHITE_RAT, targetCoords[0], targetCoords[1]);
            }
        }

        //spawn troops
        if (engine->getProbFromSigmoid(zone.second->getDifficulty() + 1, zone.second->getDevelopmentLevel() + 12000) > engine->randomDouble() && zone.second->mobSpawn)
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
    if (!player->cameraFollowPlayer)
    {
        scrollCamera();
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