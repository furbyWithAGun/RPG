#pragma once
#include "AnimatedSprite.h"
#include "RpgGameConstants.h"
#include "TileGridScene.h"
#include "Attack.h"
#include "UnitState.h"
#include "IdleState.h"
#include "MovingState.h"
#include "AttackingState.h"
#include "BareHands.h"
#include "ItemFactory.h"

enum EXPERIENCE_TYPES {
    COMBAT_EXPERIENCE
};


class BaseGameEngine;
class InputMessage;

class Unit : public AnimatedSprite
{
public:
    //attributes
    std::unordered_map<int, int> nextLevelExp = {
    {1, 15},
    {2, 20},
    {3, 40},
    {4, 50},
    {5, 70},
    {6, 80},
    {7, 100},
    {8, 115},
    {9, 140},
    {10, 200},
    {11, 250},
    {12, 300},
    {13, 400},
    {14, 550},
    {15, 700}
    };
    std::vector<Unit*> beingTargetedBy;
    bool toBeDeleted;
    int type;
    int gold;
    int goldValue;
    int expValue;
    TileGridScene* scene;
    Location* tileLocation;
    Location* tileDestination;
    std::string name;
    double leftToMove;
    bool isStatic, isPlayerControlled;
    bool movingUp, movingDown, movingRight, movingLeft;
    int directionFacing;
    bool canGoThroughPortal;
    int team;
    int zone;
    std::unordered_map<int, Equipment*> equippedItems;
    std::vector<Item*> inventory;
    Building* assignedToBuilding;
    std::vector<chanceObject> dropTable;
    int minNumDrops;
    int maxNumDrops;
    double dropChance;
    Unit* targetUnit;
    Location* targetLocation;
    int aggroTriggerDistance, aggroMaintainDistance;
    std::vector<std::vector<int>> directions = { {0, -1},{0, 1},{-1, 0},{1, 0},{1, -1},{1, 1},{-1, -1},{-1, 1} }; // UP, DOWN, LEFT, RIGHT, UP RIGHT, DOWN RIGHT, UP LEFT, DOWN LEFT
    std::vector<int> pathDirections;
    int aggroUpdateRate;
    int aggroUpdateTick;
    int getPathTick;
    int getPathRate;
    int adjustPathTick;
    int adjustPathRate;
    int getNewPathFailLimit;
    int getNewPathFailTick;
    int processPathFailLimit;
    int processPathFailTick;
    
    //character stats
    int maxHealth;
    int health;
    int maxMana;
    int mana;
    int speed;
    int dex;
    int str;
    int agi;
    int end;
    int intl;
    int baseArmour;
    int armour;
    int combatExperience;
    int combatExperienceNextLevel;
    int combatExperienceLastLevel;
    int combatLevel;

    //actions
    std::unordered_map<int, Attack*> equipedAttacks;
    Attack* activeAttack;


    //constructors
    Unit();
    Unit(int zoneId, int unitType);
    Unit(int zoneId, int unitType, TileGridScene* gameScene);
    Unit(int zoneId, int unitType, TileGridScene* gameScene, int startX, int startY);

    //destructor
    ~Unit();

    //methods
    void startMovement(int direction);
    bool updateMovement();
    bool processPath();
    void setTargetLocation(Location* newTargetLocation);
    void setTargetUnit(Unit* newTargetUnit);
    void setTileLocation(int x, int y);
    void moveTo(int x, int y);
    void portalTo(int zoneId, int x, int y);
    void updateCoords();
    void setStartLocation(int x, int y);
    virtual void createAnimations() {};
    void draw();
    virtual void update();
    bool performAttack(int attackId);
    int assignDamage(int damageTaken);
    int assignDamage(Unit* attackingUnit, int damageTaken);
    void getLocationUnitIsFacing(int tileXY[2]);
    void getLocationUnitDestinationIsFacing(int tileXY[2]);
    void drawHealth();
    void handleInput(InputMessage* message);
    void updateAttacks();
    void faceCoords(int x, int y);
    void addExp(int expType, int expValue);
    bool isAlive();
    void levelUp();
    void updateStats();
    int getTeamStatus(Unit* otherUnit);
    void death();
    void death(Unit* attackingUnit);
    bool equipItem(Equipment* item);
    Weapon* getEquippedWeapon();
    void dropItemFromInventory(int inventoryIndex);
    void deleteItemFromInventory(int inventoryIndex);
    void deleteItemFromInventory(Item* itemToDelete);
    std::vector<Item*> getDrops();
    virtual void setDropTable() {};
    void updateAggro();
    void updateAggro2();
    void getNewPath();


protected:
    void setUnitState(int newState);

private:
    //attributes
    UnitState* currentState;
    std::unordered_map<int, UnitState*> unitStates;

    //methods
    void init();
    void init(int zoneId, int unitType);
    void init(int zoneId, int unitType, TileGridScene* gameScene);
};
