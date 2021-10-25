#include "Unit.h"
#include"GameScene.h"

int uniqueUnitId = 0;

void Unit::getNewPath()
{
    //SDL_CreateThread(getPathThread, "getPathThread", (void*)this);
    scene->unitsNeedingPath.push_back(this);
}
void Unit::setScene(TileGridScene* gameScene)
{
    scene = gameScene;
    Sprite::scene = gameScene;
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
    saveString += getAttributeString(getUniqueId(), UNIT_TO_BE_DELETED, toBeDeleted);
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
    saveString += getAttributeString(getUniqueId(), UNIT_MAX_HEALTH, maxHealth);
    saveString += getAttributeString(getUniqueId(), UNIT_HEALTH, health);
    saveString += getAttributeString(getUniqueId(), UNIT_SPEED, speed);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_UNIT) + "\n";
    }
    return saveString;
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
            else {
                id = getUniqueUnitId();
            }
            break;
        case UNIT_BEING_TARGETED_BY:
            savedBeingTargetedByIds = getIntVectorFromSaveString(saveObject.attributes[i].valueString);
            break;
        case UNIT_TO_BE_DELETED:
            toBeDeleted = stoi(saveObject.attributes[i].valueString);
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
        case UNIT_TARGET_UNIT:
            savedTargetUnitId = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_TARGET_LOCATION:
            targetLocation = getLocationFromSaveObject(saveObject.attributes[i].valueString);
            break;
        case UNIT_PATH_DIRECTIONS:
            pathDirections = getIntVectorFromSaveString(saveObject.attributes[i].valueString);
            break;
        case UNIT_CURRENT_STATE:
            savedCurrentStateId = stoi(saveObject.attributes[i].valueString);
            setUnitState(savedCurrentStateId);
            break;
        case UNIT_MAX_HEALTH:
            maxHealth = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_HEALTH:
            health = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_SPEED:
            speed = stoi(saveObject.attributes[i].valueString);
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
}

void Unit::init() {
    type = -1;
    name = "";
    tileLocation = new Location{ 0, 0 };
    tileDestination = new Location{ 0, 0 };
    maxHealth = 1;
    health = 1;
    speed = 1;
    leftToMove = 0;
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
    toBeDeleted = false;
    getPathTick = 0;
    getPathRate = 30;
    adjustPathTick = 0;
    adjustPathRate = 3;
    getNewPathFailLimit = 2;
    getNewPathFailTick = 0;
    processPathFailLimit = 20;
    processPathFailTick = 0;
    currentState = nullptr;
    //special attributes for loading saved units
    savedSceneId = -1;
    savedTargetUnitId = -1;
    
}

void Unit::init(int zoneId, int unitType) {
    init();
    type = unitType;
    zone = zoneId;
}

void Unit::init(int zoneId, int unitType, TileGridScene* gameScene) {
    init(zoneId, unitType);
    scene = gameScene;
    resize(scene->tileWidth * 3, scene->tileHeight * 3);
}

bool Unit::isAlive()
{
    return health > 0 && active;
}


//destructor
Unit::~Unit() {
    name = "";
    health = 0;
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
        break;
    case DOWN:
        if (scene->isTilePassable(zone, tileLocation->x, tileLocation->y + 1))
        {
            tileDestination->y = tileLocation->y + 1;
            leftToMove = 1;
        }            
        break;
    case RIGHT:
        if (scene->isTilePassable(zone, tileLocation->x + 1, tileLocation->y))
        {
            tileDestination->x = tileLocation->x + 1;
            leftToMove = 1;
        }
        break;
    case LEFT:
        if (scene->isTilePassable(zone, tileLocation->x - 1, tileLocation->y))
        {
            tileDestination->x = tileLocation->x - 1;
            leftToMove = 1;
        }
        break;
    default:
        break;
    }
    //scene->zones[zone]->removeUnitFromLocation(this, tileLocation->x, tileLocation->y); //causes graphic glitch
    scene->zones[zone]->unitMap[tileDestination->x][tileDestination->y].push_back(this);
}

void Unit::update() {
    AnimatedSprite::update();
    setUnitState(currentState->update());
}

bool Unit::updateMovement() {
    //return true if unit still moving, else, return false
    if (leftToMove > 0) {
        leftToMove = leftToMove - (double)speed / 100;
    }
    if (leftToMove <= 0) {
        leftToMove = 0;
        if (tileDestination->x != tileLocation->x || tileDestination->y != tileLocation->y) {
            moveTo(tileDestination->x, tileDestination->y);
        }
        
        if (movingUp && !movingDown && (currentState == unitStates[UNIT_MOVING] || currentState == unitStates[UNIT_IDLE])) {
            startMovement(UP);
            return true;
        }
        if (movingDown && !movingUp && (currentState == unitStates[UNIT_MOVING] || currentState == unitStates[UNIT_IDLE])) {
            startMovement(DOWN);
            return true;
        }
        if (movingRight && !movingLeft && (currentState == unitStates[UNIT_MOVING] || currentState == unitStates[UNIT_IDLE])) {
            startMovement(RIGHT);
            return true;
        }
        if (movingLeft && !movingRight && (currentState == unitStates[UNIT_MOVING] || currentState == unitStates[UNIT_IDLE])) {
            startMovement(LEFT);
            return true;
        }
        return false;
    }
    return true;
}

