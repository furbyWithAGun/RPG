#pragma once
#include "RpgTileGridScene.h"
#include "RpgKeysMouseController.h"
#include "OverWorldSceneMenu.h"
#include "TownBuildMenu.h"
#include "InventoryMenu.h"
#include "EquippedMenu.h"
#include "itemSellmenu.h"
#include "ItemBuyMenu.h"
#include <cmath>
#include <deque>

class AiUnit;
class AiUnit;
class AiUnit;
class AiUnit;
class AiUnit;
class AiUnit;
class AiUnit;
class RpgUnit;

class RpgOverWorldScene : public RpgTileGridScene
{
public:
    //attributes
    int frames = 0;
    RpgUnit* testUnit;
    bool displayHud;
    //Player* player;

    //constructors
    RpgOverWorldScene();
    RpgOverWorldScene(BaseGameEngine* gameEngine);

    //methods
    void loadZone(int zoneId) override;
    void declareSceneAssets();
    void setUpScene() override;
    void handleInput() override;
    void sceneLogic() override;
    void renderScene() override;
    void renderHUD();
    //void unitEntersTile(Unit* unit, int x, int y) override;

private:
    //attributes
    class AiUnit;
    //AiUnit enemy;
    //AiUnit enemy2;

    //methods
    void init();
    void pickUpItem(RpgUnit* unit, Item* item);
    void pickUpItemAtLocation(RpgUnit* unit, int x, int y);
};



int getPathThread(void* scene);