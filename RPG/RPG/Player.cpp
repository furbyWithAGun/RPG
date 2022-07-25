#include "Player.h"
#include "RpgTileGridScene.h"
#include "BasicMeleeAttack.h"
#include "RpgOverWorldScene.h"

//stat constants
//const int PLAYER_SPEED = 4;
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
    isStatic = true;
    isPlayer = true;
    cameraFollowPlayer = true;
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
    isPlayer = true;
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

//void Player::updateCamera()
//{
//    double coords[2];
//    double destCoords[2];
//    scene->coordsFromTileIndex(tileLocationBuffer->x, tileLocationBuffer->y, coords);
//    scene->coordsFromTileIndex(tileDestinationBuffer->x, tileDestinationBuffer->y, destCoords);
//    double x = coords[0] + ((double)destCoords[0] - (double)coords[0]) * (1 - leftToMoveBuffer);
//    double y = coords[1] + ((double)destCoords[1] - (double)coords[1]) * (1 - leftToMoveBuffer);
//    double desiredCoords[2];
//    scene->desiredPlayerDrawLocation(desiredCoords);
//    
//    int destXOffset = desiredCoords[0] - scene->mainCanvasStartX - tileDestinationBuffer->x * scene->tileWidth;
//    int destYOffset = desiredCoords[1] - tileDestinationBuffer->y * scene->tileHeight;
//
//    int prevxoffset = scene->xOffset;
//    int prevyoffset = scene->yOffset;
//    scene->xOffset += desiredCoords[0] - x;
//    scene->yOffset += desiredCoords[1] - y;
//
//    int basexoff = scene->xOffset;
//    int baseyoff = scene->yOffset;
//    
//    if (leftToMoveBuffer > 0)
//    {
//        if (leftToMoveBuffer < 0.0001)
//        {
//            int dfgdfgdfg = 345345;
//        }
//        if (prevxoffset > scene->xOffset)
//        {
//            int hh = scene->xOffset - prevxoffset;
//            int c = 23436;
//        }
//
//        double movementPerTick = ((double)speed / 100);
//        double timeSinceLastTick = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() - scene->getLastTickTimeStampBuffer();
//        if (timeSinceLastTick > scene->engine->tickDelay)
//        {
//            //timeSinceLastTick = scene->engine->tickDelay;
//        }
//        double lastLogictick = scene->getLastTickTimeStampBuffer();
//        double newtick = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
//        double timeRatioSinceLastTick = timeSinceLastTick / scene->engine->tickDelay;
//        double impliedMovement = movementPerTick * timeRatioSinceLastTick;
//        double remainderMovement = 0;
//        
//        //impliedMovement = 0;
//        if (impliedMovement > 0)
//        {
//            int f = 45757567;
//        }
//        if (impliedMovement > leftToMoveBuffer) {
//            int dfgdgdf = 234234;
//        }
//
//        if (tileDestinationBuffer->x > tileLocationBuffer->x) //moving right
//        {
//            if (impliedMovement > leftToMoveBuffer && (!movingRight || !scene->isTilePassableIgnoreUnit(zone, tileDestinationBuffer->x + 1, tileDestinationBuffer->y, this)))
//            {
//                remainderMovement = impliedMovement - leftToMoveBuffer;
//                impliedMovement = leftToMoveBuffer;
//                scene->xOffset = destXOffset;
//                // TESTING START
//                if (prevxoffset > scene->xOffset)
//                {
//                    int hh = scene->xOffset - prevxoffset;
//                    int c = 23436;
//                }
//                //std::cout << scene->xOffset - prevxoffset;
//                //std::cout << " left to move: ";
//                //std::cout << leftToMoveBuffer;
//                //std::cout << " implied movement: ";
//                //std::cout << impliedMovement;
//                //std::cout << " time since last tick: ";
//                //std::cout << timeSinceLastTick;
//                //std::cout << "\n";
//                if (scene->xOffset - prevxoffset > 5 || scene->xOffset - prevxoffset < -5)
//                {
//                    int dfgdfg = 4564;
//                }
//                // TESTING END
//            }
//            else {
//                scene->xOffset -= impliedMovement * scene->tileWidth;
//                // TESTING START
//                if (prevxoffset > scene->xOffset)
//                {
//                    int hh = scene->xOffset - prevxoffset;
//                    int c = 23436;
//                }
//                //std::cout << scene->xOffset - prevxoffset;
//                //std::cout << " left to move: ";
//                //std::cout << leftToMoveBuffer;
//                //std::cout << " implied movement: ";
//                //std::cout << impliedMovement;
//                //std::cout << " time since last tick: ";
//                //std::cout << timeSinceLastTick;
//                //std::cout << "\n";
//                if (scene->xOffset - prevxoffset > 5 || scene->xOffset - prevxoffset < -5)
//                {
//                    int dfgdfg = 4564;
//                }
//                // TESTING END
//                if (scene->xOffset < destXOffset && (!movingRight || !scene->isTilePassableIgnoreUnit(zone, tileDestinationBuffer->x + 1, tileDestinationBuffer->y, this)))
//                {
//                    scene->xOffset = destXOffset;
//                    // TESTING START
//                    if (prevxoffset > scene->xOffset)
//                    {
//                        int hh = scene->xOffset - prevxoffset;
//                        int c = 23436;
//                    }
//                    /*std::cout << scene->xOffset - prevxoffset;
//                    std::cout << " left to move: ";
//                    std::cout << leftToMoveBuffer;
//                    std::cout << " implied movement: ";
//                    std::cout << impliedMovement;
//                    std::cout << " time since last tick: ";
//                    std::cout << timeSinceLastTick;
//                    std::cout << "\n";*/
//                    if (scene->xOffset - prevxoffset > 5 || scene->xOffset - prevxoffset < -5)
//                    {
//                        int dfgdfg = 4564;
//                    }
//                    // TESTING END
//                }
//            }
//        }
//        else if (tileDestinationBuffer->x < tileLocationBuffer->x) { // moving left
//            if (impliedMovement > leftToMoveBuffer && (!movingLeft || !scene->isTilePassableIgnoreUnit(zone, tileDestinationBuffer->x - 1, tileDestinationBuffer->y, this)))
//            {
//                remainderMovement = impliedMovement - leftToMoveBuffer;
//                impliedMovement = leftToMoveBuffer;
//                scene->xOffset = destXOffset;
//            }
//            else {
//                scene->xOffset += impliedMovement * scene->tileWidth;
//                if (scene->xOffset > destXOffset && (!movingLeft || !scene->isTilePassableIgnoreUnit(zone, tileDestinationBuffer->x - 1, tileDestinationBuffer->y, this)))
//                {
//                    scene->xOffset = destXOffset;
//                }
//            }
//        }
//        else if (tileDestinationBuffer->y > tileLocationBuffer->y) { // moving down
//            if (impliedMovement > leftToMoveBuffer && (!movingDown || !scene->isTilePassableIgnoreUnit(zone, tileDestinationBuffer->x, tileDestinationBuffer->y + 1, this)))
//            {
//                remainderMovement = impliedMovement - leftToMoveBuffer;
//                impliedMovement = leftToMoveBuffer;
//                scene->yOffset = destYOffset;
//            }
//            else {
//                scene->yOffset -= impliedMovement * scene->tileHeight;
//                if (scene->yOffset < destYOffset && (!movingDown || !scene->isTilePassableIgnoreUnit(zone, tileDestinationBuffer->x, tileDestinationBuffer->y + 1, this)))
//                {
//                    scene->yOffset = destYOffset;
//                }
//            }
//        }
//        else if (tileDestinationBuffer->y < tileLocationBuffer->y) { //moving up
//            if (impliedMovement > leftToMoveBuffer && (!movingUp || !scene->isTilePassableIgnoreUnit(zone, tileDestinationBuffer->x, tileDestinationBuffer->y - 1, this)))
//            {
//                remainderMovement = impliedMovement - leftToMoveBuffer;
//                impliedMovement = leftToMoveBuffer;
//                scene->yOffset = destYOffset;
//            }
//            else {
//                scene->yOffset += impliedMovement * scene->tileHeight;
//                if (scene->yOffset > destYOffset && (!movingUp || !scene->isTilePassableIgnoreUnit(zone, tileDestinationBuffer->x, tileDestinationBuffer->y - 1, this)))
//                {
//                    scene->yOffset = destYOffset;
//                }
//            }
//        }
//        if (remainderMovement > 0)
//        {
//            if (movingDown && scene->isTilePassableIgnoreUnit(zone, tileDestinationBuffer->x, tileDestinationBuffer->y + 1, this)) {
//            //if (movingDown) {
//                scene->yOffset -= remainderMovement * scene->tileHeight;
//            }
//            else if (movingUp && scene->isTilePassableIgnoreUnit(zone, tileDestinationBuffer->x, tileDestinationBuffer->y - 1, this)) {
//            //else if (movingUp) {
//                scene->yOffset += remainderMovement * scene->tileHeight;
//            }
//            else if (movingRight && scene->isTilePassableIgnoreUnit(zone, tileDestinationBuffer->x + 1, tileDestinationBuffer->y, this)) {
//            //else if (movingRight) {
//                scene->xOffset -= remainderMovement * scene->tileWidth;
//            }
//            else if (movingLeft && scene->isTilePassableIgnoreUnit(zone, tileDestinationBuffer->x - 1, tileDestinationBuffer->y, this)) {
//            //else if (movingLeft) {
//                scene->xOffset += remainderMovement * scene->tileWidth;
//            }
//        }
//        int xdelta = scene->xOffset - prevxoffset;
//        int ydelta = scene->yOffset - prevyoffset;
//
//        if (tileDestinationBuffer->x > tileLocationBuffer->x && xdelta >= 0)
//        {
//            scene->xOffset = prevxoffset - 1;
//        }
//        else if (tileDestinationBuffer->x < tileLocationBuffer->x && xdelta <= 0) {
//            scene->xOffset = prevxoffset + 1;
//        }
//        else if (tileDestinationBuffer->y > tileLocationBuffer->y && ydelta >= 0) {
//            scene->yOffset = prevyoffset - 1;
//        }
//        else if (tileDestinationBuffer->y < tileLocationBuffer->y && ydelta <= 0) {
//            scene->yOffset = prevyoffset + 1;
//        }
//
//        /*if (xdelta == 0 && leftToMoveBuffer > 0)
//        {
//            if (movingLeft) {
//                scene->xOffset += 1;
//            }
//            else if (movingRight) {
//                scene->xOffset -= 1;
//            }
//        }
//
//        if (ydelta == 0 && leftToMoveBuffer > 0)
//        {
//            if (movingUp) {
//                scene->yOffset += 1;
//            }
//            else if (movingDown) {
//                scene->yOffset -= 1;
//            }
//        }*/
//        // TESTING START
//        xdelta = scene->xOffset - prevxoffset;
//        ydelta = scene->yOffset - prevyoffset;
//
//        if (prevxoffset == scene->xOffset && movingRight)
//        {
//            int hh = scene->xOffset - prevxoffset;
//            int c = 23436;
//        }
//        std::cout << "\ndelta: ";
//        std::cout << scene->xOffset - prevxoffset;
//        std::cout << " base delta: ";
//        std::cout << basexoff - prevxoffset;
//        std::cout << " left to move: ";
//        std::cout << leftToMoveBuffer;
//        std::cout << " implied movement: ";
//        std::cout << impliedMovement;
//        std::cout << " time since last tick: ";
//        std::cout << timeSinceLastTick;
//        std::cout << "\nlast render time: ";
//        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() - lastRenderTimeStamp;
//        //std::cout << "\n";
//        if (scene->xOffset - prevxoffset > 5 || scene->xOffset - prevxoffset < -5)
//        {
//            int dfgdfg = 4564;
//        }
//        // TESTING END
//    }
//     else {
//     //std::cout << "\nnot moving\n";
//    }
//    
//    //xdelta = scene->xOffset - prevxoffset;
//    //ydelta = scene->yOffset - prevyoffset;
//
//    //std::cout <<  "\n delta: ";
//    //std::cout <<  scene->xOffset - prevxoffset;
//    //std::cout << "\n";
//    lastRenderTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
//    //if (movingRight && xdelta > 0)
//    //{
//    //    scene->xOffset = prevxoffset - 1;
//    //}
//    updateCoords();
//}