bool Unit::processPath()
{
    int newDirection = pathDirections.back();
    //pathDirections.pop_back();
    switch (newDirection)
    {
    case UP:
        //movingUp = true;
        if (scene->zones[zone]->isTilePassable(scene, tileLocation->x, tileLocation->y - 1))
        {
            pathDirections.pop_back();
            startMovement(UP);
            if (adjustPathRate == adjustPathTick)
            {
                getNewPath();
                adjustPathTick = 0;
                return true;
            }
            adjustPathTick++;
        }
        else {
            processPathFailTick++;
            if (processPathFailLimit <= processPathFailTick)
            {
                processPathFailTick = 0;
                getNewPath();
            }
        }
        break;
    case DOWN:
        //movingDown = true;
        if (scene->zones[zone]->isTilePassable(scene, tileLocation->x, tileLocation->y + 1))
        {
            pathDirections.pop_back();
            startMovement(DOWN);
            if (adjustPathRate == adjustPathTick)
            {
                getNewPath();
                adjustPathTick = 0;
                return true;
            }
            adjustPathTick++;
        }
        else {
            processPathFailTick++;
            if (processPathFailLimit <= processPathFailTick)
            {
                processPathFailTick = 0;
                getNewPath();
            }
        }
        break;
    case LEFT:
        //movingLeft = true;
        if (scene->zones[zone]->isTilePassable(scene, tileLocation->x - 1, tileLocation->y))
        {
            pathDirections.pop_back();
            startMovement(LEFT);
            if (adjustPathRate == adjustPathTick)
            {
                getNewPath();
                adjustPathTick = 0;
                return true;
            }
            adjustPathTick++;
        }
        else {
            processPathFailTick++;
            if (processPathFailLimit <= processPathFailTick)
            {
                processPathFailTick = 0;
                getNewPath();
            }
        }
        break;
    case RIGHT:
        //movingRight = true;
        if (scene->zones[zone]->isTilePassable(scene, tileLocation->x + 1, tileLocation->y))
        {
            pathDirections.pop_back();
            startMovement(RIGHT);
            if (adjustPathRate == adjustPathTick)
            {
                getNewPath();
                adjustPathTick = 0;
                return true;
            }
            adjustPathTick++;
        }
        else {
            processPathFailTick++;
            if (processPathFailLimit <= processPathFailTick)
            {
                processPathFailTick = 0;
                getNewPath();
            }
        }
        break;
    default:
        break;
    }
    return true;
}

void Unit::setTargetLocation(Location* newTargetLocation)
{
    targetLocation = newTargetLocation;
    getNewPath();
}

void Unit::setTargetUnit(Unit* newTargetUnit)
{
    targetUnit = newTargetUnit;
    targetUnit->beingTargetedBy.push_back(this);
    getNewPath();
}

void Unit::setTileLocation(int x, int y) {
    tileLocation->x = x;
    tileLocation->y = y;
    tileDestination->x = x;
    tileDestination->y = y;
}

void Unit::moveTo(int x, int y)
{
    scene->zones[zone]->removeUnitFromLocation(this, tileLocation->x, tileLocation->y);
    scene->zones[zone]->removeUnitFromLocation(this, tileDestination->x, tileDestination->y);
    setTileLocation(x, y);
    scene->zones[zone]->unitMap[tileLocation->x][tileLocation->y].push_back(this);
    scene->zones[zone]->unitEntersTile(this, tileLocation->x, tileLocation->y);
    if (targetLocation != nullptr && x == targetLocation->x && y == targetLocation->y)
    {
        pathDirections.clear();
        targetLocation = nullptr;
    }
}

void Unit::portalTo(int zoneId, int x, int y)
{
    //remove unit from current zone
    scene->zones[zone]->removeUnitFromLocation(this, tileLocation->x, tileLocation->y);
    scene->zones[zone]->removeUnitFromLocation(this, tileDestination->x, tileDestination->y);
    auto unitIterator = scene->zones[zone]->units.begin();
    while (unitIterator != scene->zones[zone]->units.end())
    {
        if ((*unitIterator) == this) {
            unitIterator = scene->zones[zone]->units.erase(unitIterator);
            break;
        }
        else {
            unitIterator++;
        }
    }
    //add unit to new zone
    scene->zones[zoneId]->units.push_back(this);

    //set units location
    zone = zoneId;
    setTileLocation(x, y);
    scene->zones[zone]->unitMap[tileLocation->x][tileLocation->y].push_back(this);
    scene->zones[zone]->unitMap[tileDestination->x][tileDestination->y].push_back(this);
}

void Unit::updateCoords() {
    int coords[2];
    int destCoords[2];
    scene->coordsFromTileIndex(tileLocation->x, tileLocation->y, coords);
    scene->coordsFromTileIndex(tileDestination->x, tileDestination->y, destCoords);
    xpos = coords[0] + (destCoords[0] - coords[0]) * (1 - leftToMove) - scene->tileWidth;
    ypos = coords[1] + (destCoords[1] - coords[1]) * (1 - leftToMove) - scene->tileHeight;
}

void Unit::setStartLocation(int x, int y) {
    tileLocation->x = x;
    tileLocation->y = y;
    tileDestination->x = x;
    tileDestination->y = y;
    int screenCoords[2];
    scene->coordsFromTileIndex(x, y, screenCoords);
    xpos = screenCoords[0];
    ypos = screenCoords[1];
}

void Unit::draw()
{
    AnimatedSprite::draw();
}

void Unit::getLocationUnitIsFacing(int tileXY[2]) {
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
    if (unitStates.find(newState) != unitStates.end())
    {
        currentState = unitStates[newState];
    }
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
