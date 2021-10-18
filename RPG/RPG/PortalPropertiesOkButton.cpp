#include "PortalPropertiesOkButton.h"
#include "PortalPropertiesMenu.h"
#include "RpgWorldbuilderScene.h"

PortalPropertiesOkButton::PortalPropertiesOkButton() : MenuButton()
{
    scene = NULL;
}

PortalPropertiesOkButton::PortalPropertiesOkButton(PortalPropertiesMenu* newMenu, int xpos, int ypos, int textureKey) : MenuButton(newMenu->scene, textureKey, xpos, ypos)
{
    menu = newMenu;
    setText("OK");
}

void PortalPropertiesOkButton::onClick()
{
    menu->setPortalBeingBuiltProperties();
    menu->close();
}
