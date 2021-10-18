#include "MainMenuScene.h"
#include "BaseGameEngine.h"



//constructors
MainMenuScene::MainMenuScene() : GameScene() {
    init();
}

MainMenuScene::MainMenuScene(BaseGameEngine* gameEngine) : GameScene((BaseGameEngine*)gameEngine) {
    init();
}

void MainMenuScene::setUpScene()
{
    menus[MAIN_MENU] = new MainMenu(this, MAIN_MENU, engine->screenWidth, engine->screenHeight, 0, 0);
}

//methods
void MainMenuScene::init() {
    controllerInterface = new RpgKeysMouseController();
}