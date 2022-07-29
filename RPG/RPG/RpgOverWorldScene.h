#pragma once
#include "RpgTileGridScene.h"
#include "RpgKeysMouseController.h"
#include "OverWorldSceneMenu.h"
#include "TownBuildMenu.h"
#include "InventoryMenu.h"
#include "EquippedMenu.h"
#include "ItemShopMenu.h"
#include "TransferItemsMenu.h"
#include "SaveGameMenu.h"
#include <cmath>
#include <deque>

class AiUnit;
class RpgUnit;

const int MAX_NUM_SQUAD_UNITS = 8;

class RpgOverWorldScene : public RpgTileGridScene
{
public:
    //attributes
    int frames = 0;
    RpgUnit* testUnit;
    bool displayHud;
    //Player* player;
    bool pathfindThreadActive;
    bool aggroThreadActive;
    SDL_Thread* pathFindingThread;
    SDL_Thread* aggroThread;

    //constructors
    RpgOverWorldScene();
    RpgOverWorldScene(BaseGameEngine* gameEngine);

    //methods
    void saveGame();
    void setCurrentZone(int zoneId) override;
    void declareSceneAssets();
    void setUpScene() override;
    void handleInput() override;
    void sceneLogic() override;
    void renderScene() override;
    void renderHUD();
    void virtual destroyUnit(RpgUnit* unit) override;
    void setSaveGameName(std::string newSaveGameName);
    std::string getSaveGameName();

private:
    //attributes
    std::unordered_map<int, std::vector<ChanceObject>> monsterTable;
    std::unordered_map<int, AiUnit*> squadUnits;
    std::string saveGameName;

    //methods
    void init();
    void pickUpItem(RpgUnit* unit, Item* item);
    int getUnitTypeByDifficulty(int difficulty);
    void setUpMonsterTable();
};



int getPathThread(void* scene);
int updateAggroThread(void* scene);