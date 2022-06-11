#include "SaveGameMenu.h"
#include "RpgOverWorldScene.h"

enum SAVE_ZONE_MENU_IDS {
    SAVE_NAME_LABEL,
    SAVE_NAME_TEXT_BOX,
    GAME_SAVE_OK_BUTTON,
    GAME_SAVE_CANCEL_BUTTON
};

//constructors
SaveGameMenu::SaveGameMenu() : GameMenu() {
    scene = NULL;
}

SaveGameMenu::SaveGameMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos) {
    scene = gameScene;
    buildElements();
}

void SaveGameMenu::open()
{
    scene->closeAllMenus();
    GameMenu::open();
    scene->openMenu(RPG_OVERWORLD_MENU);
    //getElementbyId(ZONE_NAME_TEXT_BOX)->setText(scene->sceneToEdit.zoneName);
}

void SaveGameMenu::buildElements()
{
    //Label and text box
    addElement(SAVE_NAME_LABEL, new MenuText(scene, "Zone Name", { 255, 255, 255 }, xpos + (width - width * 0.8) / 2, ypos + height * 0.015));
    addElement(SAVE_NAME_TEXT_BOX, new TextBox(scene, xpos + (width - width * 0.8) / 2, ypos + height * 0.4, width * 0.8, height * 0.16));

    //OK button
    MenuButton* okButton = new MenuButton(this->scene, BUTTON_BACKGROUND, xpos + width * 0.08, ypos + height * 0.7);
    okButton->setText("OK")->addOnClick([this]() {
        if (getElementbyId(SAVE_NAME_TEXT_BOX)->getText().length() > 0)
        {
            scene->setSaveGameName(getElementbyId(SAVE_NAME_TEXT_BOX)->getText());
            scene->saveGame();
            close();
        }
        });
    addElement(GAME_SAVE_OK_BUTTON, okButton);

    //Cancel button
    MenuButton* cancelButton = new MenuButton(this->scene, BUTTON_BACKGROUND, xpos + width * 0.55, ypos + height * 0.7);
    cancelButton->setText("Cancel")->addOnClick([this] {
        close();
        });
    addElement(GAME_SAVE_CANCEL_BUTTON, cancelButton);
}
