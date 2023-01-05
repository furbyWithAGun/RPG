#include "Skeleton.h"

#include "BasicMeleeAttack.h"

const int MAX_HEALTH = 80;
const int SPEED = 4;
const int DEX = 20;
const int AGI = 8;
const int STR = 20;
const int EXP_VALUE = 25;
const int GOLD_VALUE = 75;

Skeleton::Skeleton() : AiUnit() {
    init();
}
Skeleton::Skeleton(SaveObject saveObject, RpgTileGridScene* gameScene) : AiUnit(saveObject, gameScene)
{
    setDropTable();
    createAnimations();
}
Skeleton::Skeleton(int zoneId, int unitType) : AiUnit(zoneId, unitType) {
    init();
}

Skeleton::Skeleton(int zoneId, int unitType, RpgTileGridScene* gameScene) : AiUnit(zoneId, unitType, gameScene) {
    init(gameScene);
}

Skeleton::Skeleton(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY) : AiUnit(zoneId, unitType, gameScene, startX, startY) {
    init(gameScene);
}

void Skeleton::init() {
    setAttributeLevel(UNIT_STAT_SPEED, SPEED);
    health = MAX_HEALTH;
    setAttributeLevel(UNIT_STAT_MAX_HEALTH, MAX_HEALTH);
    expValue = EXP_VALUE;
    setAttributeLevel(UNIT_STAT_DEX, DEX);
    setAttributeLevel(UNIT_STAT_AGI, AGI);
    setAttributeLevel(UNIT_STAT_STR, STR);
    //dex = DEX;
    //agi = AGI;
    //str = STR;
    equipedAttacks[MAIN_ATTACK] = new BasicMeleeAttack(MELEE, this); //potential memory leak
    activeAttack = equipedAttacks[MAIN_ATTACK];
    team = MONSTER_TEAM;
    goldValue = GOLD_VALUE;
    setDropTable();
    createAnimations();
}

void Skeleton::init(RpgTileGridScene* gameScene) {
    init();
    //createAnimations();
    //resize(scene->tileWidth, scene->tileWidth);
}


void Skeleton::createAnimations() {
    addAnimation(IDLE_UP_LEFT, SKELETON_IDLE_UP, 1, 10);
    addAnimation(IDLE_UP, SKELETON_IDLE_UP, 1, 10);
    addAnimation(IDLE_UP_RIGHT, SKELETON_IDLE_UP, 1, 10);
    addAnimation(IDLE_RIGHT, SKELETON_IDLE_RIGHT, 1, 10);
    addAnimation(IDLE_DOWN_RIGHT, SKELETON_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN, SKELETON_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN_LEFT, SKELETON_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_LEFT, SKELETON_IDLE_LEFT, 1, 10);

    addAnimation(MOVE_DOWN, SKELETON_MOVE_DOWN, 4, 40);
    addAnimation(MOVE_UP, SKELETON_MOVE_UP, 4, 40);
    addAnimation(MOVE_RIGHT, SKELETON_MOVE_RIGHT, 4, 40);
    addAnimation(MOVE_LEFT, SKELETON_MOVE_LEFT, 4, 40);

    addAnimation(ATTACK_UP_LEFT, SKELETON_ATTACK_UP, 2, 10, false);
    addAnimation(ATTACK_UP, SKELETON_ATTACK_UP, 2, 10, false);
    addAnimation(ATTACK_UP_RIGHT, SKELETON_ATTACK_UP, 2, 10, false);
    addAnimation(ATTACK_RIGHT, SKELETON_ATTACK_RIGHT, 2, 10, false);
    addAnimation(ATTACK_DOWN_RIGHT, SKELETON_ATTACK_DOWN, 2, 10, false);
    addAnimation(ATTACK_DOWN, SKELETON_ATTACK_DOWN, 2, 10, false);
    addAnimation(ATTACK_DOWN_LEFT, SKELETON_ATTACK_DOWN, 2, 10, false);
    addAnimation(ATTACK_LEFT, SKELETON_ATTACK_LEFT, 2, 10, false);
}

void Skeleton::setDropTable()
{
    dropChance = 0.25;

    DropTable dropTable = DropTable();
    dropTable.chance = 0.25;
    dropTable.items.push_back({ 0.09, ITEM_SHORT_SWORD });
    dropTable.items.push_back({ 0.09, ITEM_MACE });
    dropTable.items.push_back({ 0.06, ITEM_LONG_SWORD });
    dropTable.items.push_back({ 0.10, ITEM_RAG_BODY });
    dropTable.items.push_back({ 0.10, ITEM_RAG_BOOTS });
    dropTable.items.push_back({ 0.10, ITEM_RAG_GLOVES });
    dropTable.items.push_back({ 0.10, ITEM_RAG_HAT });
    dropTable.items.push_back({ 0.10, ITEM_RAG_PANTS });
    dropTable.items.push_back({ 0.04, ITEM_LINEN_BODY });
    dropTable.items.push_back({ 0.04, ITEM_LINEN_BOOTS });
    dropTable.items.push_back({ 0.04, ITEM_LINEN_GLOVES });
    dropTable.items.push_back({ 0.04, ITEM_LINEN_HAT });
    dropTable.items.push_back({ 0.04, ITEM_LINEN_PANTS });
    dropTable.items.push_back({ 0.01, ITEM_LEATHER_BODY });
    dropTable.items.push_back({ 0.01, ITEM_LEATHER_BOOTS });
    dropTable.items.push_back({ 0.01, ITEM_LEATHER_GLOVES });
    dropTable.items.push_back({ 0.01, ITEM_LEATHER_HAT });
    dropTable.items.push_back({ 0.01, ITEM_LEATHER_PANTS });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_BODY });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_BOOTS });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_GLOVES });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_HELM });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_PANTS });
    dropTables.push_back(dropTable);
}
