#include "Unit.h"
#include"GameScene.h"
#include "RpgOverWorldScene.h"

int uniqueUnitId = 0;
const int MAX_PATH_ATTEMPTS = 5;

void Unit::getNewPath()
{
    if (!gettingPath)
    {
        getPathAttempts++;
        if (getPathAttempts > MAX_PATH_ATTEMPTS)
        {
            getPathAttempts = 0;
            clearTargetLocation();
            clearTargetUnit();
            return;
        }
        gettingPath = true;
        scene->addUnitToPathQueue(this);
    }
}

void Unit::setScene(TileGridScene* gameScene)
{
    scene = gameScene;
    Sprite::scene = gameScene;
}

int Unit::getAttributeLevel(int attribute)
{
    return unitAttributes[attribute].level;
}

void Unit::setAttributeLevel(int attribute, int newLevel)
{
    unitAttributes[attribute].level = newLevel;
}

void Unit::changeAttributeLevel(int attribute, int attributeChange)
{
    unitAttributes[attribute].level += attributeChange;
}

int Unit::getHealth()
{
    return health;
}

int Unit::changeHealth(int change)
{
    health += change;
    if (health > getAttributeLevel(UNIT_STAT_MAX_HEALTH))
    {
        health = getAttributeLevel(UNIT_STAT_MAX_HEALTH);
    }
    return health;
}

int Unit::setHealth(int newHealth)
{
    if (newHealth > getAttributeLevel(UNIT_STAT_MAX_HEALTH))
    {
        health = getAttributeLevel(UNIT_STAT_MAX_HEALTH);
        return health;
    }
   health = newHealth;
   return health;
}

int Unit::setFullHealth()
{
    health = getAttributeLevel(UNIT_STAT_MAX_HEALTH);
    return health;
}

void Unit::setZone(int newZone)
{
    if (newZone < 0)
    {
        int test = 32423;
    }
    zone = newZone;
}

int Unit::getZone()
{
    return zone;
}

std::vector<Unit*> Unit::getBeingTargetedBy()
{
    //SDL_AtomicLock(&targetedByUnitLock);
    return beingTargetedBy;
    //SDL_AtomicUnlock(&targetedByUnitLock);
}

void Unit::addUnitToBeingTargetedBy(Unit* newUnit)
{
    SDL_AtomicLock(&targetedByUnitLock);
    for (Unit* unit : beingTargetedBy) {
        if (unit == newUnit)
        {
            SDL_AtomicUnlock(&targetedByUnitLock);
            return;
        }
    }
    beingTargetedBy.push_back(newUnit);
    SDL_AtomicUnlock(&targetedByUnitLock);
}

void Unit::removeUnitFromBeingTargetedBy(Unit* newUnit)
{
    SDL_AtomicLock(&targetedByUnitLock);
    auto targetingUnitIterator = beingTargetedBy.begin();
    while (targetingUnitIterator != beingTargetedBy.end())
    {
        if ((*targetingUnitIterator) == newUnit) {
            targetingUnitIterator = beingTargetedBy.erase(targetingUnitIterator);
        }
        else {
            targetingUnitIterator++;
        }
    }
    SDL_AtomicUnlock(&targetedByUnitLock);
}

void Unit::getCentreCoords(double coords[2])
{
    scene->coordsFromTileIndex(tileLocation->x, tileLocation->y, coords);
    coords[0] += scene->tileWidth / 2;
    coords[1] += scene->tileHeight / 2;
}

Location* Unit::getTargetLocation()
{
    SDL_AtomicLock(&targetLocationLock);
    if (!targetLocation) {
        targetLocationBuffer->x = tileDestination->x;
        targetLocationBuffer->y = tileDestination->y;
    }
    else {
        targetLocationBuffer->x = targetLocation->x;
        targetLocationBuffer->y = targetLocation->y;
    }
    SDL_AtomicUnlock(&targetLocationLock);
    return targetLocationBuffer;
}

