#include "MapBuilderPortalButton.h"
#include "PortalPropertiesMenu.h"

//constants
static const int WIDTH_ADJUSTOR = 38;
static const int HEIGHT_ADJUSTOR = 20;

//constructors
MapBuilderPortalButton::MapBuilderPortalButton() : MenuButton() {
    init();
}

MapBuilderPortalButton::MapBuilderPortalButton(RpgWorldBuilderScene* gameScene, int newPortalKey) : MenuButton(gameScene, newPortalKey) {
    init(gameScene, newPortalKey);
}

MapBuilderPortalButton::MapBuilderPortalButton(int elementId, RpgWorldBuilderScene* gameScene, int newPortalKey) : MenuButton(elementId, gameScene, newPortalKey) {
    init(gameScene, newPortalKey);
}

//methods
void MapBuilderPortalButton::onClick() {
    //scene->openMenu(PORTAL_PROPERTIES_MENU);
    scene->placingTile = false;
    scene->placingBuilding = false;
    scene->placingPortal = true;
    scene->placingDooDad = false;
    scene->placingUnit = false;
    scene->portalBeingPlaced->textureId = portalKey;
    PortalPropertiesMenu* editPortalMenu;
    editPortalMenu = (PortalPropertiesMenu*)scene->menus[PORTAL_PROPERTIES_MENU];
    editPortalMenu->open(scene->portalBeingPlaced);;
}

void MapBuilderPortalButton::init() {
    scene = NULL;
    portalKey = -1;
    width = -1;
    height = -1;
}

void MapBuilderPortalButton::init(RpgWorldBuilderScene* gameScene, int newPortalKey) {
    init();
    scene = gameScene;
    portalKey = newPortalKey;
    width = scene->engine->screenWidth / WIDTH_ADJUSTOR;
    height = scene->engine->screenHeight / HEIGHT_ADJUSTOR;
}