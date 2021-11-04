#pragma once
#include "Unit.h"
#include "ItemFactory.h"
#include "FoodEffect.h"
#include "Attack.h"
#include "RpgGameConstants.h"

class RpgTileGridScene;

enum RPG_UNIT_SAVE_ATTRIBUTES {
    UNIT_TEAM = NUM_UNIT_ATTRIBUTES,
    UNIT_GOLD,
    UNIT_GOLD_VALUE,
    UNIT_EXP_VALUE,
    UNIT_EQUIPPED_ITEMS,
    UNIT_INVENTORY,
    UNIT_ASSIGNED_TO_BUILDING,
    UNIT_MIN_NUM_DROPS,
    UNIT_MAX_NUM_DROPS,
    UNIT_DROP_CHANCE,
    UNIT_AGGRO_TRIGGER_DISTANCE,
    UNIT_AGGRO_MAINTAIN_DISTANCE,
    UNIT_MAX_MANA,
    UNIT_MANA,
    UNIT_DEX,
    UNIT_STR,
    UNIT_AGI,
    UNIT_END,
    UNIT_INTL,
    UNIT_BASE_ARMOUR,
    UNIT_ARMOUR,
    UNIT_COMBAT_EXPERIENCE,
    UNIT_COMBAT_EXPERIENCE_NEXT_LEVEL,
    UNIT_COMBAT_EXPERIENCE_LAST_LEVEL,
    UNIT_COMBAT_LEVEL,
    UNIT_HUNGER_LEVEL,
    UNIT_MAX_HUNGER_LEVEL,
    NUM_RPG_UNIT_ATTRIBUTES
};

enum EXPERIENCE_TYPES {
    COMBAT_EXPERIENCE
};

class RpgUnit : public Unit
{
public:
    //attributes
    std::deque<FoodEffect*> foodEffects;
    int hungerLevel;
    int maxHungerLevel;
    int team;
    int gold;
    int goldValue;
    int expValue;
    RpgTileGridScene* scene;
    std::unordered_map<int, Equipment*> equippedItems;
    std::vector<Item*> inventory;
    Building* assignedToBuilding;
    std::vector<ChanceObject> dropTable;
    int minNumDrops;
    int maxNumDrops;
    double dropChance;
    int aggroUpdateRate;
    int aggroUpdateTick;
    int aggroTriggerDistance, aggroMaintainDistance;


    //character stats
    int maxMana;
    int mana;
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

    //special attributes for loading saved units
    int assignedToBuildingId;

    //constructors
    RpgUnit();
    RpgUnit(SaveObject saveObject, RpgTileGridScene* gameScene);
    RpgUnit(int zoneId, int unitType);
    RpgUnit(int zoneId, int unitType, RpgTileGridScene* gameScene);
    RpgUnit(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY);

    //methods
    bool performAttack(int attackId);
    int assignDamage(int damageTaken);
    int assignDamage(RpgUnit* attackingUnit, int damageTaken);
    void draw() override;
    void drawHealth();
    void updateAttacks();
    void addExp(int expType, int expValue);
    void levelUp();
    void updateStats();
    int getTeamStatus(RpgUnit* otherUnit);
    void death();
    void death(RpgUnit* attackingUnit);
    bool equipItem(Equipment* item);
    bool unEquipItem(int slot);
    Weapon* getEquippedWeapon();
    void dropItemFromInventory(int inventoryIndex);
    void deleteItemFromInventory(int inventoryIndex);
    void deleteItemFromInventory(Item* itemToDelete);
    void removeItemFromInventory(int inventoryIndex);
    void removeItemFromInventory(Item* itemToDelete);
    std::vector<Item*> getDrops();
    virtual void setDropTable() {};
    void updateAggro();
    virtual void update() override;
    void setScene(RpgTileGridScene* gameScene);
    void eatFood(Food* foodToEat);
    void updateFoodEffects();
    void addToInventory(Item* itemToAdd);

    virtual std::string toSaveString(bool withHeaderAndFooter = true) override;

private:

    //methods
    void init();
    virtual void createAnimations() {};
    std::string getEquippedItemsSavedString();
    void setEquippedItemsFromSavedString(std::string saveString);
};

std::string getItemVectorSaveString(std::vector<Item*> vector);
std::vector<Item*> getItemVectorFromSaveString(std::string saveString);