#include "SkeletonKing.h"
#include "BasicMeleeAttack.h"
#include "RpgTileGridScene.h"

const int MAX_HEALTH = 300;
const int SPEED = 8;
const int DEX = 35;
const int AGI = 20;
const int STR = 35;
const int EXP_VALUE = 300;
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
    speed = SPEED;
    health = MAX_HEALTH;
    maxHealth = MAX_HEALTH;
    expValue = EXP_VALUE;
    goldValue = GOLD_VALUE;
    dex = DEX;
    agi = AGI;
    str = STR;
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
    dropTable.push_back({ 1.0, ITEM_LONG_SWORD });
}

void SkeletonKing::death()
{
    RpgUnit::death();
    scene->addDelayedCombatMessage(20, "YOU HAVE BEATEN THE GAME! (Such that it is)", COLOR_GREEN, tileLocation->x, tileLocation->y, 1400);
}
