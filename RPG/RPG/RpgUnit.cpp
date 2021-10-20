#include "RpgUnit.h"
#include "MovingState.h"
#include "AttackingState.h"
#include "IdleState.h"
#include "BareHands.h"
#include "RpgTileGridScene.h"

RpgUnit::RpgUnit() : Unit() {
    init();
}

RpgUnit::RpgUnit(int zoneId, int unitType) : Unit(zoneId, unitType) {
    init();
}

RpgUnit::RpgUnit(int zoneId, int unitType, RpgTileGridScene* gameScene) : Unit(zoneId, unitType, gameScene) {
    init();
    scene = gameScene;
}

RpgUnit::RpgUnit(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY) : Unit(zoneId, unitType, gameScene, startX, startY) {
    init();
    scene = gameScene;
}

bool RpgUnit::performAttack(int attackId)
{
    activeAttack = equipedAttacks[attackId];
    return activeAttack->startAttack();
}

int RpgUnit::assignDamage(int damageTaken)
{
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

int RpgUnit::assignDamage(RpgUnit* attackingUnit, int damageTaken)
{
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

void RpgUnit::draw()
{
    Unit::draw();
    drawHealth();
}

void RpgUnit::drawHealth()
{
    double healthPercent = (double)health / (double)maxHealth;
    scene->engine->renderRectangle(xpos + scene->tileWidth, ypos + scene->tileHeight, (double)scene->tileWidth * healthPercent, (double)scene->tileHeight * 0.05, 0xff, 0, 0);
}

void RpgUnit::updateAttacks()
{
    for (auto attack : equipedAttacks)
    {
        attack.second->update();
    }
}

void RpgUnit::addExp(int expType, int expValue)
{
    if (expType == COMBAT_EXPERIENCE)
    {
        combatExperience += expValue;
    }
    updateStats();
}

void RpgUnit::levelUp()
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

void RpgUnit::updateStats()
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

int RpgUnit::getTeamStatus(RpgUnit* otherUnit)
{
    return scene->getTeamStatus(team, otherUnit->team);
}

bool RpgUnit::equipItem(Equipment* item)
{
    if (item->slot != -1)
    {
        equippedItems[item->slot] = item;
        return true;
    }
    return false;
}

Weapon* RpgUnit::getEquippedWeapon()
{
    if (equippedItems[LEFT_HAND] != nullptr)
    {
        return (Weapon*)equippedItems[LEFT_HAND];
    }
    else {
        return (Weapon*)equippedItems[BARE_HANDS];
    }
}

void RpgUnit::dropItemFromInventory(int inventoryIndex)
{
    scene->currentZone->itemMap[tileLocation->x][tileLocation->y].push_back(inventory[inventoryIndex]);
    inventory.erase(inventory.begin() + inventoryIndex);
}

void RpgUnit::deleteItemFromInventory(int inventoryIndex)
{
    delete inventory[inventoryIndex];
    inventory.erase(inventory.begin() + inventoryIndex);
}

void RpgUnit::deleteItemFromInventory(Item* itemToDelete)
{
}

std::vector<Item*> RpgUnit::getDrops()
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

void RpgUnit::updateAggro()
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
        RpgUnit* tempTarget;
        for (int x = tileLocation->x - aggroTriggerDistance; x < tileLocation->x + aggroTriggerDistance; x++)
        {
            for (int y = tileLocation->y - aggroTriggerDistance; y < tileLocation->y + aggroTriggerDistance; y++)
            {
                tempTarget = (RpgUnit*)scene->getUnitAtLocation(zone, x, y);
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
void RpgUnit::update()
{
    Unit::update();
    updateAttacks();
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

void RpgUnit::init()
{
    scene = nullptr;
    maxMana = 1;
    mana = 1;
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
    expValue = 1;
    gold = 0;
    goldValue = 1;
    combatExperience = 0;
    IdleState* newState = new IdleState(UNIT_IDLE, this);
    unitStates.clear();
    //unitStates.insert({ 999999, new MovingState(UNIT_MOVING, this) });
    unitStates.insert({ UNIT_MOVING, new MovingState(UNIT_MOVING, this) });
    unitStates.insert({ UNIT_ATTACKING, new AttackingState(UNIT_ATTACKING, this) });
    unitStates.insert({ UNIT_IDLE, new IdleState(UNIT_IDLE, this) });
    //unitStates.insert({ UNIT_IDLE, newState });
    setUnitState(UNIT_IDLE);
    targetUnit = nullptr;
    team = UNKNOWN_TEAM;
    assignedToBuilding = nullptr;
    minNumDrops = 1;
    maxNumDrops = 1;
    dropChance = 0.0;
    aggroTriggerDistance = 4;
    aggroMaintainDistance = 6;
    aggroUpdateRate = 70;
    aggroUpdateTick = 0;
    
    for (int i = BARE_HANDS; i != NUM_EQUIPMENT_SLOTS; i++)
    {
        equippedItems[i] = nullptr;
    }
    equippedItems[BARE_HANDS] = new BareHands();

    setDropTable();
}


void RpgUnit::death()
{
    scene->addItemsToMap(zone, tileLocation->x, tileLocation->y, getDrops());
    active = false;
    toBeDeleted = true;
    for (auto unit : beingTargetedBy) {
        unit->targetUnit = nullptr;
    }
}

void RpgUnit::death(RpgUnit* attackingUnit)
{
    death();
    attackingUnit->addExp(COMBAT_EXPERIENCE, expValue);
    int goldGiven = scene->engine->randomInt(1, goldValue);
    if (zone == scene->currentZone->id)
    {
        scene->addDelayedCombatMessage(15, "+" + std::to_string(goldGiven) + " Gold", COLOR_GOLD, tileLocation->x, tileLocation->y, 140);
    }
    attackingUnit->gold += goldGiven;
}
