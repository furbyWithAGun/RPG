// Includes
#include "BaseGameEngine.h"
#include "RpgWorldBuilderScene.h"
#include "RpgOverWorldScene.h"
#include "RpgGameConstants.h"
#include "MainMenuScene.h"

//TODO:
// unit spawners
// unit spawn table by difficulty
// open inventory by pressing 'i' key
// easy switch between buy/sell
// show inventory when at shop
// town quests
// town attacks
// crafting
// ranged combat
// overworld towers / walls
// unit factory
// Town class
// allied units aggro and attack spawners
// followers
// commands to followers
// magic
// fix the item menus update and rebuildElements methods - all alterations to unit inventories should be behind methods. No direct access to that vector - make the inventory vector private
// move includes for Menu Ui elements (buttons text etc to the base menu class)
// map rendering layers
// design tavern
// design blacksmith
// design armoury
// design granery
// design storage pit
// design house
// make it so buildings can have multiple floors
// make it so buildings can have roofs that are hidden when inside the building
// add Art/animations from Tim
// add ability to recruit soldiers
//move to database system
//make a structure building scene
//add ability to place enemy units in world builder scene
//make the game client/server
//rework asset loading strategy
//add a cleanup method to GameScene and have the engine call it when scene is over (units are a memory leak when changing scenes, as are UiElements)
// will need destructors for menus as well.
//create destructors for units (Attack pointers are a memory leak, as are the unit states)
//game message system
//ranged combat
//improve attack functionality
//attack animation
//ability to select stats on level up

int main(int argc, char* args[])
{
    //local vars
    BaseGameEngine engine = BaseGameEngine(GAME_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

    engine.setTicksPerSecond(RPG_GAME_TICKS_PER_SECOND);
    engine.init();
    engine.addScene(MAIN_MENU_SCENE, new MainMenuScene(&engine));
    engine.setNextScene(MAIN_MENU_SCENE);
    engine.startMainGameLoop();

    //terminate the engine
    engine.close();
    return 0;
}