std::string Unit::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_UNIT) + "\n";
    }
    saveString += getAttributeString(getUniqueId(), UNIT_ID, id);
    if (beingTargetedBy.size() > 0)
    {
        std::vector<int> beingTargetedByIds;
        for (auto unit : beingTargetedBy) {
            beingTargetedByIds.push_back(unit->id);
        }
        saveString += getAttributeString(getUniqueId(), UNIT_BEING_TARGETED_BY, getIntVectorSaveString(beingTargetedByIds));
    }
    saveString += getAttributeString(getUniqueId(), UNIT_TYPE, type);
    saveString += getAttributeString(getUniqueId(), UNIT_TILE_LOCATION, getLocationSaveString(tileLocation));
    saveString += getAttributeString(getUniqueId(), UNIT_TILE_DESTINATION, getLocationSaveString(tileDestination));
    if (name != "")
    {
        saveString += getAttributeString(getUniqueId(), UNIT_NAME, name);
    }
    saveString += getAttributeString(getUniqueId(), UNIT_LEFT_TO_MOVE, leftToMove);
    saveString += getAttributeString(getUniqueId(), UNIT_IS_STATIC, isStatic);
    saveString += getAttributeString(getUniqueId(), UNIT_IS_PLAYER_CONTROLLED, isPlayerControlled);
    saveString += getAttributeString(getUniqueId(), UNIT_MOVING_UP, movingUp);
    saveString += getAttributeString(getUniqueId(), UNIT_MOVING_DOWN, movingDown);
    saveString += getAttributeString(getUniqueId(), UNIT_MOVING_LEFT, movingLeft);
    saveString += getAttributeString(getUniqueId(), UNIT_MOVING_RIGHT, movingRight);
    saveString += getAttributeString(getUniqueId(), UNIT_DIRECTION_FACING, directionFacing);
    saveString += getAttributeString(getUniqueId(), UNIT_CAN_GO_THROUGH_PORTAL, canGoThroughPortal);
    saveString += getAttributeString(getUniqueId(), UNIT_ZONE, zone);
    if (targetUnit != nullptr)
    {
        saveString += getAttributeString(getUniqueId(), UNIT_TARGET_UNIT, targetUnit->id);
    }
    else {
        saveString += getAttributeString(getUniqueId(), UNIT_TARGET_UNIT, -1);
    }
    if (targetLocation!= nullptr)
    {
        saveString += getAttributeString(getUniqueId(), UNIT_TARGET_LOCATION, getLocationSaveString(targetLocation));
    }
    saveString += getAttributeString(getUniqueId(), UNIT_PATH_DIRECTIONS, getIntVectorSaveString(pathDirections));
    saveString += getAttributeString(getUniqueId(), UNIT_CURRENT_STATE, currentState->id);
    saveString += getAttributeString(getUniqueId(), UNIT_MAX_HEALTH, getAttributeLevel(UNIT_STAT_MAX_HEALTH));
    saveString += getAttributeString(getUniqueId(), UNIT_HEALTH, health);
    saveString += getAttributeString(getUniqueId(), UNIT_SPEED, getAttributeLevel(UNIT_STAT_SPEED));
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_UNIT) + "\n";
    }
    return saveString;
}

void Unit::resetUid()
{
    uniqueUnitId = 0;
}

//constructors
Unit::Unit() : AnimatedSprite() {
    init();
}

Unit::Unit(SaveObject saveObject, TileGridScene* gameScene) : AnimatedSprite(gameScene)
{
    init();
    scene = gameScene;
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case UNIT_ID:
            id = stoi(saveObject.attributes[i].valueString);
            if (id > uniqueUnitId) {
                uniqueUnitId = id;
            }
            //else {
            //    id = getUniqueUnitId();
            //}
            break;
        case UNIT_BEING_TARGETED_BY:
            savedBeingTargetedByIds = getIntVectorFromSaveString(saveObject.attributes[i].valueString);
            break;
        case UNIT_TO_BE_DELETED:
            break;
        case UNIT_TYPE:
            type = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_TILE_LOCATION:
            tileLocation = getLocationFromSaveObject(saveObject.attributes[i].valueString);
            break;
        case UNIT_TILE_DESTINATION:
            tileDestination = getLocationFromSaveObject(saveObject.attributes[i].valueString);
            break;
        case UNIT_NAME:
            name = saveObject.attributes[i].valueString;
            break;
        case UNIT_LEFT_TO_MOVE:
            leftToMove = stod(saveObject.attributes[i].valueString);
            break;
        case UNIT_IS_STATIC:
            isStatic = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_IS_PLAYER_CONTROLLED:
            isPlayerControlled = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_MOVING_UP:
            movingUp = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_MOVING_DOWN:
            movingDown = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_MOVING_LEFT:
            movingLeft = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_MOVING_RIGHT:
            movingRight = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_DIRECTION_FACING:
            directionFacing = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_CAN_GO_THROUGH_PORTAL:
            canGoThroughPortal = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_ZONE:
            zone = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_TARGET_UNIT:
            savedTargetUnitId = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_TARGET_LOCATION:
            setTargetLocation(getLocationFromSaveObject(saveObject.attributes[i].valueString));
            break;
        case UNIT_PATH_DIRECTIONS:
            pathDirections = getIntVectorFromSaveString(saveObject.attributes[i].valueString);
            break;
        case UNIT_CURRENT_STATE:
            savedCurrentStateId = stoi(saveObject.attributes[i].valueString);
            setUnitState(savedCurrentStateId);
            break;
        case UNIT_MAX_HEALTH:
            setAttributeLevel(UNIT_STAT_MAX_HEALTH, stoi(saveObject.attributes[i].valueString));
            //maxHealth = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_HEALTH:
            health = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_SPEED:
            setAttributeLevel(UNIT_STAT_SPEED, stoi(saveObject.attributes[i].valueString));
            //speed = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
    resize(scene->tileWidth * 3, scene->tileHeight * 3);
}

