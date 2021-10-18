#include "RatKing.h"
#include "BasicMeleeAttack.h"

const int RAT_KING_MAX_HEALTH = 250;
const int RAT_KING_SPEED = 4;
const int RAT_KING_DEX = 15;
const int RAT_KING_AGI = 15;
const int RAT_KING_STR = 20;
const int RAT_KING_EXP_VALUE = 300;

RatKing::RatKing() : AiUnit() {
    init();
}
RatKing::RatKing(int zoneId, int unitType) : AiUnit(zoneId, unitType) {
    init();
}

RatKing::RatKing(int zoneId, int unitType, TileGridScene* gameScene) : AiUnit(zoneId, unitType, gameScene) {
    init(gameScene);
}

RatKing::RatKing(int zoneId, int unitType, TileGridScene* gameScene, int startX, int startY) : AiUnit(zoneId, unitType, gameScene, startX, startY) {
    init(gameScene);
}

void RatKing::init() {
    speed = RAT_KING_SPEED;
    health = RAT_KING_MAX_HEALTH;
    maxHealth = RAT_KING_MAX_HEALTH;
    expValue = RAT_KING_EXP_VALUE;
    dex = RAT_KING_DEX;
    agi = RAT_KING_AGI;
    str = RAT_KING_STR;
    equipedAttacks[MAIN_ATTACK] = new BasicMeleeAttack(MELEE, this); //potential memory leak
    activeAttack = equipedAttacks[MAIN_ATTACK];
    team = MONSTER_TEAM;
    setDropTable();
}

void RatKing::init(TileGridScene* gameScene) {
    init();
    createAnimations();
    //resize(scene->tileWidth, scene->tileWidth);
}


void RatKing::createAnimations() {
    addAnimation(IDLE_UP_LEFT, RAT_KING_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_UP, RAT_KING_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_UP_RIGHT, RAT_KING_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_RIGHT, RAT_KING_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN_RIGHT, RAT_KING_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN, RAT_KING_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN_LEFT, RAT_KING_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_LEFT, RAT_KING_IDLE_DOWN, 1, 10);

    addAnimation(MOVE_DOWN, RAT_KING_IDLE_DOWN, 1, 20);
    addAnimation(MOVE_UP, RAT_KING_IDLE_DOWN, 1, 20);
    addAnimation(MOVE_RIGHT, RAT_KING_IDLE_DOWN, 1, 20);
    addAnimation(MOVE_LEFT, RAT_KING_IDLE_DOWN, 1, 20);

    addAnimation(ATTACK_UP_LEFT, RAT_KING_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_UP, RAT_KING_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_UP_RIGHT, RAT_KING_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_RIGHT, RAT_KING_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_DOWN_RIGHT, RAT_KING_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_DOWN, RAT_KING_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_DOWN_LEFT, RAT_KING_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_LEFT, RAT_KING_IDLE_DOWN, 1, 10, false);
}

void RatKing::setDropTable()
{
    dropChance = 1.0;
    dropTable.push_back({ 1.0, ITEM_LONG_SWORD });
}
