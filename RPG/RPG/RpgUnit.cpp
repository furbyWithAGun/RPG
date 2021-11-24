#include "RpgUnit.h"
#include "MovingState.h"
#include "AttackingState.h"
#include "IdleState.h"
#include "BareHands.h"
#include "RpgTileGridScene.h"
#include "BasicMeleeAttack.h"
std::unordered_map<int, int> nextLevelExp = {
    {1, 30},
    {2, 50},
    {3, 75},
    {4, 100},
    {5, 130},
    {6, 170},
    {7, 210},
    {8, 280},
    {9, 350},
    {10, 450},
    {11, 550},
    {12, 700},
    {13, 850},
    {14, 975},
    {15, 1150},
    {16, 1350},
    {17, 1650},
    {18, 1800},
    {19, 2000},
    {20, 2100}
};


RpgUnit::RpgUnit() : Unit() {
    init();
}

RpgUnit::RpgUnit(SaveObject saveObject, RpgTileGridScene* gameScene) : Unit(saveObject, gameScene)
{
    init();
    scene = gameScene;
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case UNIT_TEAM:
            team = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_GOLD:
            gold = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_GOLD_VALUE:
            goldValue = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_EXP_VALUE:
            expValue = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_EQUIPPED_ITEMS:
            setEquippedItemsFromSavedString(saveObject.attributes[i].valueString);
            break;
        case UNIT_INVENTORY:
            inventory = getItemVectorFromSaveString(saveObject.attributes[i].valueString);
            break;
        case UNIT_ASSIGNED_TO_BUILDING:
            assignedToBuildingId = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_MIN_NUM_DROPS:
            minNumDrops = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_MAX_NUM_DROPS:
            maxNumDrops = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_DROP_CHANCE:
            dropChance = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_AGGRO_TRIGGER_DISTANCE:
            aggroTriggerDistance = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_AGGRO_MAINTAIN_DISTANCE:
            aggroMaintainDistance = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_MAX_MANA:
            maxMana = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_MANA:
            mana = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_DEX:
            dex = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_STR:
            str = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_AGI:
            agi = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_END:
            end = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_INTL:
            intl = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_BASE_ARMOUR:
            baseArmour = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_ARMOUR:
            armour = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_COMBAT_EXPERIENCE:
            combatExperience = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_COMBAT_EXPERIENCE_NEXT_LEVEL:
            combatExperienceNextLevel = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_COMBAT_EXPERIENCE_LAST_LEVEL:
            combatExperienceLastLevel = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_COMBAT_LEVEL:
            combatLevel = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_HUNGER_LEVEL:
            hungerLevel = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_MAX_HUNGER_LEVEL:
            maxHungerLevel = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
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
    currentState->updateAnimation();
    Unit::draw();
    drawHealth();
}

void RpgUnit::drawHealth()
{
    int healthToDisplay;
    if (health < 0 )
    {
        healthToDisplay = 0;
    }
    else {
        healthToDisplay = health;
    }
    double healthPercent = (double)healthToDisplay / (double)maxHealth;
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
    if (scene->getZone(zone) == scene->currentZone)
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
        if (equippedItems[item->slot] != nullptr)
        {
            addToInventory(equippedItems[item->slot]);
        }
        equippedItems[item->slot] = item;
        removeItemFromInventory(item);
        if (scene->menus[INVENTORY_MENU]->isActive)
        {
            scene->menus[INVENTORY_MENU]->rebuildElements();
        }
        if (scene->menus[EQUIPPED_MENU]->isActive)
        {
            scene->menus[EQUIPPED_MENU]->rebuildElements();
        }
        return true;
    }
    return false;
}

bool RpgUnit::unEquipItem(int slot)
{
    addToInventory(equippedItems[slot]);
    equippedItems[slot] = nullptr;
    if (scene->menus[EQUIPPED_MENU]->isActive)
    {
        scene->menus[EQUIPPED_MENU]->rebuildElements();
    }
    if (scene->menus[INVENTORY_MENU]->isActive)
    {
        scene->menus[INVENTORY_MENU]->rebuildElements();
    }
    return true;
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
    scene->currentZone->addItemToLocation(inventory[inventoryIndex], tileLocation->x, tileLocation->y);
    removeItemFromInventory(inventoryIndex);
}

void RpgUnit::deleteItemFromInventory(int inventoryIndex)
{
    /*delete inventory[inventoryIndex];
    inventory.erase(inventory.begin() + inventoryIndex);*/
    deleteItemFromContainer(inventoryIndex, inventory);
    if (this == scene->player && scene->menus[INVENTORY_MENU]->isActive)
    {
        scene->menus[INVENTORY_MENU]->rebuildElements();
    }
}

