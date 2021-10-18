#include "Unit.h"
#include"GameScene.h"
#include "Player.h"

Weapon* Unit::getEquippedWeapon()
{
    if (equippedItems[LEFT_HAND] != nullptr)
    {
        return (Weapon* )equippedItems[LEFT_HAND];
    }
    else {
        return (Weapon*)equippedItems[BARE_HANDS];
    }
}

void Unit::dropItemFromInventory(int inventoryIndex)
{
    scene->currentZone->itemMap[tileLocation->x][tileLocation->y].push_back(inventory[inventoryIndex]);
    inventory.erase(inventory.begin() + inventoryIndex);
}

void Unit::deleteItemFromInventory(int inventoryIndex)
{
    delete inventory[inventoryIndex];
    inventory.erase(inventory.begin() + inventoryIndex);
}

void Unit::deleteItemFromInventory(Item* itemToDelete)
{
}

std::vector<Item*> Unit::getDrops()
{
    std::vector<Item*> returnItems;
    if (dropChance > scene->engine->randomDouble())
    {
        if (dropTable.size() > 0)
        {
            int numDrops = scene->engine->randomInt(minNumDrops, maxNumDrops);
            for (size_t i = 0; i < numDrops; i++)
            {
                returnItems.push_back(createNewItem(scene->engine->pickElementByProbability(dropTable)));
            }
        }
    }
    return returnItems;
}

void Unit::updateAggro()
{
    if (aggroUpdateTick != aggroUpdateRate)
    {
        aggroUpdateTick++;
        return;
    }
    else {
        aggroUpdateTick = 0;
    }
    if (targetUnit == nullptr)
    {
        Unit* tempTarget;
        for (int x = tileLocation->x - aggroTriggerDistance; x < tileLocation->x + aggroTriggerDistance; x++)
        {
            for (int y = tileLocation->y - aggroTriggerDistance; y < tileLocation->y + aggroTriggerDistance; y++)
            {
                tempTarget = scene->getUnitAtLocation(zone, x, y);
                if (tempTarget != nullptr && getTeamStatus(tempTarget) == ENEMY)
                {
                    setTargetUnit(tempTarget);
                    return;
                }
            }
        }
    }
    else {
        if (targetUnit->toBeDeleted || (std::abs(targetUnit->tileLocation->x - tileLocation->x) > aggroMaintainDistance) || (std::abs(targetUnit->tileLocation->y - tileLocation->y) > aggroMaintainDistance))
        {
            auto unitIterator = targetUnit->beingTargetedBy.begin();
            while (unitIterator != targetUnit->beingTargetedBy.end())
            {
                if ((*unitIterator) == this) {
                    unitIterator = targetUnit->beingTargetedBy.erase(unitIterator);
                    break;
                }
                else {
                    unitIterator++;
                }
            }
            targetUnit = nullptr;
        }
    }
}

void Unit::updateAggro2()
{
    /*if (aggroUpdateTick != aggroUpdateRate)
    {
        aggroUpdateTick++;
        return;
    }
    else {
        aggroUpdateTick = 0;
    }*/
    int tileCoords[2], screenCoords[2];
    if (targetUnit == nullptr)
    {
        Unit* tempTarget;
        for (size_t x = tileLocation->x - aggroTriggerDistance; x < tileLocation->x + aggroTriggerDistance; x++)
        {
            for (size_t y = tileLocation->y - aggroTriggerDistance; y < tileLocation->y + aggroTriggerDistance; y++)
            {
                tempTarget = scene->getUnitAtLocation(zone, x, y);
                if (tempTarget != nullptr && getTeamStatus(tempTarget) == ENEMY)
                {
                    targetUnit = tempTarget;
                    getNewPath();
                    scene->coordsFromTileIndex(x, y, screenCoords);
                    scene->engine->renderText("X", screenCoords[0], screenCoords[1], scene->tileWidth, scene->tileHeight, COLOR_RED);
                    return;
                }
                else {
                    scene->coordsFromTileIndex(x,y, screenCoords);
                    scene->engine->renderText("O", screenCoords[0], screenCoords[1], scene->tileWidth, scene->tileHeight, COLOR_GREEN);
                }
            }
        }
    }
    else {
        if (targetUnit->toBeDeleted || (std::abs(targetUnit->tileLocation->x - tileLocation->x) > aggroMaintainDistance) || (std::abs(targetUnit->tileLocation->y - tileLocation->y) > aggroMaintainDistance))
        {
            targetUnit = nullptr;
            if (tileDestination != nullptr)
            {
                getNewPath();
            }
        }
        else if (pathDirections.size() <= 0)
        {
            getNewPath();
        }
    }
}

