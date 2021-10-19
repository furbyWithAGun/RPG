#include "RpgWorldBuilderScene.h"
#include "BaseGameEngine.h"
#include "ZoneBuilderMenu.h"
#include "PortalPropertiesMenu.h"
#include "saveZoneMenu.h"
#include "LoadZoneMenu.h"

//constants
const int DEFAULT_DESIRED_TILES_DOWN = 10;
const int DEFAULT_DESIRED_TILES_ACROSS = 19;
const int SCROLL_SPEED = 4;

//constructor
RpgWorldBuilderScene::RpgWorldBuilderScene() : TileGridScene(){
    init();
}

RpgWorldBuilderScene::RpgWorldBuilderScene(BaseGameEngine * gameEngine) : TileGridScene(gameEngine){
    init();
    engine = gameEngine;
}

void RpgWorldBuilderScene::init() {
    engine = NULL;
    tileBeingPlaced = NULL;
    portalExitZone = nullptr;
    placingTile = false;
    placingPortal = false;
    pickingPortalCoords = false;
    portalBeingPlaced = -1;
    controllerInterface = new RpgKeysMouseController();
    portalBeingPlacedExitId = 0;
    portalBeingPlacedExitCoordsX = 0;
    portalBeingPlacedExitCoordsY = 0;
    previousZoneXoffset = 0;
    previousZoneYoffset = 0;
}

void RpgWorldBuilderScene::declareSceneAssets() {
    TileGridScene::declareSceneAssets();
    texturesToLoad.insert({ BUTTON_BACKGROUND, "images/buttonBackground.png" });
}

void RpgWorldBuilderScene::setUpScene() {
    TileGridScene::setUpScene();
    sceneToEdit = ZoneMap(*zones[0]);
    currentZone = &sceneToEdit;
    ZoneBuilderMenu* zoneBuildMenu = new ZoneBuilderMenu(this, BUILD_MENU, mainCanvasStartX, engine->screenHeight, 0, 0);
    zoneBuildMenu->isActive = true;

    menus[BUILD_MENU] = zoneBuildMenu;
    menus[PORTAL_PROPERTIES_MENU] = new PortalPropertiesMenu(this, PORTAL_PROPERTIES_MENU, 300, 300, 300, 300);
    menus[SAVE_ZONE_MENU] = new saveZoneMenu(this, SAVE_ZONE_MENU, 300, 200, 300, 300);
    menus[LOAD_ZONE_MENU] = new LoadZoneMenu(this, SAVE_ZONE_MENU, 500, 500, 300, 300);
}

void RpgWorldBuilderScene::handleInput() {
    TileGridScene::handleInput();
    int tileCoords[2];
    InputMessage* message = new InputMessage();
    while (controllerInterface->getNextMessage(message)) {
        switch (message->id)
        {
        case END_SCENE:
            endScene();
            break;
        case SELECT_ON:
            if (pickingPortalCoords)
            {
                getTileIndexFromScreenCoords(message->x, message->y, tileCoords);
                addCommand(InputMessage(PICK_EXIT_COORDS, tileCoords[0], tileCoords[1]));
            }
            else {
                if (placingTile && coordsAreOnDisplayedMapTile(message->x, message->y))
                {
                    getTileIndexFromScreenCoords(message->x, message->y, tileCoords);
                    addCommand(InputMessage(PLACE_TILE, tileCoords[0], tileCoords[1], tileBeingPlaced->textureKey));
                }
                if (placingPortal && coordsAreOnDisplayedMapTile(message->x, message->y))
                {
                    getTileIndexFromScreenCoords(message->x, message->y, tileCoords);
                    addCommand(InputMessage(PLACE_PORTAL, tileCoords[0], tileCoords[1], portalBeingPlaced));
                }
            }
            
            break;
        case BUTTON_1_OFF:
            getTileIndexFromScreenCoords(message->x, message->y, tileCoords);
            if (sceneToEdit.getPortalAtLocation(tileCoords[0], tileCoords[1]) != nullptr)
            {
                addCommand(InputMessage(OPEN_PLACED_PORTAL_OPTIONS_MENU, tileCoords[0], tileCoords[1]));
            }
            break;
        case SELECT_OFF:
            break;
        case POINTER_MOVEMENT:
            if (placingTile && coordsAreOnDisplayedMapTile(message->x, message->y) && controllerInterface->selectOn)
            {
                getTileIndexFromScreenCoords(message->x, message->y, tileCoords);
                addCommand(InputMessage(PLACE_TILE, tileCoords[0], tileCoords[1], tileBeingPlaced->textureKey));
            }
            if (placingPortal && coordsAreOnDisplayedMapTile(message->x, message->y) && controllerInterface->selectOn)
            {
                getTileIndexFromScreenCoords(message->x, message->y, tileCoords);
                addCommand(InputMessage(PLACE_PORTAL, tileCoords[0], tileCoords[1], portalBeingPlaced));
            }
            break;
        default:
            break;
        }
    }
    delete message;
}

