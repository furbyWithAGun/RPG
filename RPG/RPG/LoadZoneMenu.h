#pragma once
#include "GameMenu.h"
#include "MenuText.h"
#include "RpgGameConstants.h"
#include "MenuButton.h"
#include "ScrollBox.h"

class RpgWorldBuilderScene;

class LoadZoneMenu : public GameMenu
{
public:
    //attributes
    RpgWorldBuilderScene* scene;
    ScrollBox* zonesDisplay;

    //constructors
    LoadZoneMenu();
    LoadZoneMenu(RpgWorldBuilderScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);

    //methods
    //bool handleInput(InputMessage* message);
    void open() override;

private:
    //methods
    void buildElements();
    void init();
};

