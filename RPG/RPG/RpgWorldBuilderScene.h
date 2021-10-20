#pragma once
#include "RpgTileGridScene.h"
#include "MapTile.h"
#include <unordered_map>
#include "Player.h"
#include "GameMenu.h"
#include "ZoneMap.h"
#include "RpgGameConstants.h"
#include "RpgKeysMouseController.h"
#include "SelectPrompt.h"

class BaseGameEngine;

class RpgWorldBuilderScene : public RpgTileGridScene
{
public:
    //attributes
    BaseGameEngine* engine;
    bool placingTile;
    MapTile* tileBeingPlaced;
    bool placingPortal;
    bool pickingPortalCoords;
    int portalBeingPlaced;
    int portalBeingPlacedExitId;
    int portalBeingPlacedExitCoordsX;
    int portalBeingPlacedExitCoordsY;
    ZoneMap* portalExitZone;
    int previousZoneXoffset, previousZoneYoffset;
    ZoneMap sceneToEdit;

    //constructor
    RpgWorldBuilderScene();
    RpgWorldBuilderScene(BaseGameEngine* gameEngine);

    //methods
    void declareSceneAssets();
    void setUpScene() override;
    void handleInput() override;
    void sceneLogic() override;
    void renderScene() override;
    void loadZone(int zoneId) override;
    void createNewZone() override;

private:
    //methods
    void init();
    void scrollCamera();
};