void RpgWorldBuilderScene::sceneLogic() {
    //handle commands
    InputMessage* message = new InputMessage();
    while (getNextCommand(message)) {
        switch (message->id)
        {
        case PLACE_TILE:
            if (gettingTextInput) {
                int x = 1;
            }
            sceneToEdit.tileMap[message->y][message->x] = message->misc;
            break;
        case PLACE_PORTAL:
            if (getPortalAtLocation(&sceneToEdit, message->x, message->y) == nullptr)
            {
                sceneToEdit.addZonePortal(message->misc, { message->x, message->y }, portalBeingPlacedExitId, { portalBeingPlacedExitCoordsX, portalBeingPlacedExitCoordsY });
            }
            break;
        case OPEN_PLACED_PORTAL_OPTIONS_MENU:
            ZonePortal* selectedPortal;
            selectedPortal = getPortalAtLocation(&sceneToEdit, message->x, message->y);
            int portalCoords[2];
            coordsFromTileIndex(selectedPortal->tileCoords[0], selectedPortal->tileCoords[1], portalCoords);
            SelectPrompt* portalSelectPrompt;
            portalSelectPrompt = new SelectPrompt(this, COLOR_BLACK, portalCoords[0] + tileWidth, portalCoords[1] + tileHeight, 300, 300);
            portalSelectPrompt->addSelectOption("Delete Portal", 1);
            portalSelectPrompt->addSelectOption("Edit Portal", 2);
            portalSelectPrompt->addCallBack([this, portalSelectPrompt, selectedPortal]() {
                switch (portalSelectPrompt->getSelectedOptionValue())
                {
                case 1:
                    sceneToEdit.removePortalAtLocation(selectedPortal->tileCoords[0], selectedPortal->tileCoords[1]);
                    break;
                case 2:
                    PortalPropertiesMenu * editPortalMenu;
                    editPortalMenu = (PortalPropertiesMenu*)menus[PORTAL_PROPERTIES_MENU];
                    editPortalMenu->open(selectedPortal);
                    break;
                default:
                    break;
                }
                removePrompt(portalSelectPrompt);
                });
            portalSelectPrompt->active = true;
            portalSelectPrompt->closeOnClickMiss = true;
            addPrompt(portalSelectPrompt);
            break;
        case PICK_EXIT_COORDS:
            PortalPropertiesMenu* portalMenu;
            int coords[2];
            portalMenu = (PortalPropertiesMenu*)menus[PORTAL_PROPERTIES_MENU];
            coords[0] = message->x;
            coords[1] = message->y;
            portalMenu->setExitZoneCoords(coords);
            portalMenu->open();
            pickingPortalCoords = false;
            break;
        default:
            break;
        }
    }
    delete message;
}

void RpgWorldBuilderScene::renderScene() {
    scrollCamera();
    int tileCoords[2], screenCoords[2];
    if (pickingPortalCoords)
    {
        portalExitZone->draw(this);
    }
    else {
        sceneToEdit.draw(this);

        //cover Left side
        engine->renderRectangle(0, 0, mainCanvasStartX, engine->screenHeight, 0, 0, 0);

        if (placingTile && coordsAreOnDisplayedMapTile(controllerInterface->latestXpos, controllerInterface->latestYpos) && !mouseOnAMenu())
        {
            getTileIndexFromScreenCoords(controllerInterface->latestXpos, controllerInterface->latestYpos, tileCoords);
            coordsFromTileIndex(tileCoords[0], tileCoords[1], screenCoords);
            renderTexture(tileBeingPlaced->textureKey, screenCoords[0] - tileWidth, screenCoords[1] - tileWidth, tileWidth * 3, tileHeight * 3);
        }

        if (placingPortal && coordsAreOnDisplayedMapTile(controllerInterface->latestXpos, controllerInterface->latestYpos) && !mouseOnAMenu())
        {
            getTileIndexFromScreenCoords(controllerInterface->latestXpos, controllerInterface->latestYpos, tileCoords);
            coordsFromTileIndex(tileCoords[0], tileCoords[1], screenCoords);
            renderTexture(portalBeingPlaced, screenCoords[0] - tileWidth, screenCoords[1] - tileWidth, tileWidth * 3, tileHeight * 3);
            engine->renderText("P", screenCoords[0], screenCoords[1], tileWidth, tileHeight);
        }

        for (auto portal : sceneToEdit.portals) {
            engine->renderText("P", (tileWidth * portal->tileCoords[0]) + mainCanvasStartX + xOffset, tileHeight * portal->tileCoords[1] + yOffset, tileWidth, tileHeight);
        }        
    }
}

void RpgWorldBuilderScene::loadZone(int zoneId)
{
    sceneToEdit = *zones[zoneId];
    currentZone = &sceneToEdit;
    ((ZoneBuilderMenu*)menus[BUILD_MENU])->updateMobSpawnButton();
    ((ZoneBuilderMenu*)menus[BUILD_MENU])->updateDifficultyText();
}

void RpgWorldBuilderScene::createNewZone()
{
    //loadZones();
    sceneToEdit = ZoneMap();
    sceneToEdit.id = nextZoneId;
    sceneToEdit.zoneName = std::to_string(sceneToEdit.id);
    currentZone = &sceneToEdit;
    nextZoneId++;
    ((ZoneBuilderMenu*)menus[BUILD_MENU])->updateMobSpawnButton();
    ((ZoneBuilderMenu*)menus[BUILD_MENU])->updateDifficultyText();
}

void RpgWorldBuilderScene::scrollCamera() {
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