Unit::Unit(int zoneId, int unitType) : AnimatedSprite() {
    init(zoneId, unitType);
}

Unit::Unit(int zoneId, int unitType, TileGridScene* gameScene) : AnimatedSprite(gameScene) {
    init(zoneId, unitType, gameScene);
}

Unit::Unit(int zoneId, int unitType, TileGridScene* gameScene, int startX, int startY) : AnimatedSprite(gameScene) {
    init(zoneId, unitType, gameScene);
    setStartLocation(startX, startY);
    tileLocationBuffer->x = startX;
    tileLocationBuffer->y = startY;
    tileDestinationBuffer->x = startX;
    tileDestinationBuffer->y = startY;
}

void Unit::init() {
    attackNearbyLock = 0;
    targetedByUnitLock = 0;
    targetUnitLock = 0;
    targetLocationLock = 0;
    deleteLock = 0;
    gettingPath = false;
    type = -1;
    name = "";
    tileLocation = new Location{ 0, 0 };
    tileDestination = new Location{ 0, 0 };
    tileLocationBuffer = new Location{ 0, 0 };
    tileDestinationBuffer = new Location{ 0, 0 };
    targetLocationBuffer = new Location{ 0, 0 };
    //maxHealth = 1;
    //speed = 1;
    leftToMove = 0;
    leftToMoveBuffer = 0;
    isStatic = false;
    isPlayerControlled = false;
    canGoThroughPortal = true;
    directionFacing = DOWN;
    movingUp = movingDown = movingRight = movingLeft = false;
    setTileLocation(0, 0);
    unitStates.clear();
    //setUnitState(UNIT_IDLE);
    zone = 0;
    targetUnit = nullptr;
    targetUnitBuffer = nullptr;
    getPathTick = 0;
    adjustPathTick = 0;
    getNewPathFailTick = 0;
    processPathFailTick = 0;
    currentState = nullptr;
    //special attributes for loading saved units
    savedSceneId = -1;
    savedTargetUnitId = -1;
    //pathfinding vars
    getPathRate = DEFAULT_GET_PATH_RATE;
    adjustPathRate = DEFAULT_ADJUST_PATH_RATE;
    health = 1;
    unitAttributes.resize(NUM_RPG_ATTRIBUTES, { 1, 1, 0, 100, 0 });
    getPathAttempts = 0;
    //unitAttributes[UNIT_STAT_SPEED] = {1, 0, 100, 0};
    //unitAttributes[UNIT_STAT_MAX_HEALTH] = {1, 0, 100, 0};
}

void Unit::init(int zoneId, int unitType) {
    init();
    type = unitType;
    setZone(zoneId);
}

void Unit::init(int zoneId, int unitType, TileGridScene* gameScene) {
    init(zoneId, unitType);
    scene = gameScene;
    resize(scene->tileWidth * 3, scene->tileHeight * 3);
}


void Unit::setAttackingNearby(bool newValue)
{
    SDL_AtomicLock(&attackNearbyLock);
    attackingNearbyUnit = newValue;
    SDL_AtomicUnlock(&attackNearbyLock);
}

bool Unit::getAttackingNearby()
{
    SDL_AtomicLock(&attackNearbyLock);
    bool returnValue = attackingNearbyUnit;
    SDL_AtomicUnlock(&attackNearbyLock);
    return returnValue;
}

bool Unit::isAlive()
{
    return health > 0 && active;
}


//destructor
Unit::~Unit() {
    name = "";
    //health = 0;
    leftToMove = 0;
}

