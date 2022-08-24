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
    int sWidth = engine->screenWidth;
    int sHeight = engine->screenHeight;
    double rowRatio = 0.1;
    int inboxWidth = sWidth * 0.05;
    int inboxHeight = sHeight * 0.035;
    addElement(new MenuText(scene, "Size", {255, 255, 255}, xpos + sWidth * 0.1, ypos + sHeight * 0.01));
    addElement(new MenuText(scene, "X: ", { 255, 255, 255 }, xpos + sWidth * 0.01, ypos + sHeight * rowRatio));
    addElement(new MenuText(scene, "Y:", { 255, 255, 255 }, xpos + sWidth * 0.1, ypos + sHeight * rowRatio));
    addElement(X_SIZE_VAL_TEXT_BOX,new TextBox(scene, xpos + sWidth * 0.03, ypos + sHeight * rowRatio, inboxWidth, inboxHeight));
    addElement(Y_SIZE_VAL_TEXT_BOX,new TextBox(scene, xpos + sWidth * 0.12, ypos + sHeight * rowRatio, inboxWidth, inboxHeight));
    addElement(new MenuText(scene, "New Zone Type:", { 255, 255, 255 }, xpos + sWidth * 0.01, ypos + sHeight * rowRatio * 2));
    addElement(NEW_ZONE_TYPE_TEXT_BOX, new TextBox(scene, xpos + sWidth * 0.13, ypos + sHeight * rowRatio * 2, inboxWidth, inboxHeight));
    addElement((new MenuButton(scene, BUTTON_BACKGROUND, xpos + sWidth * 0.02, ypos + sHeight * rowRatio * 3))->setText("Create")->addOnClick([this]() {
        scene->addCommand(new InputMessage(WORLD_BUILDER_CREATE_NEW_ZONE, ((TextBox*)getElementbyId(X_SIZE_VAL_TEXT_BOX))->getIntInput(), ((TextBox*)getElementbyId(Y_SIZE_VAL_TEXT_BOX))->getIntInput(), ((TextBox*)getElementbyId(NEW_ZONE_TYPE_TEXT_BOX))->getIntInput()));
        }));
    addElement((new MenuButton(scene, BUTTON_BACKGROUND, xpos + sWidth * 0.12, ypos + sHeight * rowRatio * 3))->setText("Cancel")->addOnClick([this]() {
        close();
        }));
}
