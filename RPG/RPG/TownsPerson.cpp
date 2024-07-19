#include "TownsPerson.h"
#include "BasicMeleeAttack.h"

const int MAX_HEALTH = 60;
const int SPEED = 8;
const int DEX = 2;
const int AGI = 2;
const int EXP_VALUE = 3;

//animation constants
const int NUM_PLAYER_IDLE_FRAMES = 1;
const int PLAYER_IDLE_ANIMATION_FRAME_LENGTH = 10;
const int NUM_PLAYER_MOVE_FRAMES = 4;
const int PLAYER_MOVE_ANIMATION_FRAME_LENGTH = 20;
const int NUM_PLAYER_ATTACK_FRAMES = 4;
const int PLAYER_ATTCK_ANIMATION_FRAME_LENGTH = 20;

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
    doesRandomMovement = true;
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

void TownsPerson::convertToSoldier()
{
    addAnimation(IDLE_UP_LEFT, PLAYER_IDLE_UP_LEFT_SHEET, NUM_PLAYER_IDLE_FRAMES, PLAYER_IDLE_ANIMATION_FRAME_LENGTH);
    addAnimation(IDLE_UP, PLAYER_IDLE_UP_SHEET, NUM_PLAYER_IDLE_FRAMES, PLAYER_IDLE_ANIMATION_FRAME_LENGTH);
    addAnimation(IDLE_UP_RIGHT, PLAYER_IDLE_UP_RIGHT_SHEET, NUM_PLAYER_IDLE_FRAMES, PLAYER_IDLE_ANIMATION_FRAME_LENGTH);
    addAnimation(IDLE_RIGHT, PLAYER_IDLE_RIGHT_SHEET, NUM_PLAYER_IDLE_FRAMES, PLAYER_IDLE_ANIMATION_FRAME_LENGTH);
    addAnimation(IDLE_DOWN_RIGHT, PLAYER_IDLE_DOWN_RIGHT_SHEET, NUM_PLAYER_IDLE_FRAMES, PLAYER_IDLE_ANIMATION_FRAME_LENGTH);
    addAnimation(IDLE_DOWN, PLAYER_IDLE_DOWN_SHEET, NUM_PLAYER_IDLE_FRAMES, PLAYER_IDLE_ANIMATION_FRAME_LENGTH);
    addAnimation(IDLE_DOWN_LEFT, PLAYER_IDLE_DOWN_LEFT_SHEET, NUM_PLAYER_IDLE_FRAMES, PLAYER_IDLE_ANIMATION_FRAME_LENGTH);
    addAnimation(IDLE_LEFT, PLAYER_IDLE_LEFT_SHEET, NUM_PLAYER_IDLE_FRAMES, PLAYER_IDLE_ANIMATION_FRAME_LENGTH);

    addAnimation(MOVE_DOWN, PLAYER_MOVE_DOWN_SHEET, NUM_PLAYER_MOVE_FRAMES, PLAYER_MOVE_ANIMATION_FRAME_LENGTH);
    addAnimation(MOVE_UP, PLAYER_MOVE_UP_SHEET, NUM_PLAYER_MOVE_FRAMES, PLAYER_MOVE_ANIMATION_FRAME_LENGTH);
    addAnimation(MOVE_RIGHT, PLAYER_MOVE_RIGHT_SHEET, NUM_PLAYER_MOVE_FRAMES, PLAYER_MOVE_ANIMATION_FRAME_LENGTH);
    addAnimation(MOVE_LEFT, PLAYER_MOVE_LEFT_SHEET, NUM_PLAYER_MOVE_FRAMES, PLAYER_MOVE_ANIMATION_FRAME_LENGTH);

    addAnimation(ATTACK_UP_LEFT, BASIC_MELEE_ATTACK_UP_SHEET, NUM_PLAYER_ATTACK_FRAMES, PLAYER_ATTCK_ANIMATION_FRAME_LENGTH, false);
    addAnimation(ATTACK_UP, BASIC_MELEE_ATTACK_UP_SHEET, NUM_PLAYER_ATTACK_FRAMES, PLAYER_ATTCK_ANIMATION_FRAME_LENGTH, false);
    addAnimation(ATTACK_UP_RIGHT, BASIC_MELEE_ATTACK_UP_SHEET, NUM_PLAYER_ATTACK_FRAMES, PLAYER_ATTCK_ANIMATION_FRAME_LENGTH, false);
    addAnimation(ATTACK_RIGHT, BASIC_MELEE_ATTACK_RIGHT_SHEET, NUM_PLAYER_ATTACK_FRAMES, PLAYER_ATTCK_ANIMATION_FRAME_LENGTH, false);
    addAnimation(ATTACK_DOWN_RIGHT, BASIC_MELEE_ATTACK_DOWN_SHEET, NUM_PLAYER_ATTACK_FRAMES, PLAYER_ATTCK_ANIMATION_FRAME_LENGTH, false);
    addAnimation(ATTACK_DOWN, BASIC_MELEE_ATTACK_DOWN_SHEET, NUM_PLAYER_ATTACK_FRAMES, PLAYER_ATTCK_ANIMATION_FRAME_LENGTH, false);
    addAnimation(ATTACK_DOWN_LEFT, BASIC_MELEE_ATTACK_DOWN_SHEET, NUM_PLAYER_ATTACK_FRAMES, PLAYER_ATTCK_ANIMATION_FRAME_LENGTH, false);
    addAnimation(ATTACK_LEFT, BASIC_MELEE_ATTACK_LEFT_SHEET, NUM_PLAYER_ATTACK_FRAMES, PLAYER_ATTCK_ANIMATION_FRAME_LENGTH, false);
}