void Unit::getNewPath()
{
    //SDL_CreateThread(getPathThread, "getPathThread", (void*)this);
    scene->unitsNeedingPath.push_back(this);
}

//void Unit::getNewPath()
//{
//    std::vector<int> tempDirections;
//    if (targetUnit != nullptr)
//    {
//        tempDirections = scene->zones[zone]->getPathDirectionsToUnit(scene, tileDestination, targetUnit, this);
//        if (tempDirections.size() > 0)
//        {
//            pathDirections = tempDirections;
//            return;
//        }
//        getNewPathFailTick++;
//        if (getNewPathFailTick == getNewPathFailLimit)
//        {
//            getNewPathFailTick = 0;
//            pathDirections = scene->zones[zone]->getPathDirectionsIgnoreAllunits(scene, tileDestination, targetUnit->tileDestination);
//        }
//        return;
//    }
//    else if (targetLocation != nullptr) {
//        tempDirections = scene->zones[zone]->getPathDirections(scene, tileDestination, targetLocation);
//        if (tempDirections.size() > 0)
//        {
//            pathDirections = tempDirections;
//            return;
//        }
//        getNewPathFailTick++;
//        if (getNewPathFailTick == getNewPathFailLimit)
//        {
//            getNewPathFailTick = 0;
//            pathDirections = scene->zones[zone]->getPathDirectionsIgnoreAllunits(scene, tileDestination, targetLocation);
//        }
//    }
//}

