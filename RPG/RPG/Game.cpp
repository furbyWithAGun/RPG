// Includes
#include "BaseGameEngine.h"
#include "RpgWorldBuilderScene.h"
#include "RpgOverWorldScene.h"
#include "RpgGameConstants.h"
#include "MainMenuScene.h"

//TODO:
// shop inventory dependant on town buildings
// town shops max gold for buying player items (dependant on town wealth / buildings)
// better encapsulate building placement/creation. Have buildings have a spawnOtherStuff() type method that the scene calls when placing (for placing doodads/units)
// barracks building
// ability to train troops
// ability to equip troops
// overworld guard posts
// town armoury
// army spawn rate during war will be determined by ratio of army size. If your army outnumbers the other 2:1 your troops will spawn twice as fast
// items that are added to an existing stack may leak memory
// unit spawner limits and spawn logic
// town attacks
// crafting
// ranged combat
// overworld towers / walls
// unit factory
// allied units aggro and attack spawners
// followers
// commands to followers
// town quests
// magic
// make thread for unit aggro
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
// unit target location is likely a memory leak
//add ability to place enemy units in world builder scene
//make the game client/server
//rework asset loading strategy
//add a cleanup method to GameScene and have the engine call it when scene is over (units are a memory leak when changing scenes, as are UiElements)
// will need destructors for menus as well.
//create destructors for units (Attack pointers are a memory leak, as are the unit states)
//game message system
//improve attack functionality
//ability to select stats on level up
//clean up magic numbers

//ally controls
// ctrl + <num> + pointer = assign
// <num> + point = command (on release)
//  -> on hold num -> show path
// rmb + <num> + point = options
// num

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