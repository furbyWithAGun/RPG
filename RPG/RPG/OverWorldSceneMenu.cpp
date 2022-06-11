#include "OverWorldSceneMenu.h"
#include "RpgOverWorldScene.h"

enum RPG_OVERWORLD_MENU_IDS {
    OPEN_INVENTORY_BUTTON,
    QUIT_BUTTON,
    SAVE_GAME_BUTTON
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
    MenuButton* openInvBtn = new MenuButton(OPEN_INVENTORY_BUTTON, scene, BUTTON_BACKGROUND, scene->engine->screenWidth * 0.01, scene->engine->screenHeight * 0.7);
    openInvBtn->setText("Inventory")->addOnClick([this] {
        scene->openMenu(INVENTORY_MENU);
        });
    addElement(OPEN_INVENTORY_BUTTON, openInvBtn);

    MenuButton* saveGameButton = new MenuButton(SAVE_GAME_BUTTON, this->scene, BUTTON_BACKGROUND, scene->engine->screenWidth * 0.01, scene->engine->screenHeight * 0.8);
    saveGameButton->setText("Save Game")->addOnClick([this] {
        scene->saveGame();
        });
    addElement(SAVE_GAME_BUTTON, saveGameButton);

    MenuButton* quitButton = new MenuButton(QUIT_BUTTON, this->scene, BUTTON_BACKGROUND, scene->engine->screenWidth * 0.01, scene->engine->screenHeight * 0.9);
    quitButton->setText("Quit")->addOnClick([this] {
        scene->engine->setNextScene(MAIN_MENU_SCENE);
        scene->endScene();
        });
    addElement(QUIT_BUTTON, quitButton);

}

void OverWorldSceneMenu::init()
{
    scene = nullptr;
}
