#pragma once
#include "AnimatedSprite.h"
#include "TileGridScene.h"
#include "UnitState.h"

class BaseGameEngine;
class InputMessage;

enum UNIT_SAVE_ATTRIBUTES {
    UNIT_ID,
    UNIT_BEING_TARGETED_BY,
    UNIT_TO_BE_DELETED,
    UNIT_TYPE,
    UNIT_TILE_LOCATION,
    UNIT_TILE_DESTINATION,
    UNIT_NAME,
    UNIT_LEFT_TO_MOVE,
    UNIT_IS_STATIC,
    UNIT_IS_PLAYER_CONTROLLED,
    UNIT_MOVING_UP,
    UNIT_MOVING_DOWN,
    UNIT_MOVING_LEFT,
    UNIT_MOVING_RIGHT,
    UNIT_DIRECTION_FACING,
    UNIT_CAN_GO_THROUGH_PORTAL,
    UNIT_ZONE,
    UNIT_TARGET_UNIT,
    UNIT_TARGET_LOCATION,
    UNIT_PATH_DIRECTIONS,
    UNIT_CURRENT_STATE,
    UNIT_MAX_HEALTH,
    UNIT_HEALTH,
    UNIT_SPEED,
    NUM_UNIT_ATTRIBUTES
};

class Unit : public AnimatedSprite
{
public:
    int id;
    std::vector<Unit*> beingTargetedBy;
    bool toBeDeleted;
    int type;
    TileGridScene* scene;
    Location* tileLocation;
    Location* tileDestination;
    std::string name;
    double leftToMove;
    bool isStatic, isPlayerControlled;
    bool movingUp, movingDown, movingRight, movingLeft;
    int directionFacing;
    bool canGoThroughPortal;
    int zone;
    Unit* targetUnit;
    Location* targetLocation;
    //std::vector<std::vector<int>> directions = { {0, -1},{0, 1},{-1, 0},{1, 0},{1, -1},{1, 1},{-1, -1},{-1, 1} }; // UP, DOWN, LEFT, RIGHT, UP RIGHT, DOWN RIGHT, UP LEFT, DOWN LEFT
    std::vector<int> pathDirections;
    int getPathTick;
    int getPathRate;
    int adjustPathTick;
    int adjustPathRate;
    int getNewPathFailLimit;
    int getNewPathFailTick;
    int processPathFailLimit;
    int processPathFailTick;
    UnitState* currentState;
    //attributes
    int maxHealth;
    int health;
    int speed;
    //special attributes for loading saved units
    int savedSceneId;
    int savedTargetUnitId;
    int savedCurrentStateId;
    std::vector<int> savedBeingTargetedByIds;
    
    //constructors
    Unit();
    Unit(SaveObject saveObject, TileGridScene* gameScene);
    Unit(int zoneId, int unitType);
    Unit(int zoneId, int unitType, TileGridScene* gameScene);
    Unit(int zoneId, int unitType, TileGridScene* gameScene, int startX, int startY);

    //destructor
    ~Unit();

    //methods
    bool isAlive();
    void startMovement(int direction);
    bool updateMovement();
    bool processPath();
    void setTargetLocation(Location* newTargetLocation);
    void setTargetUnit(Unit* newTargetUnit);
    void setTileLocation(int x, int y);
    void moveTo(int x, int y);
    virtual void portalTo(int zoneId, int x, int y);
    void updateCoords();
    void setStartLocation(int x, int y);
    virtual void createAnimations() {};
    virtual void draw();
    virtual void update();
    void getLocationUnitIsFacing(int tileXY[2]);
    void getLocationUnitDestinationIsFacing(int tileXY[2]);
    void handleInput(InputMessage* message);
    void faceCoords(int x, int y);
    void getNewPath();
    void setScene(TileGridScene* gameScene);
    
    virtual std::string toSaveString(bool withHeaderAndFooter = true);



protected:
    //attributes
    std::unordered_map<int, UnitState*> unitStates;

    //methods
    void setUnitState(int newState);

private:
    //methods
    void init();
    void init(int zoneId, int unitType);
    void init(int zoneId, int unitType, TileGridScene* gameScene);
};

int getUniqueUnitId();