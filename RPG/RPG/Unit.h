#pragma once
#include "AnimatedSprite.h"
#include "TileGridScene.h"
#include "UnitState.h"

class BaseGameEngine;
class InputMessage;

class Unit : public AnimatedSprite
{
public:

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
    //attributes
    int maxHealth;
    int health;
    int speed;
    int getPathTick;
    int getPathRate;
    int adjustPathTick;
    int adjustPathRate;
    int getNewPathFailLimit;
    int getNewPathFailTick;
    int processPathFailLimit;
    int processPathFailTick;
    
    //constructors
    Unit();
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


protected:
    //attributes
    UnitState* currentState;
    void setUnitState(int newState);
    std::unordered_map<int, UnitState*> unitStates;

private:
    //methods
    void init();
    void init(int zoneId, int unitType);
    void init(int zoneId, int unitType, TileGridScene* gameScene);
};
