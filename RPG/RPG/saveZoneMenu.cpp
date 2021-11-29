#include "saveZoneMenu.h"
#include "RpgWorldBuilderScene.h"
#include "HealingPad.h"
#include "ZoneBuilderMenu.h"

enum SAVE_ZONE_MENU_IDS {
    ZONE_NAME_LABEL,
    ZONE_NAME_TEXT_BOX,
    ZONE_SAVE_OK_BUTTON,
    ZONE_SAVE_CANCEL_BUTTON
};

//constructors
saveZoneMenu::saveZoneMenu() : GameMenu() {
    scene = NULL;
}

saveZoneMenu::saveZoneMenu(RpgWorldBuilderScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos) {
    scene = gameScene;
    buildElements();
}

void saveZoneMenu::open()
{
    scene->closeAllMenus();
    GameMenu::open();
    getElementbyId(ZONE_NAME_TEXT_BOX)->setText(scene->sceneToEdit.zoneName);
}

void saveZoneMenu::buildElements()
{
    //Label and text box
    addElement(ZONE_NAME_LABEL, new MenuText(scene, "Zone Name", { 255, 255, 255 }, xpos + (width - width * 0.8) / 2, ypos + height * 0.015));
    addElement(ZONE_NAME_TEXT_BOX, new TextBox(scene, xpos + (width - width * 0.8) / 2, ypos + height * 0.4, width * 0.8, height * 0.16));
    
    //OK button
    MenuButton* okButton = new MenuButton(this->scene, BUTTON_BACKGROUND, xpos + width * 0.08 , ypos + height * 0.7);
    okButton->setText("OK")->addOnClick([this]() {
        if (getElementbyId(ZONE_NAME_TEXT_BOX)->getText().length() > 0)
        {
            scene->sceneToEdit.zoneName = getElementbyId(ZONE_NAME_TEXT_BOX)->getText();
            ((ZoneBuilderMenu*)scene->menus[BUILD_MENU])->setZoneDifficulty();
            ((ZoneBuilderMenu*)scene->menus[BUILD_MENU])->setZoneType();
            //scene->sceneToEdit.doodads.clear();
            //scene->sceneToEdit.backGroundTile = MOUNTAIN;
            //scene->sceneToEdit.mobSpawn = false;
            //scene->sceneToEdit.doodads.push_back(new HealingPad(scene, BLANK_PORTAL, 11, 3));
            RpgZone* newZone = &scene->sceneToEdit;
            scene->addZone(newZone->id, new RpgZone(*newZone));
            scene->saveZones();
            close();
        }
        });
    addElement(ZONE_SAVE_OK_BUTTON, okButton);

    //Cancel button
    MenuButton* cancelButton = new MenuButton(this->scene, BUTTON_BACKGROUND, xpos + width * 0.55, ypos + height * 0.7);
    cancelButton->setText("Cancel")->addOnClick([this] {
        close();
        });
    addElement(ZONE_SAVE_CANCEL_BUTTON, cancelButton);
}
