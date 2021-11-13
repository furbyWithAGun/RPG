#include "RatKing.h"
#include "BasicMeleeAttack.h"
#include "RpgTileGridScene.h"

const int MAX_HEALTH = 175;
const int SPEED = 4;
const int DEX = 25;
const int AGI = 15;
const int STR = 25;
const int EXP_VALUE = 300;
const int GOLD_VALUE = 1000;

RatKing::RatKing() : AiUnit() {
    init();
}
RatKing::RatKing(SaveObject saveObject, RpgTileGridScene* gameScene) : AiUnit(saveObject, gameScene)
{
    setDropTable();
    createAnimations();
}
RatKing::RatKing(int zoneId, int unitType) : AiUnit(zoneId, unitType) {
    init();
}

RatKing::RatKing(int zoneId, int unitType, RpgTileGridScene* gameScene) : AiUnit(zoneId, unitType, gameScene) {
    init(gameScene);
}

RatKing::RatKing(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY) : AiUnit(zoneId, unitType, gameScene, startX, startY) {
    init(gameScene);
}

void RatKing::init() {
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

void RatKing::init(RpgTileGridScene* gameScene) {
    init();
    //createAnimations();
    //resize(scene->tileWidth, scene->tileWidth);
}


void RatKing::createAnimations() {
    addAnimation(IDLE_UP_LEFT, RAT_KING_IDLE_UP, 1, 10);
    addAnimation(IDLE_UP, RAT_KING_IDLE_UP, 1, 10);
    addAnimation(IDLE_UP_RIGHT, RAT_KING_IDLE_UP, 1, 10);
    addAnimation(IDLE_RIGHT, RAT_KING_IDLE_RIGHT, 1, 10);
    addAnimation(IDLE_DOWN_RIGHT, RAT_KING_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN, RAT_KING_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN_LEFT, RAT_KING_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_LEFT, RAT_KING_IDLE_LEFT, 1, 10);

    addAnimation(MOVE_DOWN, RAT_KING_MOVE_DOWN, 4, 40);
    addAnimation(MOVE_UP, RAT_KING_MOVE_UP, 4, 40);
    addAnimation(MOVE_RIGHT, RAT_KING_MOVE_RIGHT, 4, 40);
    addAnimation(MOVE_LEFT, RAT_KING_MOVE_LEFT, 4, 40);

    addAnimation(ATTACK_UP_LEFT, RAT_KING_ATTACK_UP, 4, 5, false);
    addAnimation(ATTACK_UP, RAT_KING_ATTACK_UP, 4, 5, false);
    addAnimation(ATTACK_UP_RIGHT, RAT_KING_ATTACK_UP, 4, 5, false);
    addAnimation(ATTACK_RIGHT, RAT_KING_ATTACK_RIGHT, 2, 5, false);
    addAnimation(ATTACK_DOWN_RIGHT, RAT_KING_ATTACK_DOWN, 4, 5, false);
    addAnimation(ATTACK_DOWN, RAT_KING_ATTACK_DOWN, 4, 5, false);
    addAnimation(ATTACK_DOWN_LEFT, RAT_KING_ATTACK_DOWN, 4, 5, false);
    addAnimation(ATTACK_LEFT, RAT_KING_ATTACK_LEFT, 2, 5, false);
}

void RatKing::setDropTable()
{
    dropChance = 1.0;
    dropTable.push_back({ 1.0, ITEM_LONG_SWORD });
}

void RatKing::death()
{
    RpgUnit::death();
}
