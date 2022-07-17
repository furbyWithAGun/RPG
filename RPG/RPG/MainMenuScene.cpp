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
    menus[LOAD_GAME_MENU] = new LoadSaveGameMenu(this, (RpgOverWorldScene*) engine->scenes[OVERWORLD], MAIN_MENU, engine->screenWidth, engine->screenHeight, 0, 0);
}

void MainMenuScene::handleInput()
{
    GameScene::handleInput();
    InputMessage* message = new InputMessage();
    while (controllerInterface->getNextMessage(message)) {
        switch (message->id)
        {
        case END_SCENE:
            endScene();
            break;
        default:
            break;
        }
    }
}

//methods
void MainMenuScene::init() {
    controllerInterface = new RpgKeysMouseController();
}