//constructors
Unit::Unit() : AnimatedSprite() {
    init();
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
    maxMana = 1;
    mana = 1;
    speed = 1;
    dex = 1;
    str = 1;
    agi = 1;
    end = 1;
    intl = 1;
    armour = 1;
    baseArmour = 1;
    combatExperience = 0;
    combatExperienceLastLevel = 0;
    combatLevel = 1;
    combatExperienceNextLevel += nextLevelExp[combatLevel];
    leftToMove = 0;
    expValue = 1;
    gold = 0;
    goldValue = 1;
    combatExperience = 0;
    isStatic = false;
    isPlayerControlled = false;
    canGoThroughPortal = true;
    directionFacing = DOWN;
    movingUp = movingDown = movingRight = movingLeft = false;
    setTileLocation(0, 0);
    unitStates.clear();
    unitStates.insert({ UNIT_IDLE, new IdleState(UNIT_IDLE, this) });
    unitStates.insert({ UNIT_MOVING, new MovingState(UNIT_MOVING, this) });
    unitStates.insert({ UNIT_ATTACKING, new AttackingState(UNIT_ATTACKING, this) });
    setUnitState(UNIT_IDLE);
    team = UNKNOWN_TEAM;
    zone = 0;
    assignedToBuilding = nullptr;
    minNumDrops = 1;
    maxNumDrops = 1;
    dropChance = 0.0;
    targetUnit = nullptr;
    aggroTriggerDistance = 4;
    aggroMaintainDistance = 6;
    toBeDeleted = false;
    aggroUpdateRate = 70;
    aggroUpdateTick = 0;
    getPathTick = 0;
    getPathRate = 30;
    adjustPathTick = 0;
    adjustPathRate = 3;
    getNewPathFailLimit = 2;
    getNewPathFailTick = 0;
    processPathFailLimit = 20;
    processPathFailTick = 0;

    for (int i = BARE_HANDS; i != NUM_EQUIPMENT_SLOTS; i++)
    {
        equippedItems[i] = nullptr;
    }
    equippedItems[BARE_HANDS] = new BareHands();

    setDropTable();
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

void Unit::addExp(int expType, int expValue)
{
    if (expType == COMBAT_EXPERIENCE)
    {
        combatExperience += expValue;
    }
    updateStats();
}

bool Unit::isAlive()
{
    return health > 0 && active;
}

void Unit::levelUp()
{
    combatLevel += 1;
    combatExperienceLastLevel = combatExperienceNextLevel;
    if (nextLevelExp.find(combatLevel) != nextLevelExp.end())
    {
        combatExperienceNextLevel += nextLevelExp[combatLevel];
    }
    else {
        combatExperienceNextLevel = combatExperienceNextLevel * 2;
    }
    dex += 1;
    str += 1;
    agi += 1;
    end += 1;
    intl += 1;
    maxHealth += 10;
    health += 10;
    if (scene->zones[zone] == scene->currentZone)
    {
        scene->addCombatMessage("***LEVEL UP***", COLOR_GREEN, tileLocation->x, tileLocation->y, 150);
    }
    updateStats();
}

void Unit::updateStats()
{
    if (combatExperience >= combatExperienceNextLevel)
    {
        levelUp();
    }
    armour = baseArmour;
    for (int i = BARE_HANDS + 1; i != NUM_EQUIPMENT_SLOTS; i++)
    {
        if (equippedItems[i] != nullptr)
        {
            if (equippedItems[i]->type == ARMOUR)
            {
                armour += ((Armour*)equippedItems[i])->armour;
            }
            equippedItems[i]->statModifier(this);
        }
    }
}

int Unit::getTeamStatus(Unit* otherUnit)
{
    return scene->getTeamStatus(team, otherUnit->team);
}

void Unit::death()
{
    scene->addItemsToMap(zone, tileLocation->x, tileLocation->y, getDrops());
    active = false;
    toBeDeleted = true;
    for (auto unit : beingTargetedBy) {
        unit->targetUnit = nullptr;
    }
}

void Unit::death(Unit* attackingUnit)
{
    death();
    attackingUnit->addExp(COMBAT_EXPERIENCE, expValue);
    int goldGiven = scene->engine->randomInt(1, goldValue);
    if (zone == scene->player->zone)
    {
        scene->addDelayedCombatMessage(15, "+" + std::to_string(goldGiven) + " Gold", COLOR_GOLD, tileLocation->x, tileLocation->y, 140);
    }
    attackingUnit->gold += goldGiven;
}

bool Unit::equipItem(Equipment* item)
{
    if (item->slot != -1)
    {
        equippedItems[item->slot] = item;
        return true;
    }
    return false;
}

//destructor
Unit::~Unit() {
    name = "";
    health = 0;
    speed = 0;
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
    if ((targetLocation != nullptr || targetUnit != nullptr) && pathDirections.size() <= 0)
    {
        if (getPathRate == getPathTick)
        {
            getPathTick = 0;
            getNewPath();
        }
        else {
            getPathTick++;
        }
    }
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

    //if unit is player switch zone
    if (this == (Unit* )scene->player)
    {
        //unit->health = unit->maxHealth;
        scene->loadZone(zone);
    }
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
    drawHealth();
}

bool Unit::performAttack(int attackId) {
    activeAttack = equipedAttacks[attackId];
    return activeAttack->startAttack();
}

int Unit::assignDamage(int damageTaken) {
    damageTaken -= armour;
    if (damageTaken < 1)
    {
        damageTaken = 1;
    }
    health -= damageTaken;
    if (health <= 0)
    {
        death();
        return health;
    }
}

int Unit::assignDamage(Unit* attackingUnit, int damageTaken)
{
    if ((Unit*)scene->player == this)
    {
        int dfgf = 87;
    }
    damageTaken -= armour;
    if (damageTaken < 1)
    {
        damageTaken = 1;
    }
    if (zone == scene->currentZone->id)
    {
        scene->addCombatMessage(std::to_string(damageTaken), SDL_Color{ 255, 0, 0, 0 }, tileLocation->x, tileLocation->y);
    }
    health -= damageTaken;
    if (health <= 0)
    {
        death(attackingUnit);
    }
    return health;

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

void Unit::drawHealth()
{
    double healthPercent = (double)health / (double)maxHealth;
    scene->engine->renderRectangle(xpos + scene->tileWidth, ypos + scene->tileHeight, (double)scene->tileWidth * healthPercent, (double)scene->tileHeight * 0.05, 0xff, 0, 0);
}

void Unit::handleInput(InputMessage* message) {
    setUnitState(currentState->handleInput(message));
}
void Unit::setUnitState(int newState) {
    currentState = unitStates[newState];
}

void Unit::updateAttacks() {
    for (auto attack : equipedAttacks)
    {
        attack.second->update();
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