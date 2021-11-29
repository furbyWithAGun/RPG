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
    RpgZone* portalExitZone;
    int previousZoneXoffset, previousZoneYoffset;
    RpgZone sceneToEdit;


    //constructor
    RpgWorldBuilderScene();
    RpgWorldBuilderScene(BaseGameEngine* gameEngine);

    //methods
    void declareSceneAssets();
    void setUpScene() override;
    void handleInput() override;
    void sceneLogic() override;
    void renderScene() override;
    void setCurrentZone(int zoneId) override;
    void createNewZone() override;
    void createFirstZone();
    void virtual destroyUnit(RpgUnit* unit) override;
    void virtual destroyDooDad(DooDad* dooDad) override;

private:
    //methods
    void init();
};