void Unit::startMovement(int direction) {
    if (leftToMove > 0)
    {
        return;
    }
    directionFacing = direction;

    switch (direction)
    {
    case UP:
        if (scene->isTilePassable(zone, tileLocation->x, tileLocation->y - 1))
        {
            tileDestination->y = tileLocation->y - 1;
            leftToMove = 1;
        }
        else 
        {
            RpgUnit* unitAtLocation = (RpgUnit*)scene->getZone(zone)->getUnitAtLocation(tileLocation->x, tileLocation->y - 1);
            if (unitAtLocation && unitAtLocation->team == PLAYER_TEAM && unitAtLocation != ((RpgOverWorldScene*)scene)->player && unitAtLocation->currentState->id == UNIT_IDLE && scene->getZone(zone)->isTilePassableIgnoreUnit(scene, tileLocation->x, tileLocation->y - 1, unitAtLocation))
            {
                unitAtLocation->tileDestination->x = tileLocation->x;
                unitAtLocation->tileDestination->y = tileLocation->y;
                unitAtLocation->leftToMove = 1;
                unitAtLocation->movingUp = false;
                unitAtLocation->movingDown = true;
                unitAtLocation->movingRight = false;
                unitAtLocation->movingLeft = false;
                unitAtLocation->setUnitState(UNIT_MOVING);
                unitAtLocation->handleInput(&InputMessage(STOP_MOVE_DOWN));
                unitAtLocation->directionFacing = DOWN;
                unitAtLocation->setTargetLocation(unitAtLocation->tileLocation);
                tileDestination->y = tileLocation->y - 1;
                leftToMove = 1;
            }
        }
        break;
    case DOWN:
        if (scene->isTilePassable(zone, tileLocation->x, tileLocation->y + 1))
        {
            tileDestination->y = tileLocation->y + 1;
            leftToMove = 1;
        }
        else
        {
            RpgUnit* unitAtLocation = (RpgUnit*)scene->getZone(zone)->getUnitAtLocation(tileLocation->x, tileLocation->y + 1);
            if (unitAtLocation && unitAtLocation->team == PLAYER_TEAM && unitAtLocation != ((RpgOverWorldScene*)scene)->player && unitAtLocation->currentState->id == UNIT_IDLE && scene->getZone(zone)->isTilePassableIgnoreUnit(scene, tileLocation->x, tileLocation->y + 1, unitAtLocation))
            {
                unitAtLocation->tileDestination->x = tileLocation->x;
                unitAtLocation->tileDestination->y = tileLocation->y;
                unitAtLocation->leftToMove = 1;
                unitAtLocation->movingUp = true;
                unitAtLocation->movingDown = false;;
                unitAtLocation->movingRight = false;
                unitAtLocation->movingLeft = false;
                unitAtLocation->setUnitState(UNIT_MOVING);
                unitAtLocation->handleInput(&InputMessage(STOP_MOVE_UP));
                unitAtLocation->directionFacing = UP;
                unitAtLocation->setTargetLocation(unitAtLocation->tileLocation);
                tileDestination->y = tileLocation->y + 1;
                leftToMove = 1;
            }
        }
        break;
    case RIGHT:
        if (scene->isTilePassable(zone, tileLocation->x + 1, tileLocation->y))
        {
            tileDestination->x = tileLocation->x + 1;
            leftToMove = 1;
        }
        else
        {
            RpgUnit* unitAtLocation = (RpgUnit*)scene->getZone(zone)->getUnitAtLocation(tileLocation->x + 1, tileLocation->y);
            if (unitAtLocation && unitAtLocation->team == PLAYER_TEAM && unitAtLocation != ((RpgOverWorldScene*)scene)->player && unitAtLocation->currentState->id == UNIT_IDLE && scene->getZone(zone)->isTilePassableIgnoreUnit(scene, tileLocation->x + 1, tileLocation->y, unitAtLocation))
            {
                unitAtLocation->tileDestination->x = tileLocation->x;
                unitAtLocation->tileDestination->y = tileLocation->y;
                unitAtLocation->leftToMove = 1;
                unitAtLocation->movingUp = false;
                unitAtLocation->movingDown = false;
                unitAtLocation->movingRight = false;
                unitAtLocation->movingLeft = true;
                unitAtLocation->setUnitState(UNIT_MOVING);
                unitAtLocation->handleInput(&InputMessage(STOP_MOVE_LEFT));
                unitAtLocation->directionFacing = LEFT;
                unitAtLocation->setTargetLocation(unitAtLocation->tileLocation);
                tileDestination->x = tileLocation->x + 1;
                leftToMove = 1;
            }
        }
        break;
    case LEFT:
        if (scene->isTilePassable(zone, tileLocation->x - 1, tileLocation->y))
        {
            tileDestination->x = tileLocation->x - 1;
            leftToMove = 1;
        }
        else
        {
            RpgUnit* unitAtLocation = (RpgUnit*)scene->getZone(zone)->getUnitAtLocation(tileLocation->x - 1, tileLocation->y);
            if (unitAtLocation && unitAtLocation->team == PLAYER_TEAM && unitAtLocation != ((RpgOverWorldScene*)scene)->player && unitAtLocation->currentState->id == UNIT_IDLE && scene->getZone(zone)->isTilePassableIgnoreUnit(scene, tileLocation->x - 1, tileLocation->y, unitAtLocation))
            {
                unitAtLocation->tileDestination->x = tileLocation->x;
                unitAtLocation->tileDestination->y = tileLocation->y;
                unitAtLocation->leftToMove = 1;
                unitAtLocation->movingUp = false;
                unitAtLocation->movingDown = false;
                unitAtLocation->movingRight = true;
                unitAtLocation->movingLeft = false;
                unitAtLocation->setUnitState(UNIT_MOVING);
                unitAtLocation->handleInput(&InputMessage(STOP_MOVE_RIGHT));
                unitAtLocation->directionFacing = RIGHT;
                unitAtLocation->setTargetLocation(unitAtLocation->tileLocation);
                tileDestination->x = tileLocation->x - 1;
                leftToMove = 1;
            }
        }
        break;
    default:
        break;
    }
    scene->getZone(zone)->addUnitToDestinationLocation(this);
}

void Unit::update() {
    AnimatedSprite::update();
    setUnitState(currentState->update());
}

