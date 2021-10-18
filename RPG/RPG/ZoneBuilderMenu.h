#pragma once
#include "GameMenu.h"
#include "MapBuilderTileButton.h"
#include "MapBuilderPortalButton.h"
#include "SaveMapBuilderButton.h"
#include "MenuText.h"
#include "ScrollBox.h"
#include "TextBox.h"
#include "PagedPanel.h"

class ZoneBuilderMenu : public GameMenu
{
public:
    //attributes
    PagedPanel* mainPanel;

    //constructors
    ZoneBuilderMenu();
    ZoneBuilderMenu(RpgWorldBuilderScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);
    void close();

    //methods
    bool handleInput(InputMessage* message);
    void updateMobSpawnButton();
    void updateDifficultyText();
    void setZoneDifficulty();

private:
    //attributes
    RpgWorldBuilderScene* scene;

    //methods
    void buildElements();
    void buildPageOne();
    void buildPageTwo();
};

