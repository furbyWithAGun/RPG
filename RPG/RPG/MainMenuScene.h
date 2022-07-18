#pragma once
#include "GameScene.h"
#include "RpgGameConstants.h"
#include "MainMenu.h"
#include "RpgKeysMouseController.h"
#include "LoadSaveGameMenu.h"

class BaseGameEngine;

class MainMenuScene : public GameScene
{
public:
    //constructor
    MainMenuScene();
    MainMenuScene(BaseGameEngine* gameEngine);

    //methods
    void declareSceneAssets() override;
    void setUpScene() override;
    void handleInput() override;
    void sceneLogic() override;
    //void renderScene() override;

private:
    //methods
    void init();

};

