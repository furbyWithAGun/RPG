#pragma once
#include "TileGridScene.h"
#include "BuildingFactory.h"
#include "CombatText.h"
#include "ItemShop.h"
#include "Player.h"
#include "RpgGameConstants.h"
#include "TownCommand.h"

class Player;

class RpgTileGridScene : public TileGridScene
{
public:
    //attributes
    Player* player;
    std::unordered_map<int, std::unordered_map<int, int>> teamRelations;
    Building buildingBeingPlaced;
    DooDad dooDadgBeingPlaced;
    bool placingBuilding;
    bool placingDooDad;

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
    bool buildingCanBePlacedAtLocation(Building* building, ZoneMap* zoneMap, int xpos, int ypos);
    bool buildingCanBePlacedAtLocation(Building* building, ZoneMap* zoneMap, Location* location);
    void payBuildingCosts(Building* building);
    bool canAffordBuilding(Building* building);
    virtual void loadZones() override;
    void resizeTiles();

protected:
    virtual RpgUnit* createUnitAtLocation(int zoneId, int unitType, int x, int y);
    virtual RpgUnit* createUnitAtLocation(ZoneMap* zone, int unitType, int x, int y);
    Building* createBuildingAtLocation(int zoneId, int buildingType, int direction, int x, int y);
    Building* createBuildingAtLocation(ZoneMap* zone, int buildingType, int direction, int x, int y);
    void removeBuildingFromZone(ZoneMap* zone, Building* building);
    void removeBuildingFromZone(ZoneMap zone, Building* building);
    void scrollCamera();

private:
    //attributes
    std::vector<CombatText> combatMessages;
    
    //methods
    void createTiles();
    void init();
    void drawCombatMessages();
    void updateCombatMessages();
};

