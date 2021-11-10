#include "PortalPropertiesMenu.h"
#include "RpgWorldBuilderScene.h"

enum PORTAL_PROPERTIES_MENU_IDS  {
    PORTAL_PROPERTIES_LABEL,
    EXIT_ZONE_ID_LABEL,
    EXIT_ZONE_COORDS_LABEL,
    EXIT_ZONE_ID_TEXT,
    EXIT_COORDS_X_TEXT,
    EXIT_COORDS_Y_TEXT,
    PORTAL_PROPERTIES_OK_BUTTON,
    PORTAL_PROPERTIES_CANCEL_BUTTON,
    SELECT_PORTAL_EXIT_ID_BUTTON,
    SELECT_PORTAL_EXIT_COORDS_BUTTON
};

PortalPropertiesMenu::PortalPropertiesMenu() : GameMenu()
{
    scene = NULL;
    portalToEdit = NULL;
}

PortalPropertiesMenu::PortalPropertiesMenu(RpgWorldBuilderScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos)
{
    scene = gameScene;
    portalToEdit = NULL;
    buildElements();
}

void PortalPropertiesMenu::open(ZonePortal* newPortal) {
    scene->closeAllMenus();
    GameMenu::open();
    portalToEdit = newPortal;
    getElementbyId(EXIT_ZONE_ID_TEXT)->setText(std::to_string(portalToEdit->exitZoneId));
    getElementbyId(EXIT_COORDS_X_TEXT)->setText(std::to_string(portalToEdit->exitTileCoords[0]));
    getElementbyId(EXIT_COORDS_Y_TEXT)->setText(std::to_string(portalToEdit->exitTileCoords[1]));
}

void PortalPropertiesMenu::setExitZoneCoords(int newCoords[2])
{
    portalToEdit->exitTileCoords[0] = newCoords[0];
    portalToEdit->exitTileCoords[1] = newCoords[1];
    getElementbyId(EXIT_COORDS_X_TEXT)->setText(std::to_string(portalToEdit->exitTileCoords[0]));
    getElementbyId(EXIT_COORDS_Y_TEXT)->setText(std::to_string(portalToEdit->exitTileCoords[1]));
}

void PortalPropertiesMenu::draw()
{
    GameMenu::draw();
}

bool PortalPropertiesMenu::handleInput(InputMessage* message)
{
    bool messageConsumed = false;
    if (GameMenu::handleInput(message))
    {
        messageConsumed = true;
    }
    return messageConsumed;
}

void PortalPropertiesMenu::setPortalBeingBuiltProperties()
{
    portalToEdit->exitZoneId = stoi(getElementbyId(EXIT_ZONE_ID_TEXT)->getText());
    portalToEdit->exitTileCoords[0] = stoi(getElementbyId(EXIT_COORDS_X_TEXT)->getText());
    portalToEdit->exitTileCoords[1] = stoi(getElementbyId(EXIT_COORDS_Y_TEXT)->getText());
}

void PortalPropertiesMenu::open()
{
    scene->closeAllMenus();
    GameMenu::open();
}

void PortalPropertiesMenu::buildElements()
{
    addElement(PORTAL_PROPERTIES_LABEL, new MenuText(scene, "Portal Properties", { 255, 255, 255 }, xpos + engine->screenWidth * 0.01, ypos + engine->screenHeight * 0.01));
    addElement(EXIT_ZONE_ID_LABEL, new MenuText(scene, "Exit Zone ID", { 255, 255, 255 }, xpos + engine->screenWidth * 0.01, ypos + engine->screenHeight * 0.05));
    addElement(EXIT_ZONE_ID_TEXT, new TextBox(scene, xpos + engine->screenWidth * 0.01, ypos + engine->screenHeight * 0.09, engine->screenWidth * 0.02, engine->screenWidth * 0.02));
    addElement(EXIT_ZONE_COORDS_LABEL, new MenuText(scene, "Exit Zone Coords", { 255, 255, 255 }, xpos + engine->screenWidth * 0.01, ypos + engine->screenHeight * 0.13));
    addElement(EXIT_COORDS_X_TEXT, new TextBox(scene, xpos + engine->screenWidth * 0.01, ypos + engine->screenHeight * 0.17, engine->screenWidth * 0.02, engine->screenWidth * 0.02));
    addElement(EXIT_COORDS_Y_TEXT, new TextBox(scene, xpos + engine->screenWidth * 0.04, ypos + engine->screenHeight * 0.17, engine->screenWidth * 0.02, engine->screenWidth * 0.02));
    addElement(PORTAL_PROPERTIES_OK_BUTTON, new PortalPropertiesOkButton(this, xpos + engine->screenWidth * 0.01, ypos + engine->screenHeight * 0.22, BUTTON_BACKGROUND));
    MenuButton* cancelButton = new MenuButton(this->scene, BUTTON_BACKGROUND, xpos + engine->screenWidth * 0.08, ypos + engine->screenHeight * 0.22);
    cancelButton->addOnClick([this]() {
        close();
        })->setText("Cancel");
        addElement(PORTAL_PROPERTIES_CANCEL_BUTTON, cancelButton);

        //select exit zone
        MenuButton* selectExitIdButton = new MenuButton(this->scene, BUTTON_BACKGROUND, xpos + engine->screenWidth * 0.04, ypos + engine->screenHeight * 0.09);
        selectExitIdButton->addOnClick([this]() {
            SelectPrompt* zoneSelectPrompt;
            zoneSelectPrompt = new SelectPrompt(this->scene, COLOR_BLACK, this->xpos + this->width, this->ypos, 300, 300);
            for (auto zone : this->scene->getZones())
            {
                zoneSelectPrompt->addSelectOption(zone.second->zoneName, zone.second->id);
            }
            zoneSelectPrompt->addCallBack([this, zoneSelectPrompt]() {
                getElementbyId(EXIT_ZONE_ID_TEXT)->setText(std::to_string(zoneSelectPrompt->getSelectedOptionValue()));
                this->scene->removePrompt(zoneSelectPrompt);
                });
            zoneSelectPrompt->active = true;
            this->scene->addPrompt(zoneSelectPrompt);
            })->setText("Select Zone");
            addElement(SELECT_PORTAL_EXIT_ID_BUTTON, selectExitIdButton);

        //select exit corrds
        MenuButton* selectExitCoordsButton = new MenuButton(this->scene, BUTTON_BACKGROUND, xpos + engine->screenWidth * 0.08, ypos + engine->screenHeight * 0.17);
        selectExitCoordsButton->addOnClick([this]() {
            this->scene->pickingPortalCoords = true;
            //scene->portalExitZone = scene->zones[portalToEdit->exitZoneId];
            scene->portalExitZone = scene->getZones()[stoi(getElementbyId(EXIT_ZONE_ID_TEXT)->getText())];
            close();
            })->setText("Select Location");
        addElement(SELECT_PORTAL_EXIT_COORDS_BUTTON, selectExitCoordsButton);
}
