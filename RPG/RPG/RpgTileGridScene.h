#pragma once
#include "TileGridScene.h"
#include "RpgGameConstants.h"
#include "BaseGameEngine.h"
#include "Player.h"
#include "Rat.h"
#include "RatKing.h"
#include "WhiteRat.h"
#include "Soldier.h"
#include "TownsPerson.h"
#include "Skeleton.h"
#include "SkeletonKing.h"
#include "RpgTown.h"
#include "RpgProvinceZone.h"
#include "BuildingFactory.h"
#include "CombatText.h"
#include "ItemShop.h"
#include "UnitFactory.h"
#include "DooDadFactory.h"
#include "CraftingRecipe.h"

//class Player;

class RpgTileGridScene : public TileGridScene
{
public:
    //attributes
    Player* player;
    std::unordered_map<int, std::unordered_map<int, int>> teamRelations;
    Building buildingBeingPlaced;
    DooDad dooDadgBeingPlaced;
    Unit unitBeingPlaced;
    bool placingUnit;
    bool placingBuilding;
    bool placingDooDad;
    bool destroyingUnits;

    //pathing rates
    int aggroUpdateRate;

    //constructor
    RpgTileGridScene();
    RpgTileGridScene(BaseGameEngine* gameEngine);

    //methods
    void desiredPlayerDrawLocation(double desiredCoords[2]);
    virtual void declareSceneAssets() override;
    virtual void setUpScene() override;
    virtual void setUpScene(std::string saveFile);
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
    void payBuildingCosts(Building* building, RpgTown* town);
    bool townCanAffordBuilding(Building* building, RpgTown* town);
    bool playerCanAffordBuilding(Building* building);
    virtual void loadZones(std::string saveFile) override;
    virtual void loadZone(SaveObject saveObject);
    void resizeTiles();
    void virtual destroyUnit(RpgUnit* unit);
    void virtual destroyFlaggedUnits();
    void virtual destroyDooDad(DooDad* dooDad);
    void virtual destroyFlaggedDooDads();
    void pickUpItemAtLocation(RpgUnit* unit, int x, int y);
    virtual RpgUnit* createUnitAtLocation(int zoneId, int unitType, int x, int y);
    void setSaveGameName(std::string newSaveGameName);
    std::string getSaveGameName();
    bool unitHasSkillsToCraftRecipe(RpgUnit* craftingUnit, CraftingRecipe* recipe);
    bool unitHasMatsForRecipe(RpgUnit* craftingUnit, CraftingRecipe* recipe);
    void unitCraft(RpgUnit* craftingUnit, CraftingRecipe* recipe, int craftingStation);

protected:
    //attributes
    std::string saveGameName;
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

void addItemToContainer(Item* itemToAdd, std::vector<Item*>& container);
bool containerContainsAmount(int itemType, int qty, std::vector<Item*>& container);
int qtyInContainer(int itemType, std::vector<Item*>& container);
void removeQtyFromContainer(int itemType, int qty, std::vector<Item*>& container);
void removeItemFromContainer(int index, std::vector<Item*>& container);
void removeItemFromContainer(Item* item, std::vector<Item*>& container);
void deleteItemFromContainer(int index, std::vector<Item*>& container);
void deleteItemFromContainer(Item* item, std::vector<Item*>& container);