bool Unit::updateMovement() {
    //return true if unit still moving, else, return false
    if (leftToMove > 0) {
        leftToMove = leftToMove - (double)getAttributeLevel(UNIT_STAT_SPEED) / 100;
    }
    if (leftToMove <= 0.10 && leftToMove > 0)
    {
        int eer = 234;
    }
    if (leftToMove <= 0) {
        if (tileDestination->x != tileLocation->x || tileDestination->y != tileLocation->y) {
            moveTo(tileDestination->x, tileDestination->y);
        }
        double leftToMoveRemainder = leftToMove;
        leftToMove = 0;
        if (movingUp && !movingDown && (currentState == unitStates[UNIT_MOVING] || currentState == unitStates[UNIT_IDLE])) {
            startMovement(UP);
            if (leftToMove > 0)
            {
                leftToMove += leftToMoveRemainder;
            }
            return true;
        }
        if (movingDown && !movingUp && (currentState == unitStates[UNIT_MOVING] || currentState == unitStates[UNIT_IDLE])) {
            startMovement(DOWN);
            if (leftToMove > 0)
            {
                leftToMove += leftToMoveRemainder;
            }
            return true;
        }
        if (movingRight && !movingLeft && (currentState == unitStates[UNIT_MOVING] || currentState == unitStates[UNIT_IDLE])) {
            startMovement(RIGHT);
            if (leftToMove > 0)
            {
                leftToMove += leftToMoveRemainder;
            }
            return true;
        }
        if (movingLeft && !movingRight && (currentState == unitStates[UNIT_MOVING] || currentState == unitStates[UNIT_IDLE])) {
            startMovement(LEFT);
            if (leftToMove > 0)
            {
                leftToMove += leftToMoveRemainder;
            }
            return true;
        }

        leftToMove = 0;
        return false;
    }
    return true;
}

bool Unit::processPath()
{
    if (!getAttackingNearby() && targetUnit && (std::abs(targetUnit->tileDestination->x - tileDestination->x) <= 1 && std::abs(targetUnit->tileDestination->y - tileDestination->y) <= 1))
    {
        return false;
    }
    int newDirection = pathDirections.back();
    //pathDirections.pop_back();
    switch (newDirection)
    {
    case UP:
        //movingUp = true;
        if (scene->getZone(zone)->isTilePassable(scene, tileLocation->x, tileLocation->y - 1))
        {
            pathDirections.pop_back();
            startMovement(UP);
            if (adjustPathRate == adjustPathTick)
            {
                getNewPath();
                adjustPathTick = 0;
            }
            adjustPathTick++;
            return true;
        }
        else {
            processPathFailTick++;
            if (scene->processPathFailLimit <= processPathFailTick)
            {
                processPathFailTick = 0;
                getNewPath();
            }
        }
        break;
    case DOWN:
        //movingDown = true;
        if (scene->getZone(zone)->isTilePassable(scene, tileLocation->x, tileLocation->y + 1))
        {
            pathDirections.pop_back();
            startMovement(DOWN);
            if (adjustPathRate == adjustPathTick)
            {
                getNewPath();
                adjustPathTick = 0;
            }
            adjustPathTick++;
            return true;
        }
        else {
            processPathFailTick++;
            if (scene->processPathFailLimit <= processPathFailTick)
            {
                processPathFailTick = 0;
                getNewPath();
            }
        }
        break;
    case LEFT:
        //movingLeft = true;
        if (scene->getZone(zone)->isTilePassable(scene, tileLocation->x - 1, tileLocation->y))
        {
            pathDirections.pop_back();
            startMovement(LEFT);
            if (adjustPathRate == adjustPathTick)
            {
                getNewPath();
                adjustPathTick = 0;
            }
            adjustPathTick++;
            return true;
        }
        else {
            processPathFailTick++;
            if (scene->processPathFailLimit <= processPathFailTick)
            {
                processPathFailTick = 0;
                getNewPath();
            }
        }
        break;
    case RIGHT:
        //movingRight = true;
        if (scene->getZone(zone)->isTilePassable(scene, tileLocation->x + 1, tileLocation->y))
        {
            pathDirections.pop_back();
            startMovement(RIGHT);
            if (adjustPathRate == adjustPathTick)
            {
                getNewPath();
                adjustPathTick = 0;
            }
            adjustPathTick++;
            return true;
        }
        else {
            processPathFailTick++;
            if (scene->processPathFailLimit <= processPathFailTick)
            {
                processPathFailTick = 0;
                getNewPath();
            }
        }
        break;
    default:
        break;
    }
    return false;
}

void Unit::setTargetLocation(Location* newTargetLocation)
{
    SDL_AtomicLock(&targetLocationLock);
    if (targetLocation == nullptr)
    {
        targetLocation = new Location();
    }
    targetLocation->x = newTargetLocation->x;
    targetLocation->y = newTargetLocation->y;
    getPathAttempts = 0;
    getNewPath();
    SDL_AtomicUnlock(&targetLocationLock);
}

