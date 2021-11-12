#include "WhiteRat.h"
#include "BasicMeleeAttack.h"

const int MAX_HEALTH = 50;
const int SPEED = 2;
const int DEX = 15;
const int AGI = 8;
const int STR = 15;
const int EXP_VALUE = 10;
const int GOLD_VALUE = 45;

WhiteRat::WhiteRat() : AiUnit() {
    init();
}
WhiteRat::WhiteRat(SaveObject saveObject, RpgTileGridScene* gameScene) : AiUnit(saveObject, gameScene)
{
    setDropTable();
    createAnimations();
}
WhiteRat::WhiteRat(int zoneId, int unitType) : AiUnit(zoneId, unitType) {
    init();
}

WhiteRat::WhiteRat(int zoneId, int unitType, RpgTileGridScene* gameScene) : AiUnit(zoneId, unitType, gameScene) {
    init(gameScene);
}

WhiteRat::WhiteRat(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY) : AiUnit(zoneId, unitType, gameScene, startX, startY) {
    init(gameScene);
}

void WhiteRat::init() {
    speed = SPEED;
    health = MAX_HEALTH;
    maxHealth = MAX_HEALTH;
    expValue = EXP_VALUE;
    dex = DEX;
    agi = AGI;
    str = STR;
    equipedAttacks[MAIN_ATTACK] = new BasicMeleeAttack(MELEE, this); //potential memory leak
    activeAttack = equipedAttacks[MAIN_ATTACK];
    team = MONSTER_TEAM;
    goldValue = GOLD_VALUE;
    setDropTable();
    createAnimations();
}

void WhiteRat::init(RpgTileGridScene* gameScene) {
    init();
    //createAnimations();
    //resize(scene->tileWidth, scene->tileWidth);
}


void WhiteRat::createAnimations() {
    addAnimation(IDLE_UP_LEFT, WHITE_RAT_IDLE_UP, 1, 10);
    addAnimation(IDLE_UP, WHITE_RAT_IDLE_UP, 1, 10);
    addAnimation(IDLE_UP_RIGHT, WHITE_RAT_IDLE_UP, 1, 10);
    addAnimation(IDLE_RIGHT, WHITE_RAT_IDLE_RIGHT, 1, 10);
    addAnimation(IDLE_DOWN_RIGHT, WHITE_RAT_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN, WHITE_RAT_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN_LEFT, WHITE_RAT_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_LEFT, WHITE_RAT_IDLE_LEFT, 1, 10);

    addAnimation(MOVE_DOWN, WHITE_RAT_MOVE_DOWN, 4, 10);
    addAnimation(MOVE_UP, WHITE_RAT_MOVE_UP, 4, 10);
    addAnimation(MOVE_RIGHT, WHITE_RAT_MOVE_RIGHT, 4, 10);
    addAnimation(MOVE_LEFT, WHITE_RAT_MOVE_LEFT, 4, 10);

    addAnimation(ATTACK_UP_LEFT, WHITE_RAT_ATTACK_UP, 2, 10, false);
    addAnimation(ATTACK_UP, WHITE_RAT_ATTACK_UP, 2, 10, false);
    addAnimation(ATTACK_UP_RIGHT, WHITE_RAT_ATTACK_UP, 2, 10, false);
    addAnimation(ATTACK_RIGHT, WHITE_RAT_ATTACK_RIGHT, 2, 10, false);
    addAnimation(ATTACK_DOWN_RIGHT, WHITE_RAT_ATTACK_DOWN, 2, 10, false);
    addAnimation(ATTACK_DOWN, WHITE_RAT_ATTACK_DOWN, 2, 10, false);
    addAnimation(ATTACK_DOWN_LEFT, WHITE_RAT_ATTACK_DOWN, 2, 10, false);
    addAnimation(ATTACK_LEFT, WHITE_RAT_ATTACK_LEFT, 2, 10, false);
}

void WhiteRat::setDropTable()
{
    dropChance = 0.22;
    dropTable.push_back({ 0.15, ITEM_SHORT_SWORD });
    dropTable.push_back({ 0.06, ITEM_MACE});
    dropTable.push_back({ 0.04, ITEM_LONG_SWORD });
    dropTable.push_back({ 0.12, ITEM_RAG_BODY });
    dropTable.push_back({ 0.12, ITEM_RAG_BOOTS });
    dropTable.push_back({ 0.12, ITEM_RAG_GLOVES });
    dropTable.push_back({ 0.12, ITEM_RAG_HAT });
    dropTable.push_back({ 0.12, ITEM_RAG_PANTS });
    dropTable.push_back({ 0.03, ITEM_LINEN_BODY });
    dropTable.push_back({ 0.03, ITEM_LINEN_BOOTS });
    dropTable.push_back({ 0.03, ITEM_LINEN_GLOVES });
    dropTable.push_back({ 0.03, ITEM_LINEN_HAT });
    dropTable.push_back({ 0.03, ITEM_LINEN_PANTS });
}
