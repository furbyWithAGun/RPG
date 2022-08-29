#include "SkeletonKing.h"
#include "BasicMeleeAttack.h"
#include "RpgTileGridScene.h"

const int MAX_HEALTH = 300;
const int SPEED = 8;
const int DEX = 37;
const int AGI = 22;
const int STR = 37;
const int EXP_VALUE = 600;
const int GOLD_VALUE = 3000;

SkeletonKing::SkeletonKing() : AiUnit() {
    init();
}
SkeletonKing::SkeletonKing(SaveObject saveObject, RpgTileGridScene* gameScene) : AiUnit(saveObject, gameScene)
{
    setDropTable();
    createAnimations();
}
SkeletonKing::SkeletonKing(int zoneId, int unitType) : AiUnit(zoneId, unitType) {
    init();
}

SkeletonKing::SkeletonKing(int zoneId, int unitType, RpgTileGridScene* gameScene) : AiUnit(zoneId, unitType, gameScene) {
    init(gameScene);
}

SkeletonKing::SkeletonKing(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY) : AiUnit(zoneId, unitType, gameScene, startX, startY) {
    init(gameScene);
}

void SkeletonKing::init() {
    setAttributeLevel(UNIT_STAT_SPEED, SPEED);
    health = MAX_HEALTH;
    setAttributeLevel(UNIT_STAT_MAX_HEALTH, MAX_HEALTH);
    expValue = EXP_VALUE;
    goldValue = GOLD_VALUE;
    setAttributeLevel(UNIT_STAT_DEX, DEX);
    setAttributeLevel(UNIT_STAT_AGI, AGI);
    setAttributeLevel(UNIT_STAT_STR, STR);
    //dex = DEX;
    //agi = AGI;
    //str = STR;
    equipedAttacks[MAIN_ATTACK] = new BasicMeleeAttack(MELEE, this); //potential memory leak
    activeAttack = equipedAttacks[MAIN_ATTACK];
    team = MONSTER_TEAM;
    setDropTable();
    createAnimations();
}

void SkeletonKing::init(RpgTileGridScene* gameScene) {
    init();
    //createAnimations();
    //resize(scene->tileWidth, scene->tileWidth);
}


void SkeletonKing::createAnimations() {
    addAnimation(IDLE_UP_LEFT, SKELETON_KING_IDLE_UP, 1, 10);
    addAnimation(IDLE_UP, SKELETON_KING_IDLE_UP, 1, 10);
    addAnimation(IDLE_UP_RIGHT, SKELETON_KING_IDLE_UP, 1, 10);
    addAnimation(IDLE_RIGHT, SKELETON_KING_IDLE_RIGHT, 1, 10);
    addAnimation(IDLE_DOWN_RIGHT, SKELETON_KING_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN, SKELETON_KING_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN_LEFT, SKELETON_KING_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_LEFT, SKELETON_KING_IDLE_LEFT, 1, 10);

    addAnimation(MOVE_DOWN, SKELETON_KING_MOVE_DOWN, 1, 40);
    addAnimation(MOVE_UP, SKELETON_KING_MOVE_UP, 1, 40);
    addAnimation(MOVE_RIGHT, SKELETON_KING_MOVE_RIGHT, 1, 40);
    addAnimation(MOVE_LEFT, SKELETON_KING_MOVE_LEFT, 1, 40);

    addAnimation(ATTACK_UP_LEFT, SKELETON_KING_ATTACK_UP, 1, 10, false);
    addAnimation(ATTACK_UP, SKELETON_KING_ATTACK_UP, 1, 10, false);
    addAnimation(ATTACK_UP_RIGHT, SKELETON_KING_ATTACK_UP, 1, 10, false);
    addAnimation(ATTACK_RIGHT, SKELETON_KING_ATTACK_RIGHT, 1, 10, false);
    addAnimation(ATTACK_DOWN_RIGHT, SKELETON_KING_ATTACK_DOWN, 1, 10, false);
    addAnimation(ATTACK_DOWN, SKELETON_KING_ATTACK_DOWN, 1, 10, false);
    addAnimation(ATTACK_DOWN_LEFT, SKELETON_KING_ATTACK_DOWN, 1, 10, false);
    addAnimation(ATTACK_LEFT, SKELETON_KING_ATTACK_LEFT, 1, 10, false);
}

void SkeletonKing::setDropTable()
{
    dropChance = 1.0;
    maxNumDrops = 5;
    dropTable.push_back({ 0.1, ITEM_MACE });
    dropTable.push_back({ 0.1, ITEM_LONG_SWORD });
    dropTable.push_back({ 0.01, ITEM_RAG_BODY });
    dropTable.push_back({ 0.01, ITEM_RAG_BOOTS });
    dropTable.push_back({ 0.01, ITEM_RAG_GLOVES });
    dropTable.push_back({ 0.01, ITEM_RAG_HAT });
    dropTable.push_back({ 0.01, ITEM_RAG_PANTS });
    dropTable.push_back({ 0.05, ITEM_LINEN_BODY });
    dropTable.push_back({ 0.05, ITEM_LINEN_BOOTS });
    dropTable.push_back({ 0.05, ITEM_LINEN_GLOVES });
    dropTable.push_back({ 0.05, ITEM_LINEN_HAT });
    dropTable.push_back({ 0.05, ITEM_LINEN_PANTS });
    dropTable.push_back({ 0.09, ITEM_LEATHER_BODY });
    dropTable.push_back({ 0.09, ITEM_LEATHER_BOOTS });
    dropTable.push_back({ 0.09, ITEM_LEATHER_GLOVES });
    dropTable.push_back({ 0.09, ITEM_LEATHER_HAT });
    dropTable.push_back({ 0.09, ITEM_LEATHER_PANTS });
    dropTable.push_back({ 0.01, ITEM_BRONZE_BODY });
    dropTable.push_back({ 0.01, ITEM_BRONZE_BOOTS });
    dropTable.push_back({ 0.01, ITEM_BRONZE_GLOVES });
    dropTable.push_back({ 0.01, ITEM_BRONZE_HELM });
    dropTable.push_back({ 0.01, ITEM_BRONZE_PANTS });
}

void SkeletonKing::death()
{
    RpgUnit::death();
    scene->addDelayedCombatMessage(20, "YOU HAVE BEATEN THE GAME! (Such that it is)", COLOR_GREEN, tileLocation->x, tileLocation->y, 1400);
}
