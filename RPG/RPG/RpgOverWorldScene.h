#pragma once
#include "TileGridScene.h"
#include "Player.h"
#include "AiUnit.h"
#include "RpgKeysMouseController.h"
#include "OverWorldSceneMenu.h"
#include "InventoryMenu.h"
#include "EquippedMenu.h"
#include "itemSellmenu.h"
#include "ItemBuyMenu.h"
#include <cmath>
#include <deque>

class RpgOverWorldScene : public TileGridScene
{
public:
    //attributes
    int frames = 0;
    Unit* testUnit;
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
    AiUnit enemy;
    AiUnit enemy2;

    //methods
    void init();
    void pickUpItem(Unit* unit, Item* item);
    void pickUpItemAtLocation(Unit* unit, int x, int y);
};



int getPathThread(void* scene);