#include "Player.h"
#include "RpgTileGridScene.h"
#include "BasicMeleeAttack.h"
#include "RpgOverWorldScene.h"

//stat constants
const int PLAYER_SPEED = 4;
const int PLAYER_DEX = 4;
const int PLAYER_AGI = 3;
const int PLAYER_MAX_HEALTH = 100;

//animation constants
const int NUM_PLAYER_IDLE_FRAMES = 1;
const int PLAYER_IDLE_ANIMATION_FRAME_LENGTH = 10;
const int NUM_PLAYER_MOVE_FRAMES = 4;
const int PLAYER_MOVE_ANIMATION_FRAME_LENGTH = 20;
const int NUM_PLAYER_ATTACK_FRAMES = 4;
const int PLAYER_ATTCK_ANIMATION_FRAME_LENGTH = 20;

Player::Player() : RpgUnit() {
    init();
}

Player::Player(SaveObject saveObject, RpgTileGridScene* gameScene) : RpgUnit(saveObject, gameScene)
{
    createAnimations();
}

Player::Player(int zoneId, int unitType) : RpgUnit(zoneId, unitType) {
    init();
    zone = 0;
}

Player::Player(int zoneId, int unitType, RpgTileGridScene* gameScene) : RpgUnit(zoneId, unitType, gameScene) {
    init(gameScene);
}

Player::Player(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY) : RpgUnit(zoneId, unitType, gameScene, startX, startY) {
    init(gameScene);
}

void Player::init() {
    isStatic = true;
    speed = PLAYER_SPEED;
    equipedAttacks[MAIN_ATTACK] = new BasicMeleeAttack(MELEE, this); //potential memory leak
    activeAttack = equipedAttacks[MAIN_ATTACK];
    maxHealth = PLAYER_MAX_HEALTH;
    health = PLAYER_MAX_HEALTH;
    dex = PLAYER_DEX;
    agi = PLAYER_AGI;
    team = PLAYER_TEAM;
    cameraFollowPlayer = true;
    createAnimations();
    lastXDelta = 0;
    lastXDelta2 = 0;
    lastXDelta3 = 0;
    lastYDelta = 0;
    lastYDelta2 = 0;
    lastYDelta3 = 0;
}

void Player::init(RpgTileGridScene* gameScene) {
    init();
    //createAnimations();
    //resize(scene->tileWidth, scene->tileWidth);
}

void Player::update() {
    RpgUnit::update();

    //centre on screen by changing scene x and y offsets
    if (cameraFollowPlayer)
    {
        //updateCamera();
    }
    
    //scene->yOffset = ypos - y;
    //scene->xOffset += xpos - x;
    //scene->yOffset += ypos - y;


}