void Unit::setTargetLocation(int newX, int newY)
{
    SDL_AtomicLock(&targetLocationLock);
    if (targetLocation == nullptr)
    {
        targetLocation = new Location();
    }
    targetLocation->x = newX;
    targetLocation->y = newY;
    getPathAttempts = 0;
    getNewPath();
    SDL_AtomicUnlock(&targetLocationLock);
}

void Unit::setTargetUnit(Unit* newTargetUnit)
{
    SDL_AtomicLock(&targetUnitLock);

    if (targetUnit)
    {
        targetUnit->removeUnitFromBeingTargetedBy(this);
    }

    targetUnit = newTargetUnit;
    targetUnit->addUnitToBeingTargetedBy(this);
    //targetUnit->beingTargetedBy.push_back(this);
    getPathAttempts = 0;
    getNewPath();
    SDL_AtomicUnlock(&targetUnitLock);
}

void Unit::clearTargetUnit()
{
    SDL_AtomicLock(&targetUnitLock);
    if (targetUnit)
    {
        targetUnit->removeUnitFromBeingTargetedBy(this);
    }
    targetUnit = nullptr;
    getPathAttempts = 0;
    //getNewPath();
    SDL_AtomicUnlock(&targetUnitLock);
}

Unit* Unit::getTargetUnit()
{
    SDL_AtomicLock(&targetUnitLock);
    targetUnitBuffer = targetUnit;
    SDL_AtomicUnlock(&targetUnitLock);
    return targetUnitBuffer;
}

void Unit::setTileLocation(int x, int y) {
    tileLocation->x = x;
    tileLocation->y = y;
    tileDestination->x = x;
    tileDestination->y = y;
    //tileLocationBuffer->x = x;
    //tileLocationBuffer->y = y;
    //tileDestinationBuffer->x = x;
    //tileDestinationBuffer->y = y;
}

void Unit::clearTargetLocation()
{
    SDL_AtomicLock(&targetLocationLock);
    delete targetLocation;
    targetLocation = nullptr;
    scene->removeUnitFromPathQueue(this);
    SDL_AtomicUnlock(&targetLocationLock);
}

void Unit::moveTo(int x, int y)
{
    scene->getZone(zone)->removeUnitFromLocation(this, tileLocation->x, tileLocation->y);
    scene->getZone(zone)->removeUnitFromLocation(this, tileDestination->x, tileDestination->y);
    setTileLocation(x, y);
    scene->getZone(zone)->addUnitToLocation(this, tileDestination->x, tileDestination->y);
    scene->getZone(zone)->unitEntersTile(this, tileLocation->x, tileLocation->y);
    if (targetLocation != nullptr && x == targetLocation->x && y == targetLocation->y)
    {
        pathDirections.clear();
        clearTargetLocation();
    }
}

void Unit::portalTo(int zoneId, int x, int y)
{
    //remove unit from current zone
    scene->getZone(zone)->removeUnitFromZone(this);
    //add unit to new zone
    scene->getZone(zoneId)->addUnitToLocation(this, x, y);
    //if its a command squad unit disable further portaling
    for (size_t i = 1; i < MAX_NUM_SQUAD_UNITS; i++)
    {
        if (((RpgOverWorldScene*)scene)->getSquadUnits()[i] == this) {
            ((RpgOverWorldScene*)scene)->getSquadUnits()[i]->canGoThroughPortal = false;
        }
    }
    //clear old target location
    clearTargetLocation();
}

void Unit::updateCoords() {
    double coords[2];
    double destCoords[2];
    scene->coordsFromTileIndex(tileLocationBuffer->x, tileLocationBuffer->y, coords);
    scene->coordsFromTileIndex(tileDestinationBuffer->x, tileDestinationBuffer->y, destCoords);
    xpos = coords[0] + (destCoords[0] - coords[0]) * (1 - leftToMoveBuffer) - scene->tileWidth;
    ypos = coords[1] + (destCoords[1] - coords[1]) * (1 - leftToMoveBuffer) - scene->tileHeight;
}

void Unit::setStartLocation(int x, int y) {
    tileLocation->x = x;
    tileLocation->y = y;
    tileDestination->x = x;
    tileDestination->y = y;
    double screenCoords[2];
    scene->coordsFromTileIndex(x, y, screenCoords);
    xpos = screenCoords[0];
    ypos = screenCoords[1];
}

void Unit::draw()
{
    updateCoords();
    AnimatedSprite::draw();
}

void Unit::drawNoCoordUpdate()
{
    AnimatedSprite::draw();
}

