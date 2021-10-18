#include "PortalPropertiesCancelButton.h"
PortalPropertiesCancelButton::PortalPropertiesCancelButton() : MenuButton()
{
    scene = NULL;
}

PortalPropertiesCancelButton::PortalPropertiesCancelButton(PortalPropertiesMenu* newMenu, int xpos, int ypos, int textureKey) : MenuButton(newMenu->scene, textureKey, xpos, ypos)
{
    menu = newMenu;
    setText("Cancel");
}

void PortalPropertiesCancelButton::onClick()
{
    menu->setPortalBeingBuiltProperties();
    menu->scene->placingPortal = false;
    menu->close();
}