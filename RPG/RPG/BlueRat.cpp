#include "BlueRat.h"
#include "BasicMeleeAttack.h"

const int BLUE_RAT_MAX_HEALTH = 70;
const int BLUE_RAT_SPEED = 1;
const int BLUE_RAT_DEX = 12;
const int BLUE_RAT_AGI = 8;
const int BLUE_RAT_STR = 10;
const int BLUE_RAT_EXP_VALUE = 50;

BlueRat::BlueRat() : AiUnit() {
    init();
}
BlueRat::BlueRat(int zoneId, int unitType) : AiUnit(zoneId, unitType) {
    init();
}

BlueRat::BlueRat(int zoneId, int unitType, TileGridScene* gameScene) : AiUnit(zoneId, unitType, gameScene) {
    init(gameScene);
}

BlueRat::BlueRat(int zoneId, int unitType, TileGridScene* gameScene, int startX, int startY) : AiUnit(zoneId, unitType, gameScene, startX, startY) {
    init(gameScene);
}

void BlueRat::init() {
    speed = BLUE_RAT_SPEED;
    health = BLUE_RAT_MAX_HEALTH;
    maxHealth = BLUE_RAT_MAX_HEALTH;
    expValue = BLUE_RAT_EXP_VALUE;
    dex = BLUE_RAT_DEX;
    agi = BLUE_RAT_AGI;
    str = BLUE_RAT_STR;
    equipedAttacks[MAIN_ATTACK] = new BasicMeleeAttack(MELEE, this); //potential memory leak
    activeAttack = equipedAttacks[MAIN_ATTACK];
    team = MONSTER_TEAM;
    goldValue = 45;
    setDropTable();
}

void BlueRat::init(TileGridScene* gameScene) {
    init();
    createAnimations();
    //resize(scene->tileWidth, scene->tileWidth);
}


void BlueRat::createAnimations() {
    addAnimation(IDLE_UP_LEFT, BLUE_RAT_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_UP, BLUE_RAT_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_UP_RIGHT, BLUE_RAT_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_RIGHT, BLUE_RAT_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN_RIGHT, BLUE_RAT_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN, BLUE_RAT_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN_LEFT, BLUE_RAT_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_LEFT, BLUE_RAT_IDLE_DOWN, 1, 10);

    addAnimation(MOVE_DOWN, BLUE_RAT_IDLE_DOWN, 1, 20);
    addAnimation(MOVE_UP, BLUE_RAT_IDLE_DOWN, 1, 20);
    addAnimation(MOVE_RIGHT, BLUE_RAT_IDLE_DOWN, 1, 20);
    addAnimation(MOVE_LEFT, BLUE_RAT_IDLE_DOWN, 1, 20);

    addAnimation(ATTACK_UP_LEFT, BLUE_RAT_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_UP, BLUE_RAT_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_UP_RIGHT, BLUE_RAT_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_RIGHT, BLUE_RAT_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_DOWN_RIGHT, BLUE_RAT_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_DOWN, BLUE_RAT_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_DOWN_LEFT, BLUE_RAT_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_LEFT, BLUE_RAT_IDLE_DOWN, 1, 10, false);
}

void BlueRat::setDropTable()
{
    dropChance = 0.10;
    dropTable.push_back({ 0.14, ITEM_SHORT_SWORD });
    dropTable.push_back({ 0.05, ITEM_MACE});
    dropTable.push_back({ 0.01, ITEM_LONG_SWORD });
    dropTable.push_back({ 0.15, ITEM_RAG_BODY });
    dropTable.push_back({ 0.15, ITEM_RAG_BOOTS });
    dropTable.push_back({ 0.15, ITEM_RAG_GLOVES });
    dropTable.push_back({ 0.15, ITEM_RAG_HAT });
    dropTable.push_back({ 0.15, ITEM_RAG_PANTS });
    dropTable.push_back({ 0.01, ITEM_LINEN_BODY });
    dropTable.push_back({ 0.01, ITEM_LINEN_BOOTS });
    dropTable.push_back({ 0.01, ITEM_LINEN_GLOVES });
    dropTable.push_back({ 0.01, ITEM_LINEN_HAT });
    dropTable.push_back({ 0.01, ITEM_LINEN_PANTS });
}
