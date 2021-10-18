// Includes
#include "BaseGameEngine.h"
#include "RpgWorldBuilderScene.h"
#include "RpgOverWorldScene.h"
#include "RpgGameConstants.h"
#include "MainMenuScene.h"

//TODO:
//move to database system
//design how game will track structures
//make a structure building scene
//make units savable
//add ability to place enemy units in world builder scene
//pathfinding
//make the game client/server
//rework asset loading strategy
//add a cleanup method to GameScene and have the engine call it when scene is over (units are a memory leak when changing scenes, as are UiElements)
// will need destructors for menus as well.
//create destructors for units (Attack pointers are a memory leak, as are the unit states)
//make semi-not-terrible player animations ***DO IT YOU SLACKER***
//game message system
//ranged combat
//improve attack functionality
//attack animation

int main(int argc, char* args[])
{
    //local vars
    BaseGameEngine engine = BaseGameEngine(GAME_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

    engine.init();
    engine.addScene(MAIN_MENU_SCENE, new MainMenuScene(&engine));
    engine.setNextScene(MAIN_MENU_SCENE);
    engine.startMainGameLoop();

    //terminate the engine
    engine.close();
    return 0;
}