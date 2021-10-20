#pragma once
#include "TileGridScene.h"
#include "CombatText.h"
#include "ItemShop.h"

class Player;

class RpgTileGridScene : public TileGridScene
{
public:
    //attributes
    Player* player;
    std::unordered_map<int, std::unordered_map<int, int>> teamRelations;

    //constructor
    RpgTileGridScene();
    RpgTileGridScene(BaseGameEngine* gameEngine);

    //methods
    void desiredPlayerDrawLocation(int desiredCoords[2]);
    virtual void declareSceneAssets() override;
    virtual void setUpScene() override;
    void handleInput() override;
    void sceneLogic() override;
    void renderScene() override;
    void addCombatMessage(std::string text, int tileX, int tileY);
    void addCombatMessage(std::string text, int tileX, int tileY, int duration);
    void addCombatMessage(std::string text, SDL_Color colour, int tileX, int tileY);
    void addCombatMessage(std::string text, SDL_Color colour, int tileX, int tileY, int duration);
    void addDelayedCombatMessage(int delay, std::string text, int tileX, int tileY);
    void addDelayedCombatMessage(int delay, std::string text, int tileX, int tileY, int duration);
    void addDelayedCombatMessage(int delay, std::string text, SDL_Color colour, int tileX, int tileY);
    void addDelayedCombatMessage(int delay, std::string text, SDL_Color colour, int tileX, int tileY, int duration);
    int getTeamStatus(int unitTeam, int otherUnitTeam);
    RpgUnit* getUnitAtLocation(int zoneId, int x, int y);

protected:
    virtual RpgUnit* createUnitAtLocation(int zoneId, int unitType, int x, int y);
    Building* createBuildingAtLocation(int zoneId, int buildingType, int direction, int x, int y);

private:
    //attributes
    std::vector<CombatText> combatMessages;
    
    //methods
    void createTiles();
    void init();
    void drawCombatMessages();
    void updateCombatMessages();

};

