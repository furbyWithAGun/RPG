#pragma once
#include "MenuText.h"
#include "ScrollBox.h"
#include "TextBox.h"
#include "GameMenu.h"
#include "PortalPropertiesOkButton.h"
#include "PortalPropertiesCancelButton.h"

class RpgWorldBuilderScene;

class PortalPropertiesMenu : public GameMenu
{
public:
    //attributes
    RpgWorldBuilderScene* scene;
    ZonePortal* portalToEdit;

    //constructors
    PortalPropertiesMenu();
    PortalPropertiesMenu(RpgWorldBuilderScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);


    //methods
    bool handleInput(InputMessage* message);
    void setPortalBeingBuiltProperties();
    void open();
    void open(ZonePortal* newPortal);
    void setExitZoneCoords(int newCoords[2]);

private:
    //methods
    void buildElements();
};

