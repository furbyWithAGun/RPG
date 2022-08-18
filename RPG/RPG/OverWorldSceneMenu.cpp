#include "OverWorldSceneMenu.h"
#include "RpgOverWorldScene.h"

enum RPG_OVERWORLD_MENU_IDS {
    OPEN_INVENTORY_BUTTON,
    QUIT_BUTTON,
    SAVE_GAME_BUTTON,
    OPEN_BUILD_MENU,
    OPEN_CRAFT_MENU
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
    MenuButton* openCraftMenu = new MenuButton(OPEN_CRAFT_MENU, scene, BUTTON_BACKGROUND, scene->engine->screenWidth * 0.01, scene->engine->screenHeight * 0.5);
    openCraftMenu->setText("Craft")->addOnClick([this] {
        //scene->openMenu(CRAFTING_MENU);
        ((CraftingMenu*)scene->menus[CRAFTING_MENU])->open(scene->player, NO_CRAFTING_STATION);
        });
    addElement(OPEN_CRAFT_MENU, openCraftMenu);

    MenuButton* openBuildMenu = new MenuButton(OPEN_BUILD_MENU, scene, BUTTON_BACKGROUND, scene->engine->screenWidth * 0.01, scene->engine->screenHeight * 0.6);
    openBuildMenu->setText("Build")->addOnClick([this] {
        scene->openMenu(TOWN_BUILD_MENU);
        //scene->closeMenu(RPG_OVERWORLD_MENU);
        });
    addElement(OPEN_BUILD_MENU, openBuildMenu);

    MenuButton* openInvBtn = new MenuButton(OPEN_INVENTORY_BUTTON, scene, BUTTON_BACKGROUND, scene->engine->screenWidth * 0.01, scene->engine->screenHeight * 0.7);
    openInvBtn->setText("Inventory")->addOnClick([this] {
        scene->openMenu(INVENTORY_MENU);
        });
    addElement(OPEN_INVENTORY_BUTTON, openInvBtn);

    //save game button
    addElement(SAVE_GAME_BUTTON, (new MenuButton(this->scene, BUTTON_BACKGROUND, scene->engine->screenWidth * 0.01, scene->engine->screenHeight * 0.8))->setText("Save Game")->addOnClick([this] {
        scene->openMenu(SAVE_GAME_MENU);
        }));

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
