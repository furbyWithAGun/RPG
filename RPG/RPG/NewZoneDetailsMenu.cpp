#include "NewZoneDetailsMenu.h"
#include "RpgWorldBuilderScene.h"
#include "TextBox.h"
#include "MenuButton.h"

enum ZONE_DETAILS_MENU_IDS {
    X_SIZE_VAL_TEXT_BOX,
    Y_SIZE_VAL_TEXT_BOX,
    NEW_ZONE_TYPE_TEXT_BOX
};

NewZoneDetailsMenu::NewZoneDetailsMenu() : GameMenu()
{
    init();
}

NewZoneDetailsMenu::NewZoneDetailsMenu(RpgWorldBuilderScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos)
{
    init(gameScene);
    buildElements();
}

NewZoneDetailsMenu::NewZoneDetailsMenu(RpgWorldBuilderScene* gameScene, int newId) : GameMenu(gameScene, newId)
{
    init(gameScene);
    buildElements();
}

void NewZoneDetailsMenu::init()
{
    scene = nullptr;
}

void NewZoneDetailsMenu::init(RpgWorldBuilderScene* gameScene)
{
    init();
    scene = gameScene;
}

void NewZoneDetailsMenu::buildElements()
{
    addElement(new MenuText(scene, "Size", xpos, ypos));
    addElement(new MenuText(scene, "X: ", xpos, ypos));
    addElement(new MenuText(scene, "Y:", xpos, ypos));
    addElement(X_SIZE_VAL_TEXT_BOX,new TextBox(scene, xpos + 100, ypos + 100, 100, 100));
    addElement(Y_SIZE_VAL_TEXT_BOX,new TextBox(scene, xpos + 200, ypos + 200, 100, 100));
    addElement(new MenuText(scene, "New Zone Type:", xpos, ypos));
    //addElement(NEW_ZONE_TYPE_TEXT_BOX, new TextBox(scene, xpos, ypos, 100, 100));
    addElement((new MenuButton(scene, BUTTON_BACKGROUND, xpos + 400, ypos + 400))->setText("Create")->addOnClick([this]() {
        scene->addCommand(new InputMessage(WORLD_BUILDER_CREATE_NEW_ZONE, 100, 100, 0));
        }));
}
