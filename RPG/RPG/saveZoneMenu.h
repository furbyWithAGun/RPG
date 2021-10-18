#pragma once
#include "GameMenu.h"
#include "TextBox.h"
#include "MenuText.h"
#include "RpgGameConstants.h"
#include "MenuButton.h"

class RpgWorldBuilderScene;

class saveZoneMenu : public GameMenu
{
public:
    //attributes
    RpgWorldBuilderScene* scene;

    //constructors
    saveZoneMenu();
    saveZoneMenu(RpgWorldBuilderScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);

    //methods
    //bool handleInput(InputMessage* message);
    void open() override;

private:
    //methods
    void buildElements();
};

