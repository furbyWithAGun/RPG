#include "OverWorldSceneMenu.h"
#include "RpgOverWorldScene.h"

enum RPG_OVERWORLD_MENU_IDS {
    OPEN_INVENTORY_BUTTON
};

OverWorldSceneMenu::OverWorldSceneMenu() : GameMenu()
{
    init();
}

OverWorldSceneMenu::OverWorldSceneMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos)
{
    init();
    scene = gameScene;
    buildElements();
    isActive = true;
}

void OverWorldSceneMenu::close()
{
    GameMenu::close();
}

bool OverWorldSceneMenu::handleInput(InputMessage* message)
{
    return GameMenu::handleInput(message);
}

void OverWorldSceneMenu::buildElements()
{
    MenuButton* openInvBtn = new MenuButton(OPEN_INVENTORY_BUTTON, scene, BUTTON_BACKGROUND, scene->engine->screenWidth * 0.01, scene->engine->screenHeight * 0.8);
    openInvBtn->setText("Inventory")->addOnClick([this] {
        scene->openMenu(INVENTORY_MENU);
        });
    addElement(OPEN_INVENTORY_BUTTON, openInvBtn);

    HoverToolTip* toolTip = new HoverToolTip(scene, openInvBtn->xpos + openInvBtn->width, openInvBtn->ypos + openInvBtn->height, 100, 100);
    toolTip->subElements.push_back(new MenuText(scene, "test", COLOR_WHITE, 10, 10));
    registerToolTip(openInvBtn, toolTip);
}

void OverWorldSceneMenu::init()
{
    scene = nullptr;
}