void Unit::getLocationUnitIsFacing(double tileXY[2]) {
    switch (directionFacing)
    {
    case UP_LEFT:
        tileXY[0] = tileLocation->x -1;
        tileXY[1] = tileLocation->y - 1;
        break;
    case UP:
        tileXY[0] = tileLocation->x;
        tileXY[1] = tileLocation->y - 1;
        break;
    case UP_RIGHT:
        tileXY[0] = tileLocation->x + 1;
        tileXY[1] = tileLocation->y - 1;
        break;
    case RIGHT:
        tileXY[0] = tileLocation->x + 1;
        tileXY[1] = tileLocation->y;
        break;
    case DOWN_RIGHT:
        tileXY[0] = tileLocation->x + 1;
        tileXY[1] = tileLocation->y + 1;
        break;
    case DOWN:
        tileXY[0] = tileLocation->x;
        tileXY[1] = tileLocation->y + 1;
        break;
    case DOWN_LEFT:
        tileXY[0] = tileLocation->x - 1;
        tileXY[1] = tileLocation->y + 1;
        break;
    case LEFT:
        tileXY[0] = tileLocation->x - 1;
        tileXY[1] = tileLocation->y;
        break;
    default:
        tileXY[0] = tileLocation->x;
        tileXY[1] = tileLocation->y;
        break;
    }
    tileXY;
}

void Unit::getLocationUnitDestinationIsFacing(int tileXY[2])
{
    switch (directionFacing)
    {
    case UP_LEFT:
        tileXY[0] = tileDestination->x - 1;
        tileXY[1] = tileDestination->y - 1;
        break;
    case UP:
        tileXY[0] = tileDestination->x;
        tileXY[1] = tileDestination->y - 1;
        break;
    case UP_RIGHT:
        tileXY[0] = tileDestination->x + 1;
        tileXY[1] = tileDestination->y - 1;
        break;
    case RIGHT:
        tileXY[0] = tileDestination->x + 1;
        tileXY[1] = tileDestination->y;
        break;
    case DOWN_RIGHT:
        tileXY[0] = tileDestination->x + 1;
        tileXY[1] = tileDestination->y + 1;
        break;
    case DOWN:
        tileXY[0] = tileDestination->x;
        tileXY[1] = tileDestination->y + 1;
        break;
    case DOWN_LEFT:
        tileXY[0] = tileDestination->x - 1;
        tileXY[1] = tileDestination->y + 1;
        break;
    case LEFT:
        tileXY[0] = tileDestination->x - 1;
        tileXY[1] = tileDestination->y;
        break;
    default:
        tileXY[0] = tileDestination->x;
        tileXY[1] = tileDestination->y;
        break;
    }
    tileXY;
}

void Unit::handleInput(InputMessage* message) {
    setUnitState(currentState->handleInput(message));
}

void Unit::setUnitState(int newState) {
    //if (unitStates.find(newState) != unitStates.end())
    //{
    currentState = unitStates[newState];
    //}
}

void Unit::faceCoords(int x, int y) {
    if (x < xpos + scene->tileWidth && y < ypos + scene->tileHeight)
    {
        directionFacing = UP_LEFT;
    }
    else if (x >= xpos + scene->tileWidth && x < xpos + scene->tileWidth + scene->tileWidth && y < ypos + scene->tileHeight) {
        directionFacing = UP;
    }
    else if (x >= xpos + scene->tileWidth + scene->tileWidth && y < ypos + scene->tileHeight) {
        directionFacing = UP_RIGHT;
    }
    else if (x >= xpos + scene->tileWidth + scene->tileWidth && y >= ypos + scene->tileHeight && y < ypos + scene->tileHeight + scene->tileHeight) {
        directionFacing = RIGHT;
    }
    else if (x >= xpos + scene->tileWidth + scene->tileWidth && y >= ypos + scene->tileHeight + scene->tileHeight) {
        directionFacing = DOWN_RIGHT;
    }
    else if (x >= xpos + scene->tileWidth && x <= xpos + scene->tileWidth + scene->tileWidth && y >= ypos + scene->tileHeight + scene->tileHeight) {
        directionFacing = DOWN;
    }
    else if (x < xpos + scene->tileWidth && y >= ypos + scene->tileHeight + scene->tileHeight) {
        directionFacing = DOWN_LEFT;
    }
    else if (x < xpos + scene->tileWidth && y >= ypos + scene->tileHeight && y <= ypos + scene->tileHeight + scene->tileHeight) {
        directionFacing = LEFT;
    }
}
//
////functions
//int getPathThread(void* movingUnit) {
//    srand(time(NULL));
//    SDL_SetThreadPriority(SDL_THREAD_PRIORITY_LOW);
//    try {
//        Unit* unit = static_cast <Unit*> (movingUnit);
//        Unit* targetUnit = static_cast <Unit*> (movingUnit)->targetUnit;
//        TileGridScene* scene = static_cast <Unit*> (movingUnit)->scene;
//        Location* targetLocation = static_cast <Unit*> (movingUnit)->targetLocation;
//        std::vector<int> tempDirections;
//
//        if (targetUnit != nullptr)
//        {
//            tempDirections = unit->scene->zones[unit->zone]->getPathDirectionsToUnit(scene, unit->tileDestination, targetUnit, unit);
//            if (tempDirections.size() > 0)
//            {
//                unit->pathDirections = tempDirections;
//                return 0;
//            }
//            /*if (unit->followingDirectPath)
//            {
//                return 0;
//            }*/
//            unit->getNewPathFailTick++;
//            if (unit->getNewPathFailTick >= unit->getNewPathFailLimit)
//            {
//                unit->getNewPathFailTick = 0;
//                unit->pathDirections = scene->zones[unit->zone]->getPathDirectionsIgnoreAllunits(scene, unit->tileDestination, targetUnit->tileDestination);
//            }
//            return 0;
//        }
//        else if (targetLocation != nullptr) {
//            tempDirections = scene->zones[unit->zone]->getPathDirections(scene, unit->tileDestination, targetLocation);
//            if (tempDirections.size() > 0)
//            {
//                unit->pathDirections = tempDirections;
//                return 0;
//            }
//            unit->getNewPathFailTick++;
//            if (unit->getNewPathFailTick >= unit->getNewPathFailLimit)
//            {
//                unit->getNewPathFailTick = 0;
//                unit->pathDirections = scene->zones[unit->zone]->getPathDirectionsIgnoreAllunits(scene, unit->tileDestination, targetLocation);
//            }
//            return 0;
//        }
//    }
//    catch (...) {
//        return 1;
//    }
//    return 0;
//}

