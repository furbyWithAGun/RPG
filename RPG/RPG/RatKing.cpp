#include "RatKing.h"
#include "BasicMeleeAttack.h"
#include "RpgTileGridScene.h"

const int MAX_HEALTH = 200;
const int SPEED = 8;
const int DEX = 30;
const int AGI = 17;
const int STR = 27;
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
    setAttributeLevel(UNIT_STAT_SPEED, SPEED);
    health = MAX_HEALTH;
    setAttributeLevel(UNIT_STAT_MAX_HEALTH, MAX_HEALTH);
    expValue = EXP_VALUE;
    goldValue = GOLD_VALUE;
    setAttributeLevel(UNIT_STAT_DEX, DEX);
    setAttributeLevel(UNIT_STAT_AGI, AGI);
    setAttributeLevel(UNIT_STAT_STR, STR);
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

    DropTable dropTable = DropTable();
    dropTable.chance = 1.0;
    dropTable.items.push_back({ 0.04, ITEM_SHORT_SWORD });
    dropTable.items.push_back({ 0.1, ITEM_MACE });
    dropTable.items.push_back({ 0.1, ITEM_LONG_SWORD });
    dropTable.items.push_back({ 0.03, ITEM_RAG_BODY });
    dropTable.items.push_back({ 0.03, ITEM_RAG_BOOTS });
    dropTable.items.push_back({ 0.03, ITEM_RAG_GLOVES });
    dropTable.items.push_back({ 0.03, ITEM_RAG_HAT });
    dropTable.items.push_back({ 0.03, ITEM_RAG_PANTS });
    dropTable.items.push_back({ 0.09, ITEM_LINEN_BODY });
    dropTable.items.push_back({ 0.09, ITEM_LINEN_BOOTS });
    dropTable.items.push_back({ 0.09, ITEM_LINEN_GLOVES });
    dropTable.items.push_back({ 0.09, ITEM_LINEN_HAT });
    dropTable.items.push_back({ 0.09, ITEM_LINEN_PANTS });
    dropTable.items.push_back({ 0.03, ITEM_LEATHER_BODY });
    dropTable.items.push_back({ 0.03, ITEM_LEATHER_BOOTS });
    dropTable.items.push_back({ 0.03, ITEM_LEATHER_GLOVES });
    dropTable.items.push_back({ 0.03, ITEM_LEATHER_HAT });
    dropTable.items.push_back({ 0.03, ITEM_LEATHER_PANTS });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_BODY });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_BOOTS });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_GLOVES });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_HELM });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_PANTS });
    dropTables.push_back(dropTable);

    dropTable = DropTable();
    dropTable.chance = .50;
    dropTable.items.push_back({ 0.04, ITEM_SHORT_SWORD });
    dropTable.items.push_back({ 0.1, ITEM_MACE });
    dropTable.items.push_back({ 0.1, ITEM_LONG_SWORD });
    dropTable.items.push_back({ 0.03, ITEM_RAG_BODY });
    dropTable.items.push_back({ 0.03, ITEM_RAG_BOOTS });
    dropTable.items.push_back({ 0.03, ITEM_RAG_GLOVES });
    dropTable.items.push_back({ 0.03, ITEM_RAG_HAT });
    dropTable.items.push_back({ 0.03, ITEM_RAG_PANTS });
    dropTable.items.push_back({ 0.09, ITEM_LINEN_BODY });
    dropTable.items.push_back({ 0.09, ITEM_LINEN_BOOTS });
    dropTable.items.push_back({ 0.09, ITEM_LINEN_GLOVES });
    dropTable.items.push_back({ 0.09, ITEM_LINEN_HAT });
    dropTable.items.push_back({ 0.09, ITEM_LINEN_PANTS });
    dropTable.items.push_back({ 0.03, ITEM_LEATHER_BODY });
    dropTable.items.push_back({ 0.03, ITEM_LEATHER_BOOTS });
    dropTable.items.push_back({ 0.03, ITEM_LEATHER_GLOVES });
    dropTable.items.push_back({ 0.03, ITEM_LEATHER_HAT });
    dropTable.items.push_back({ 0.03, ITEM_LEATHER_PANTS });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_BODY });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_BOOTS });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_GLOVES });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_HELM });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_PANTS });
    dropTables.push_back(dropTable);

    dropTable = DropTable();
    dropTable.chance = 0.33;
    dropTable.items.push_back({ 0.04, ITEM_SHORT_SWORD });
    dropTable.items.push_back({ 0.1, ITEM_MACE });
    dropTable.items.push_back({ 0.1, ITEM_LONG_SWORD });
    dropTable.items.push_back({ 0.03, ITEM_RAG_BODY });
    dropTable.items.push_back({ 0.03, ITEM_RAG_BOOTS });
    dropTable.items.push_back({ 0.03, ITEM_RAG_GLOVES });
    dropTable.items.push_back({ 0.03, ITEM_RAG_HAT });
    dropTable.items.push_back({ 0.03, ITEM_RAG_PANTS });
    dropTable.items.push_back({ 0.09, ITEM_LINEN_BODY });
    dropTable.items.push_back({ 0.09, ITEM_LINEN_BOOTS });
    dropTable.items.push_back({ 0.09, ITEM_LINEN_GLOVES });
    dropTable.items.push_back({ 0.09, ITEM_LINEN_HAT });
    dropTable.items.push_back({ 0.09, ITEM_LINEN_PANTS });
    dropTable.items.push_back({ 0.03, ITEM_LEATHER_BODY });
    dropTable.items.push_back({ 0.03, ITEM_LEATHER_BOOTS });
    dropTable.items.push_back({ 0.03, ITEM_LEATHER_GLOVES });
    dropTable.items.push_back({ 0.03, ITEM_LEATHER_HAT });
    dropTable.items.push_back({ 0.03, ITEM_LEATHER_PANTS });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_BODY });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_BOOTS });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_GLOVES });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_HELM });
    dropTable.items.push_back({ 0.002, ITEM_BRONZE_PANTS });
    dropTables.push_back(dropTable);
}

void RatKing::death()
{
    RpgUnit::death();
}
