#pragma once
#include "PortalPropertiesOkButton.h"
#include "PortalPropertiesMenu.h"
#include "RpgWorldbuilderScene.h"

class PortalPropertiesCancelButton : public MenuButton
{
public:
    //attributes
    PortalPropertiesMenu* menu;

    //constructors
    PortalPropertiesCancelButton();
    PortalPropertiesCancelButton(PortalPropertiesMenu* newMenu, int xpos, int ypos, int textureKey);

    //methods
    void onClick() override;
};

