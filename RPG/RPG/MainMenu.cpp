#include "MainMenu.h"
#include "RpgWorldBuilderScene.h"
#include "RpgOverWorldScene.h"
//const int EXIT_OPTION = NUM_SCENES + 1;

enum MAIN_MENU_OPTIONS {
    EXIT_OPTION = NUM_SCENES + 1,
    LOAD_GAME_OPTION
};

MainMenu::MainMenu() : GameMenu() {
}

MainMenu::MainMenu(GameScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos) {
    buildElements();
    setRGBA(0,0,0,0);
    isActive = true;
}

void MainMenu::open()
{
    scene->closeAllMenus();
    GameMenu::open();
    buildPrompt();
}


void MainMenu::buildElements()
{
    scene->engine->addScene(WORLD_BUILDER, new RpgWorldBuilderScene(engine));
    scene->engine->addScene(OVERWORLD, new RpgOverWorldScene(engine));
    buildPrompt();    
}

void MainMenu::buildPrompt()
{
    SelectPrompt* mainMenuPrompt;
    mainMenuPrompt = new SelectPrompt(scene, COLOR_BLACK, scene->engine->screenWidth * 0.1, scene->engine->screenHeight * 0.1, scene->engine->screenWidth * 0.8, scene->engine->screenHeight * 0.8);
    mainMenuPrompt->addSelectOption("New Game", OVERWORLD);
    mainMenuPrompt->addSelectOption("Load Game", LOAD_GAME_OPTION);
    mainMenuPrompt->addSelectOption("World Builder", WORLD_BUILDER);
    mainMenuPrompt->addSelectOption("Exit", EXIT_OPTION);
    mainMenuPrompt->addCallBack([this, mainMenuPrompt]() {
        int selectedOption = mainMenuPrompt->getSelectedOptionValue();
        if (selectedOption == EXIT_OPTION)
        {
            scene->endScene();
            return;
        }
        else if (selectedOption == LOAD_GAME_OPTION) {
            scene->openMenu(LOAD_GAME_MENU);
            scene->removePrompt(mainMenuPrompt);
        }
        else {
            scene->engine->setNextScene(mainMenuPrompt->getSelectedOptionValue());
            scene->endScene();
        }
        });
    mainMenuPrompt->active = true;
    scene->addPrompt(mainMenuPrompt);
}