void Player::updateCamera()
{
    int coords[2];
    int destCoords[2];
    scene->coordsFromTileIndex(tileLocation->x, tileLocation->y, coords);
    scene->coordsFromTileIndex(tileDestination->x, tileDestination->y, destCoords);
    int x = coords[0] + ((double)destCoords[0] - (double)coords[0]) * (1 - leftToMove);
    int y = coords[1] + ((double)destCoords[1] - (double)coords[1]) * (1 - leftToMove);
    int desiredCoords[2];
    scene->desiredPlayerDrawLocation(desiredCoords);
    if (leftToMove > 0)
    {
        double deltaEstimate = (double((double)speed / 100));
        deltaEstimate = deltaEstimate * scene->tileHeight;
        deltaEstimate = deltaEstimate * RPG_GAME_TICKS_PER_SECOND;
        //deltaEstimate = deltaEstimate * 60;
        deltaEstimate = deltaEstimate / scene->engine->getScreenRefreshRate();
        deltaEstimate = deltaEstimate * 0.55;

        if (leftToMove < 0.75)
        {
            int dfgdf = 23432;
        }
        if (tileDestination->y > tileLocation->y && desiredCoords[1] - y == 0)
        {
            scene->xOffset += desiredCoords[0] - x;
            scene->yOffset -= deltaEstimate;
        }
        else if (tileDestination->y > tileLocation->y) {
            scene->xOffset += desiredCoords[0] - x;
            scene->yOffset += desiredCoords[1] - y;
        }
        if (tileDestination->y < tileLocation->y && desiredCoords[1] - y == 0)
        {
            scene->xOffset += desiredCoords[0] - x;
            scene->yOffset += deltaEstimate;
        }
        else if (tileDestination->y < tileLocation->y) {
            scene->xOffset += desiredCoords[0] - x;
            scene->yOffset += desiredCoords[1] - y;
        }
        if (tileDestination->x > tileLocation->x && desiredCoords[0] - x == 0)
        {
            scene->xOffset -= deltaEstimate;
            scene->yOffset += desiredCoords[1] - y;
        }
        else if (tileDestination->x > tileLocation->x) {
            scene->xOffset += desiredCoords[0] - x;
            scene->yOffset += desiredCoords[1] - y;
        }
        if (tileDestination->x < tileLocation->x && desiredCoords[0] - x == 0)
        {
            scene->xOffset += deltaEstimate;
            scene->yOffset += desiredCoords[1] - y;
        }
        else if (tileDestination->x < tileLocation->x) {
            scene->xOffset += desiredCoords[0] - x;
            scene->yOffset += desiredCoords[1] - y;
        }
    }
    else {
        scene->xOffset += desiredCoords[0] - x;
        scene->yOffset += desiredCoords[1] - y;
    }
    //scene->xOffset += desiredCoords[0] - x;
    //scene->yOffset += desiredCoords[1] - y;
    //xpos = desiredCoords[0];
    //ypos = desiredCoords[1];
    updateCoords();
}

void Player::faceMouseDirection(int x, int y) {
    if (x < xpos && y < ypos)
    {
        directionFacing = UP_LEFT;
    }
    else if (x >= xpos && x <= xpos + width && y < ypos) {
        directionFacing = UP;
    }
    else if (x > xpos + width && y < ypos) {
        directionFacing = UP_RIGHT;
    }
    else if (x > xpos + width && y > ypos && y < ypos + height) {
        directionFacing = RIGHT;
    }
    else if (x > xpos + width && y > ypos + height) {
        directionFacing = DOWN_RIGHT;
    }
    else if (x >= xpos && x <= xpos + width && y > ypos + height) {
        directionFacing = DOWN;
    }
    else if (x < xpos && y > ypos + height) {
        directionFacing = DOWN_LEFT;
    }
    else if (x < xpos && y > ypos && y < ypos + height) {
        directionFacing = LEFT;
    }
}

void Player::portalTo(int zoneId, int x, int y)
{
    Unit::portalTo(zoneId, x, y);
    scene->loadZone(zone);
}

void Player::death()
{
    /*RpgUnit::death();
    scene->engine->addScene(OVERWORLD, new RpgOverWorldScene(scene->engine));
    scene->engine->setNextScene(MAIN_MENU_SCENE);
    scene->endScene();*/
    combatExperience = combatExperienceLastLevel;
    inventory.clear();
    for (int i = BARE_HANDS + 1; i != NUM_EQUIPMENT_SLOTS; i++)
    {
        scene->player->equippedItems[i] = nullptr;
    }
    health = maxHealth;
    gold = 0;
    foodEffects.clear();
    scene->menus[INVENTORY_MENU]->rebuildElements();
    scene->menus[INVENTORY_MENU]->update();
    portalTo(1, 6, 6);
}

void Player::draw()
{
    int desiredCoords[2];
    scene->desiredPlayerDrawLocation(desiredCoords);
    xpos = desiredCoords[0] - scene->tileWidth;
    ypos = desiredCoords[1] - scene->tileHeight;
    currentState->updateAnimation();
    Unit::drawNoCoordUpdate();
    drawHealth();
}

//private methods
void Player::createAnimations() {
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