int getUniqueUnitId()
{
    uniqueUnitId++;
    return uniqueUnitId;
}

std::string unitSkillAttributeVectorSaveString(std::vector<unitSkillAttributeData> skillData)
{
    std::string returnString;
    returnString += std::to_string(skillData.size()) + "\n";
    for (int i = 0; i < skillData.size(); i++)
    {
        returnString += unitSkillAttributeSaveString(skillData[i], i) + "\n";
    }
    return returnString;
}

void setUnitSkillAttributeVectorFromSaveString(std::vector<unitSkillAttributeData>* skillData, std::string saveString)
{
    std::vector<SaveObject> savedItems = getSaveObjectVectorFromSaveString2(saveString);

    for (size_t i = 0; i < savedItems.size(); i++)
    {
        unitSkillAttributeData savedSkill = getUnitSkillAttributeFromSaveString(savedItems[i].rawString);
        (*skillData)[savedSkill.id].level = savedSkill.level;
        (*skillData)[savedSkill.id].baseLevel = savedSkill.baseLevel;
        (*skillData)[savedSkill.id].experience = savedSkill.experience;
        (*skillData)[savedSkill.id].experienceNextLevel = savedSkill.experienceNextLevel;
        (*skillData)[savedSkill.id].experienceLastLevel = savedSkill.experienceLastLevel;
    }

}

std::string unitSkillAttributeSaveString(unitSkillAttributeData skillData, int skillId)
{
    std::string saveString = "";
    int uniqueObjectId = getUniqueId();
    saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_UNIT_SKILL_ATTR) + "\n";
    saveString += getAttributeString(getUniqueId(), SKILL_ATTR_ID, skillId);
    saveString += getAttributeString(getUniqueId(), SKILL_ATTR_LEVEL, skillData.level);
    saveString += getAttributeString(getUniqueId(), SKILL_ATTR_BASE_LEVEL, skillData.baseLevel);
    saveString += getAttributeString(getUniqueId(), SKILL_ATTR_EXP, skillData.experience);
    saveString += getAttributeString(getUniqueId(), SKILL_ATTR_EXP_NXT_LVL, skillData.experienceNextLevel);
    saveString += getAttributeString(getUniqueId(), SKILL_ATTR_EXP_LAST_LVL, skillData.experienceLastLevel);
    saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_UNIT_SKILL_ATTR) + "\n";
    return saveString;
}

unitSkillAttributeData getUnitSkillAttributeFromSaveString(std::string saveString)
{
    SaveObject savedSkill = SaveObject(saveString);
    unitSkillAttributeData returnSkill = unitSkillAttributeData();
    for (int i = 0; i < savedSkill.attributes.size(); i++)
    {
        switch (savedSkill.attributes[i].attributeType) {
        case SKILL_ATTR_LEVEL:
            returnSkill.level = stoi(savedSkill.attributes[i].valueString);
            break;
        case SKILL_ATTR_BASE_LEVEL:
            returnSkill.baseLevel = stoi(savedSkill.attributes[i].valueString);
            break;
        case SKILL_ATTR_EXP:
            returnSkill.experience = stoi(savedSkill.attributes[i].valueString);
            break;
        case SKILL_ATTR_EXP_NXT_LVL:
            returnSkill.experienceNextLevel = stoi(savedSkill.attributes[i].valueString);
            break;
        case SKILL_ATTR_EXP_LAST_LVL:
            returnSkill.experienceLastLevel = stoi(savedSkill.attributes[i].valueString);
            break;
        case SKILL_ATTR_ID:
            returnSkill.id = stoi(savedSkill.attributes[i].valueString);
            break;
        default:
            break;
        }
    }

    return returnSkill;
}