void Player::updateCamera()
{
    double coords[2];
    double destCoords[2];
    scene->coordsFromTileIndex(tileLocationBuffer->x, tileLocationBuffer->y, coords);
    scene->coordsFromTileIndex(tileDestinationBuffer->x, tileDestinationBuffer->y, destCoords);
    double x = coords[0] + ((double)destCoords[0] - (double)coords[0]) * (1 - leftToMoveBuffer);
    double y = coords[1] + ((double)destCoords[1] - (double)coords[1]) * (1 - leftToMoveBuffer);
    double desiredCoords[2];
    scene->desiredPlayerDrawLocation(desiredCoords);
    int desiredX = desiredCoords[0];
    int desiredY = desiredCoords[1];


    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    double framesPerTick = (current.refresh_rate) / scene->engine->ticksPerSecond;
    

    if (x < desiredX) { //moving left
        int scrollSpeed = (scene->tileWidth / speed) / framesPerTick;
        if (scrollSpeed > desiredX - x)
        {
            scrollSpeed = desiredX - x;
        }
        scene->xOffset += scrollSpeed;
    }
    if (x > desiredX) { //moving right
        int scrollSpeed = (scene->tileWidth / speed) / framesPerTick;
        if (scrollSpeed < desiredX - x)
        {
            scrollSpeed = desiredX - x;
        }
        scene->xOffset -= scrollSpeed;
    }
    if (y < desiredY) {
        int scrollSpeed = (scene->tileHeight / speed) / framesPerTick;
        if (scrollSpeed > desiredY - y)
        {
            scrollSpeed = desiredY - y;
        }
        scene->yOffset += scrollSpeed;
    }
    if (y > desiredY) {
        int scrollSpeed = (scene->tileHeight / speed) / framesPerTick;
        if (scrollSpeed < desiredY - y)
        {
            scrollSpeed = desiredY - y;
        }
        scene->yOffset -= scrollSpeed;
    }
    //updateCoords();
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
    scene->setCurrentZone(zone);
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
    scene->menus[INVENTORY_MENU]->rebuildMenuElements();
    scene->menus[INVENTORY_MENU]->update();
    portalTo(1, 6, 6);
}

void Player::draw()
{
    double desiredCoords[2];
    scene->desiredPlayerDrawLocation(desiredCoords);
    xpos = desiredCoords[0] - scene->tileWidth;
    ypos = desiredCoords[1] - scene->tileHeight;
    currentState->updateAnimation();
    if (cameraFollowPlayer)
    {
        Unit::drawNoCoordUpdate();
        drawHealth();
    }
    else {

        Unit::draw();
        drawHealth();
    }
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

