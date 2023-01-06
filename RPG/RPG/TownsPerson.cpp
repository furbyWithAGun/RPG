#include "TownsPerson.h"
#include "BasicMeleeAttack.h"

const int MAX_HEALTH = 60;
const int SPEED = 8;
const int DEX = 2;
const int AGI = 2;
const int EXP_VALUE = 3;

TownsPerson::TownsPerson() : AiUnit() {
    init();
}
TownsPerson::TownsPerson(SaveObject saveObject, RpgTileGridScene* gameScene) : AiUnit(saveObject, gameScene)
{
    setDropTable();
    createAnimations();
}
TownsPerson::TownsPerson(int zoneId, int unitType) : AiUnit(zoneId, unitType) {
    init();
}

TownsPerson::TownsPerson(int zoneId, int unitType, RpgTileGridScene* gameScene) : AiUnit(zoneId, unitType, gameScene) {
    init(gameScene);
}

TownsPerson::TownsPerson(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY) : AiUnit(zoneId, unitType, gameScene, startX, startY) {
    init(gameScene);
}

void TownsPerson::init() {
    equipedAttacks[MAIN_ATTACK] = new BasicMeleeAttack(MELEE, this); //potential memory leak
    activeAttack = equipedAttacks[MAIN_ATTACK];
    team = PLAYER_TEAM;
    createAnimations();
}

void TownsPerson::init(RpgTileGridScene* gameScene) {
    init();
    //createAnimations();
    //resize(scene->tileWidth, scene->tileWidth);
    doesRandomMovement = false;
    health = MAX_HEALTH;
    setAttributeLevel(UNIT_STAT_MAX_HEALTH, MAX_HEALTH);
    setAttributeLevel(UNIT_STAT_SPEED, SPEED);
    setAttributeLevel(UNIT_STAT_DEX, DEX);
    setAttributeLevel(UNIT_STAT_AGI, AGI);
}


void TownsPerson::createAnimations() {
    addAnimation(IDLE_UP_LEFT, MAC_WIZ_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_UP, MAC_WIZ_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_UP_RIGHT, MAC_WIZ_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_RIGHT, MAC_WIZ_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN_RIGHT, MAC_WIZ_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN, MAC_WIZ_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_DOWN_LEFT, MAC_WIZ_IDLE_DOWN, 1, 10);
    addAnimation(IDLE_LEFT, MAC_WIZ_IDLE_DOWN, 1, 10);

    addAnimation(MOVE_DOWN, MAC_WIZ_IDLE_DOWN, 1, 20);
    addAnimation(MOVE_UP, MAC_WIZ_IDLE_DOWN, 1, 20);
    addAnimation(MOVE_RIGHT, MAC_WIZ_IDLE_DOWN, 1, 20);
    addAnimation(MOVE_LEFT, MAC_WIZ_IDLE_DOWN, 1, 20);

    addAnimation(ATTACK_UP_LEFT, MAC_WIZ_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_UP, MAC_WIZ_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_UP_RIGHT, MAC_WIZ_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_RIGHT, MAC_WIZ_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_DOWN_RIGHT, MAC_WIZ_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_DOWN, MAC_WIZ_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_DOWN_LEFT, MAC_WIZ_IDLE_DOWN, 1, 10, false);
    addAnimation(ATTACK_LEFT, MAC_WIZ_IDLE_DOWN, 1, 10, false);
}