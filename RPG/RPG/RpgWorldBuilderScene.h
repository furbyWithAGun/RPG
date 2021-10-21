#pragma once
#include "RpgTileGridScene.h"
#include "RpgKeysMouseController.h"
#include "SelectPrompt.h"

class BaseGameEngine;

class RpgWorldBuilderScene : public RpgTileGridScene
{
public:
    //attributes
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
    Building buildingBeingPlaced;
    bool placingBuilding;


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

