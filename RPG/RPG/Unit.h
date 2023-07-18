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

enum UNIT_SKILL_ATTR_SAVE_ATTRIBUTES {
    SKILL_ATTR_LEVEL = NUM_UNIT_ATTRIBUTES + 20000,
    SKILL_ATTR_BASE_LEVEL,
    SKILL_ATTR_EXP,
    SKILL_ATTR_EXP_NXT_LVL,
    SKILL_ATTR_EXP_LAST_LVL,
    SKILL_ATTR_ID
};

struct unitSkillAttributeData {
    int level, baseLevel, experience, experienceNextLevel, experienceLastLevel, id;
};

class Unit : public AnimatedSprite
{
public:
    SDL_SpinLock deleteLock;
    int id;
    bool gettingPath;
    int type;
    TileGridScene* scene;
    Location* tileLocation;
    Location* tileDestination;
    Location* tileLocationBuffer;
    Location* tileDestinationBuffer;
    std::string name;
    double leftToMove;
    double leftToMoveBuffer;
    bool isStatic, isPlayerControlled;
    bool movingUp, movingDown, movingRight, movingLeft;
    int directionFacing;
    bool canGoThroughPortal;
    //std::vector<std::vector<int>> directions = { {0, -1},{0, 1},{-1, 0},{1, 0},{1, -1},{1, 1},{-1, -1},{-1, 1} }; // UP, DOWN, LEFT, RIGHT, UP RIGHT, DOWN RIGHT, UP LEFT, DOWN LEFT
    std::vector<int> pathDirections;
    int getPathTick;
    int adjustPathTick;
    int getNewPathFailTick;
    int processPathFailTick;
    UnitState* currentState;
    //attributes
    //special attributes for loading saved units
    int savedSceneId;
    int savedTargetUnitId;
    int savedCurrentStateId;
    std::vector<int> savedBeingTargetedByIds;
    //pathfinding rates
    int getPathRate;
    int adjustPathRate;
    //force move
    bool ignoreThreatsWhileMoving;
    
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
    Location* getTargetLocation();
    void setTargetLocation(Location* newTargetLocation);
    void setTargetLocation(int newX, int newY);
    void setTargetUnit(Unit* newTargetUnit);
    void clearTargetUnit();
    Unit* getTargetUnit();
    void setTileLocation(int x, int y);
    void clearTargetLocation();
    void moveTo(int x, int y);
    virtual void portalTo(int zoneId, int x, int y);
    void updateCoords();
    void setStartLocation(int x, int y);
    virtual void createAnimations() {};
    virtual void draw();
    virtual void drawNoCoordUpdate();
    virtual void update();
    void getLocationUnitIsFacing(double tileXY[2]);
    void getLocationUnitDestinationIsFacing(int tileXY[2]);
    virtual void handleInput(InputMessage* message);
    void faceCoords(int x, int y);
    void getNewPath();
    void setScene(TileGridScene* gameScene);
    int getAttributeLevel(int attribute);
    void setAttributeLevel(int attribute, int newLevel);
    void changeAttributeLevel(int attribute, int attributeChange);
    int getHealth();
    int changeHealth(int change);
    int setHealth(int newHealth);
    int setFullHealth();
    void setZone(int newZone);
    int getZone();
    std::vector<Unit*> getBeingTargetedBy();
    void addUnitToBeingTargetedBy(Unit* newUnit);
    void removeUnitFromBeingTargetedBy(Unit* newUnit);
    void getCentreCoords(double coords[2]);
    int getDirectionOfCoordsRelativeToUnit(int x, int y);

    virtual std::string toSaveString(bool withHeaderAndFooter = true);
    static void resetUid();



protected:
    //attributes
    int health;
    std::unordered_map<int, UnitState*> unitStates;
    std::vector<unitSkillAttributeData> unitAttributes;
    int getPathAttempts;

    //methods
    void setUnitState(int newState);
    void setAttackingNearby(bool newValue);
    bool getAttackingNearby();

private:
    //attributes
    Location* targetLocation;
    Location* targetLocationBuffer;
    SDL_SpinLock targetLocationLock;
    SDL_SpinLock targetUnitLock;
    SDL_SpinLock targetedByUnitLock;
    Unit* targetUnit;
    Unit* targetUnitBuffer;
    int zone;
    std::vector<Unit*> beingTargetedBy;
    bool attackingNearbyUnit;
    SDL_SpinLock attackNearbyLock;

    //methods
    void init();
    void init(int zoneId, int unitType);
    void init(int zoneId, int unitType, TileGridScene* gameScene);
};

int getUniqueUnitId();

std::string unitSkillAttributeVectorSaveString(std::vector<unitSkillAttributeData> skillData);
void setUnitSkillAttributeVectorFromSaveString(std::vector<unitSkillAttributeData> * skillData, std::string saveString);

std::string unitSkillAttributeSaveString(unitSkillAttributeData skillData, int skillId);
unitSkillAttributeData getUnitSkillAttributeFromSaveString(std::string saveString);