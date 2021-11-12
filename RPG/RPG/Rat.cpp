#include "Rat.h"
#include "BasicMeleeAttack.h"

const int MAX_HEALTH = 9;
const int SPEED = 2;
const int DEX = 3;
const int AGI = 1;
const int STR = 5;
const int EXP_VALUE = 3;
const int GOLD_VALUE = 15;

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
    speed = SPEED;
    health = MAX_HEALTH;
    maxHealth = MAX_HEALTH;
    expValue = EXP_VALUE;
    dex = DEX;
    agi = AGI;
    str = STR;
    goldValue = GOLD_VALUE;
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

    addAnimation(MOVE_DOWN, RAT_MOVE_DOWN, 4, 40);
    addAnimation(MOVE_UP, RAT_MOVE_UP, 4, 40);
    addAnimation(MOVE_RIGHT, RAT_MOVE_RIGHT, 4, 40);
    addAnimation(MOVE_LEFT, RAT_MOVE_LEFT, 4, 40);

    addAnimation(ATTACK_UP_LEFT, RAT_ATTACK_UP, 2, 20, false);
    addAnimation(ATTACK_UP, RAT_ATTACK_UP, 2, 20, false);
    addAnimation(ATTACK_UP_RIGHT, RAT_ATTACK_UP, 2, 20, false);
    addAnimation(ATTACK_RIGHT, RAT_ATTACK_RIGHT, 2, 20, false);
    addAnimation(ATTACK_DOWN_RIGHT, RAT_ATTACK_DOWN, 2, 20, false);
    addAnimation(ATTACK_DOWN, RAT_ATTACK_DOWN, 2, 20, false);
    addAnimation(ATTACK_DOWN_LEFT, RAT_ATTACK_DOWN, 2, 20, false);
    addAnimation(ATTACK_LEFT, RAT_ATTACK_LEFT, 2, 20, false);
}

void Rat::setDropTable()
{
    dropChance = 0.055;
    //dropChance = 1.0;
    dropTable.push_back({ 0.17, ITEM_CLUB });
    dropTable.push_back({ 0.05, ITEM_SHORT_SWORD});
    dropTable.push_back({ 0.156, ITEM_RAG_BODY });
    dropTable.push_back({ 0.156, ITEM_RAG_BOOTS});
    dropTable.push_back({ 0.156, ITEM_RAG_GLOVES });
    dropTable.push_back({ 0.156, ITEM_RAG_HAT });
    dropTable.push_back({ 0.156, ITEM_RAG_PANTS });
}
