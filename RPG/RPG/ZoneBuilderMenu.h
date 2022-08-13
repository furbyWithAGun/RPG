#pragma once
#include "GameMenu.h"
#include "MapBuilderTileButton.h"
#include "MapBuilderPortalButton.h"
#include "SaveMapBuilderButton.h"
#include "MenuText.h"
#include "ScrollBox.h"
#include "TextBox.h"
#include "PagedPanel.h"
#include "BuildingFactory.h"
#include "DooDadFactory.h"
#include "UnitFactory.h"

class ZoneBuilderMenu : public GameMenu
{
public:
    //attributes
    PagedPanel* mainPanel;
    std::vector<Building> buildingTemplates;
    std::vector<Unit> unitTemplates;
    std::vector<DooDad> DooDadTemplates;

    //constructors
    ZoneBuilderMenu();
    ZoneBuilderMenu(RpgWorldBuilderScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);
    void close();

    //methods
    bool handleInput(InputMessage* message);
    void updateMobSpawnButton();
    void updateDifficultyText();
    void setZoneDifficulty();
    void updateZoneTypeText();
    void setZoneType();

private:
    //attributes
    RpgWorldBuilderScene* scene;

    //methods
    void buildElements();
    void buildPageOne();
    void buildPageTwo();
    void buildPageThree();
};

