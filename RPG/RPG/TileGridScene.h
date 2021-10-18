#pragma once
#include "GameScene.h"
#include "MapTile.h"
#include "ZoneMap.h"
#include "GameMenu.h"
#include "RpgGameConstants.h"
#include "CombatText.h"
#include <deque>


class BaseGameEngine;
class Unit;
class Player;
class DooDad;


class TileGridScene : public GameScene
{
public:
    //attributes
    int mainCanvasStartX;
    int xOffset, yOffset;
    std::unordered_map<int, ZoneMap*> zones;
    ZoneMap* currentZone;
    std::unordered_map<int, MapTile> mapTiles;
    std::vector<int> zonePortalImages;
    int tileHeight;
    int tileWidth;
    Player* player;
    int nextZoneId;
    std::unordered_map<int, std::unordered_map<int, int>> teamRelations;
    std::deque<Unit*> unitsNeedingPath;

    //constructor
    TileGridScene();
    TileGridScene(BaseGameEngine* gameEngine);

    //methods
    void desiredPlayerDrawLocation(int desiredCoords[2]);
    void coordsFromTileIndex(int x, int y, int returnCoords[2]);
    virtual void declareSceneAssets() override;
    virtual void setUpScene() override;
    virtual void loadZones();
    virtual void loadZone(int zoneId);
    virtual void createNewZone();
    void deleteZone(int zoneId);
    void saveZones();
    void handleInput() override;
    void sceneLogic() override;
    void renderScene() override;
    Unit* getUnitAtLocation(int zoneId, int x, int y);
    bool isTilePassable(int zoneId, int x, int y);
    void addCombatMessage(std::string text, int tileX, int tileY);
    void addCombatMessage(std::string text, int tileX, int tileY, int duration);
    void addCombatMessage(std::string text, SDL_Color colour, int tileX, int tileY);
    void addCombatMessage(std::string text, SDL_Color colour, int tileX, int tileY, int duration);
    void addDelayedCombatMessage(int delay, std::string text, int tileX, int tileY);
    void addDelayedCombatMessage(int delay, std::string text, int tileX, int tileY, int duration);
    void addDelayedCombatMessage(int delay, std::string text, SDL_Color colour, int tileX, int tileY);
    void addDelayedCombatMessage(int delay, std::string text, SDL_Color colour, int tileX, int tileY, int duration);
    ZonePortal* getPortalAtLocation(ZoneMap* zoneMap, int xpos, int ypos);
    DooDad* getDooDadAtLocation(ZoneMap* zoneMap, int xpos, int ypos);
    void removePortalAtLocation(int zoneId, int xpos, int ypos);
    //void portalUnit(ZonePortal* portal, Unit* unit);
    int getTeamStatus(int unitTeam, int otherUnitTeam);
    //virtual void unitEntersTile(Unit* unit, int x, int y) {};
    void removeUnit(Unit* unit);
    void addItemsToMap(int zone, int x, int y, std::vector<Item*> items);
    bool coordsAreOnDisplayedMapTile(int x, int y);
    bool tileCoordsAreOnDisplayedMapTile(int x, int y);
    //void moveUnitTo(Unit* unit, int zone, int x, int y);
    

protected:
    //attributes
    int desiredTilesAcross;
    int desiredTilesDown;
    
    //methods
    void getTileIndexFromScreenCoords(int x, int y, int tileIndices[2]);
    bool tileCoordsAreDisplayedMapTile(int x, int y);
    Unit* createUnitAtLocation(int zoneId, int unitType, int x, int y);
    

private:
    //attributes
    std::vector<CombatText> combatMessages;

    //methods
    void createTiles();
    void init();
    void drawCombatMessages();
    void updateCombatMessages();
};