void RpgUnit::deleteItemFromInventory(Item* itemToDelete)
{
    /*int delIndex = -1;
    for (size_t i = 0; i < inventory.size(); i++)
    {
        if (inventory[i] == itemToDelete) {
            delIndex = i;
            break;
        }
    }
    if (delIndex == -1)
    {
        return;
    }
    deleteItemFromInventory(delIndex);*/
    deleteItemFromContainer(itemToDelete, inventory);
}

void RpgUnit::removeItemFromInventory(int inventoryIndex)
{
    //inventory.erase(inventory.begin() + inventoryIndex);
    removeItemFromContainer(inventoryIndex, inventory);
    if (this == scene->player && scene->menus[INVENTORY_MENU]->isActive)
    {
        scene->menus[INVENTORY_MENU]->rebuildElements();
    }
}

void RpgUnit::removeItemFromInventory(Item* itemToDelete)
{
    /*int delIndex = -1;
    for (size_t i = 0; i < inventory.size(); i++)
    {
        if (inventory[i] == itemToDelete) {
            delIndex = i;
            break;
        }
    }
    if (delIndex == -1)
    {
        return;
    }
    removeItemFromInventory(delIndex);*/
    removeItemFromContainer(itemToDelete, inventory);
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
    if (aggroUpdateTick != scene->aggroUpdateRate)
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
        if (targetUnit->scene->isUnitToBeDestroyed(targetUnit) || (std::abs(targetUnit->tileLocation->x - tileLocation->x) > aggroMaintainDistance) || (std::abs(targetUnit->tileLocation->y - tileLocation->y) > aggroMaintainDistance))
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
        if (scene->getPathRate == getPathTick)
        {
            getPathTick = 0;
            getNewPath();
        }
        else {
            getPathTick++;
        }
    }
    updateFoodEffects();
}

void RpgUnit::setScene(RpgTileGridScene* gameScene)
{
    scene = gameScene;
    Unit::setScene(gameScene);
}

void RpgUnit::eatFood(Food* foodToEat)
{
    foodToEat->stackSize -= 1;
    hungerLevel += foodToEat->hungerGain;
    FoodEffect* foodEffect = new FoodEffect(foodToEat);
    for (auto effect : foodEffects) {
        if (effect->name == foodEffect->name)
        {
            effect->tick = 0;
            return;
        }
    }
    if (foodEffects.size() < MAX_NUM_FOOD_EFFECTS)
    {
        foodEffects.push_back(foodEffect);
        return;
    }

    foodEffects.pop_front();
    foodEffects.push_back(foodEffect);
}

void RpgUnit::updateFoodEffects()
{
    auto effectIterator = foodEffects.begin();
    while (effectIterator != foodEffects.end())
    {
        (*effectIterator)->onUpdate(this);
        if ((*effectIterator)->tick >= (*effectIterator)->duration) {
            
            delete (*effectIterator);
            effectIterator = foodEffects.erase(effectIterator);
        }
        else {
            effectIterator++;
        }
    }
}

void RpgUnit::addToInventory(Item* itemToAdd)
{
    addItemToContainer(itemToAdd, inventory);
    if (this == scene->player && scene->menus[INVENTORY_MENU]->isActive)
    {
        scene->menus[INVENTORY_MENU]->rebuildElements();
    }
}

