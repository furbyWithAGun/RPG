#pragma once
#include "Unit.h"
#include "ItemFactory.h"

#include "Attack.h"
#include "RpgGameConstants.h"

class RpgTileGridScene;

enum EXPERIENCE_TYPES {
    COMBAT_EXPERIENCE
};

class RpgUnit : public Unit
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
    int team;
    int gold;
    int goldValue;
    int expValue;
    RpgTileGridScene* scene;
    std::unordered_map<int, Equipment*> equippedItems;
    std::vector<Item*> inventory;
    Building* assignedToBuilding;
    std::vector<chanceObject> dropTable;
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

    //constructors
    RpgUnit();
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
    Weapon* getEquippedWeapon();
    void dropItemFromInventory(int inventoryIndex);
    void deleteItemFromInventory(int inventoryIndex);
    void deleteItemFromInventory(Item* itemToDelete);
    std::vector<Item*> getDrops();
    virtual void setDropTable() {};
    void updateAggro();
    virtual void update() override;


private:

    //methods
    void init();
};

