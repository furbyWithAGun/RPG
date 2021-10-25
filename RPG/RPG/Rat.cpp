#include "Rat.h"
#include "BasicMeleeAttack.h"

const int RAT_MAX_HEALTH = 10;
const int RAT_SPEED = 2;
const int RAT_DEX = 4;
const int RAT_AGI = 2;
const int RAT_STR = 5;
const int RAT_EXP_VALUE = 3;

Rat::Rat() : AiUnit() {
    init();
}
Rat::Rat(SaveObject saveObject, RpgTileGridScene* gameScene) : AiUnit(saveObject, gameScene)
{
    setDropTable();
    createAnimations();
}
Rat::Rat(int zoneId, int unitType) : AiUnit(zoneId, unitType) {
    init();
}

Rat::Rat(int zoneId, int unitType, RpgTileGridScene* gameScene) : AiUnit(zoneId, unitType, gameScene) {
    init(gameScene);
}

Rat::Rat(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY) : AiUnit(zoneId, unitType, gameScene, startX, startY) {
    init(gameScene);
}

void Rat::init() {
    speed = RAT_SPEED;
    health = RAT_MAX_HEALTH;
    maxHealth = RAT_MAX_HEALTH;
    expValue = RAT_EXP_VALUE;
    dex = RAT_DEX;
    agi = RAT_AGI;
    str = RAT_STR;
    goldValue = 15;
    equipedAttacks[MAIN_ATTACK] = new BasicMeleeAttack(MELEE, this); //potential memory leak
    activeAttack = equipedAttacks[MAIN_ATTACK];
    team = MONSTER_TEAM;
    setDropTable();
    createAnimations();
}

void Rat::init(RpgTileGridScene* gameScene) {
    init();
    //createAnimations();
    //resize(scene->tileWidth, scene->tileWidth);
}


void Rat::createAnimations() {
    addAnimation(IDLE_UP_LEFT,RAT_IDLE_UP, 1, 10);
    addAnimation(IDLE_UP,RAT_IDLE_UP, 1, 10);
    addAnimation(IDLE_UP_RIGHT, RAT_IDLE_UP, 1, 10);
    addAnimation(IDLE_RIGHT,RAT_IDLE_RIGHT, 1, 10);
    addAnimation(IDLE_DOWN_RIGHT,RAT_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN,RAT_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN_LEFT,RAT_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_LEFT,RAT_IDLE_LEFT, 1, 10);

    addAnimation(MOVE_DOWN,RAT_IDLE_DOWN, 1, 20);
    addAnimation(MOVE_UP,RAT_IDLE_UP, 1, 20);
    addAnimation(MOVE_RIGHT,RAT_IDLE_RIGHT, 1, 20);
    addAnimation(MOVE_LEFT,RAT_IDLE_LEFT, 1, 20);

    addAnimation(ATTACK_UP_LEFT, RAT_IDLE_UP, 1, 10, false);
    addAnimation(ATTACK_UP, RAT_IDLE_UP, 1, 10, false);
    addAnimation(ATTACK_UP_RIGHT, RAT_IDLE_UP, 1, 10, false);
    addAnimation(ATTACK_RIGHT, RAT_IDLE_RIGHT, 1, 10, false);
    addAnimation(ATTACK_DOWN_RIGHT,RAT_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_DOWN,RAT_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_DOWN_LEFT,RAT_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_LEFT, RAT_IDLE_LEFT, 1, 10, false);
}

void Rat::setDropTable()
{
    //dropChance = 0.03;
    dropChance = 1.0;
    dropTable.push_back({ 0.15, ITEM_CLUB });
    dropTable.push_back({ 0.02, ITEM_SHORT_SWORD});
    dropTable.push_back({ 0.166, ITEM_RAG_BODY });
    dropTable.push_back({ 0.166, ITEM_RAG_BOOTS});
    dropTable.push_back({ 0.166, ITEM_RAG_GLOVES });
    dropTable.push_back({ 0.166, ITEM_RAG_HAT });
    dropTable.push_back({ 0.166, ITEM_RAG_PANTS });
}