std::string RpgUnit::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_RPG_UNIT) + "\n";
    }
    saveString += Unit::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), UNIT_TEAM, team);
    saveString += getAttributeString(getUniqueId(), UNIT_GOLD, gold);
    saveString += getAttributeString(getUniqueId(), UNIT_GOLD_VALUE, goldValue);
    saveString += getAttributeString(getUniqueId(), UNIT_EXP_VALUE, expValue);
    saveString += getAttributeString(getUniqueId(), UNIT_EQUIPPED_ITEMS, getEquippedItemsSavedString());
    saveString += getAttributeString(getUniqueId(), UNIT_INVENTORY, getItemVectorSaveString(inventory));
    if (assignedToBuilding != nullptr)
    {
        saveString += getAttributeString(getUniqueId(), UNIT_ASSIGNED_TO_BUILDING, assignedToBuilding->id);
    }
    saveString += getAttributeString(getUniqueId(), UNIT_MIN_NUM_DROPS, minNumDrops);
    saveString += getAttributeString(getUniqueId(), UNIT_MAX_NUM_DROPS, maxNumDrops);
    saveString += getAttributeString(getUniqueId(), UNIT_DROP_CHANCE, dropChance);
    saveString += getAttributeString(getUniqueId(), UNIT_AGGRO_TRIGGER_DISTANCE, aggroTriggerDistance);
    saveString += getAttributeString(getUniqueId(), UNIT_AGGRO_MAINTAIN_DISTANCE, aggroMaintainDistance);
    saveString += getAttributeString(getUniqueId(), UNIT_MAX_MANA, maxMana);
    saveString += getAttributeString(getUniqueId(), UNIT_MANA, mana);
    saveString += getAttributeString(getUniqueId(), UNIT_DEX, dex);
    saveString += getAttributeString(getUniqueId(), UNIT_STR, str);
    saveString += getAttributeString(getUniqueId(), UNIT_AGI, agi);
    saveString += getAttributeString(getUniqueId(), UNIT_END, end);
    saveString += getAttributeString(getUniqueId(), UNIT_INTL, intl);
    saveString += getAttributeString(getUniqueId(), UNIT_BASE_ARMOUR, baseArmour);
    saveString += getAttributeString(getUniqueId(), UNIT_ARMOUR, armour);
    saveString += getAttributeString(getUniqueId(), UNIT_COMBAT_EXPERIENCE, combatExperience);
    saveString += getAttributeString(getUniqueId(), UNIT_COMBAT_EXPERIENCE_NEXT_LEVEL, combatExperienceNextLevel);
    saveString += getAttributeString(getUniqueId(), UNIT_COMBAT_EXPERIENCE_LAST_LEVEL, combatExperienceLastLevel);
    saveString += getAttributeString(getUniqueId(), UNIT_COMBAT_LEVEL, combatLevel);
    saveString += getAttributeString(getUniqueId(), UNIT_HUNGER_LEVEL, hungerLevel);
    saveString += getAttributeString(getUniqueId(), UNIT_MAX_HUNGER_LEVEL, maxHungerLevel);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_RPG_UNIT) + "\n";
    }
    return saveString;
}

void RpgUnit::init()
{
    scene = nullptr;
    maxHungerLevel = 500;
    hungerLevel = maxHungerLevel;
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
    aggroUpdateTick = 0;
    //special attributes for loading saved units
    assignedToBuildingId = -1;
    
    for (int i = BARE_HANDS; i != NUM_EQUIPMENT_SLOTS; i++)
    {
        equippedItems[i] = nullptr;
    }
    equippedItems[BARE_HANDS] = new BareHands();
    equipedAttacks[MAIN_ATTACK] = new BasicMeleeAttack(MELEE, this); //potential memory leak
    activeAttack = equipedAttacks[MAIN_ATTACK];

    setDropTable();
    createAnimations();
}

std::string RpgUnit::getEquippedItemsSavedString()
{
    std::vector<Item*> equippedItemsVector;
    for (auto item : equippedItems)
    {
        if (item.second != nullptr)
        {
            equippedItemsVector.push_back(item.second);
        }
    }
    return getItemVectorSaveString(equippedItemsVector);
}

void RpgUnit::setEquippedItemsFromSavedString(std::string saveString)
{
    for (auto item : getItemVectorFromSaveString(saveString)) {
        equippedItems[((Equipment*)item)->slot] = (Equipment*)item;
    }
}


void RpgUnit::death()
{
    scene->addItemsToMap(zone, tileLocation->x, tileLocation->y, getDrops());
    active = false;
    scene->addUnitToDestroy(this);
}

void RpgUnit::death(RpgUnit* attackingUnit)
{
    death();
    attackingUnit->addExp(COMBAT_EXPERIENCE, expValue);
    int goldGiven = scene->engine->randomInt(1, goldValue);
    if (zone == scene->currentZone->id && attackingUnit == scene->player)
    {
        scene->addDelayedCombatMessage(15, "+" + std::to_string(goldGiven) + " Gold", COLOR_GOLD, tileLocation->x, tileLocation->y, 140);
    }
    attackingUnit->gold += goldGiven;
}

std::string getItemVectorSaveString(std::vector<Item*> vector) {
    std::string returnString;
    returnString += std::to_string(vector.size()) + "\n";
    for (int i = 0; i < vector.size(); i++)
    {
        returnString += vector[i]->toSaveString() + "\n";
    }
    return returnString;
}

std::vector<Item*> getItemVectorFromSaveString(std::string saveString) {
    std::vector<Item*> returnVector;

    std::vector<SaveObject> savedItems = getSaveObjectVectorFromSaveString2(saveString);

    for (size_t i = 0; i < savedItems.size(); i++)
    {
        for (int j = 0; j < savedItems[i].attributes.size(); j++)
        {
            if (savedItems[i].attributes[j].attributeType == ITEM_TYPE)
            {
                switch (stoi(savedItems[i].attributes[j].valueString)) {
                case WEAPON:
                    returnVector.push_back(new Weapon(savedItems[i].rawString));;
                    break;
                case ARMOUR:
                    returnVector.push_back(new Armour(savedItems[i].rawString));;
                    break;
                default:
                    returnVector.push_back(new Item(savedItems[i].rawString));
                    break;
                }
                break;
            }
        }
    }

    return returnVector;
}