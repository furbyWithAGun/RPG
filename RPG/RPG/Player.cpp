#include "Player.h"
#include "RpgTileGridScene.h"
#include "BasicMeleeAttack.h"
#include "RpgOverWorldScene.h"

//stat constants
//const int PLAYER_SPEED = 4;
const int PLAYER_SPEED = 10;
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
    setZone(0);
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
    setAttributeLevel(UNIT_STAT_SPEED, PLAYER_SPEED);
    equipedAttacks[MAIN_ATTACK] = new BasicMeleeAttack(MELEE, this); //potential memory leak
    activeAttack = equipedAttacks[MAIN_ATTACK];
    setAttributeLevel(UNIT_STAT_MAX_HEALTH, PLAYER_MAX_HEALTH);
    health = PLAYER_MAX_HEALTH;
    setAttributeLevel(UNIT_STAT_DEX, PLAYER_DEX);
    setAttributeLevel(UNIT_STAT_AGI, PLAYER_AGI);
    //dex = PLAYER_DEX;
    //agi = PLAYER_AGI;
    team = PLAYER_TEAM;
    cameraFollowPlayer = true;
    createAnimations();
    lastXDelta = 0;
    lastXDelta2 = 0;
    lastXDelta3 = 0;
    lastYDelta = 0;
    lastYDelta2 = 0;
    lastYDelta3 = 0;
    changedXSpeedlastTick = false;
    changedYSpeedlastTick = false;
    canChangeXSpeed = false;
    canChangeYSpeed = false;
    lastRenderTimeStamp = 0;
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
    double coords[2];
    double destCoords[2];
    scene->coordsFromTileIndex(tileLocationBuffer->x, tileLocationBuffer->y, coords);
    scene->coordsFromTileIndex(tileDestinationBuffer->x, tileDestinationBuffer->y, destCoords);
    double x = coords[0] + ((double)destCoords[0] - (double)coords[0]) * (1 - leftToMoveBuffer);
    double y = coords[1] + ((double)destCoords[1] - (double)coords[1]) * (1 - leftToMoveBuffer);
    double desiredCoords[2];
    scene->desiredPlayerDrawLocation(desiredCoords);
    
    int destXOffset = desiredCoords[0] - scene->mainCanvasStartX - tileDestinationBuffer->x * scene->tileWidth;
    int destYOffset = desiredCoords[1] - tileDestinationBuffer->y * scene->tileHeight;

    int prevxoffset = scene->xOffset;
    int prevyoffset = scene->yOffset;
    scene->xOffset += desiredCoords[0] - x;
    scene->yOffset += desiredCoords[1] - y;

    int basexoff = scene->xOffset;
    int baseyoff = scene->yOffset;
    
    if (leftToMoveBuffer > 0)
    {
        if (leftToMoveBuffer < 0.0001)
        {
            int dfgdfgdfg = 345345;
        }
        if (prevxoffset > scene->xOffset)
        {
            int hh = scene->xOffset - prevxoffset;
            int c = 23436;
        }

        double movementPerTick = ((double)getAttributeLevel(UNIT_STAT_SPEED) / 100);
        double timeSinceLastTick = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() - scene->getLastTickTimeStampBuffer();
        if (timeSinceLastTick > scene->engine->tickDelay)
        {
            //timeSinceLastTick = scene->engine->tickDelay;
        }
        double lastLogictick = scene->getLastTickTimeStampBuffer();
        double newtick = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        double timeRatioSinceLastTick = timeSinceLastTick / scene->engine->tickDelay;
        double impliedMovement = movementPerTick * timeRatioSinceLastTick;
        double remainderMovement = 0;
        
        //impliedMovement = 0;
        if (impliedMovement > 0)
        {
            int f = 45757567;
        }
        if (impliedMovement > leftToMoveBuffer) {
            int dfgdgdf = 234234;
        }

        if (tileDestinationBuffer->x > tileLocationBuffer->x) //moving right
        {
            if (impliedMovement > leftToMoveBuffer && (!movingRight || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x + 1, tileDestinationBuffer->y, this)))
            {
                remainderMovement = impliedMovement - leftToMoveBuffer;
                impliedMovement = leftToMoveBuffer;
                scene->xOffset = destXOffset;
                // TESTING START
                if (prevxoffset > scene->xOffset)
                {
                    int hh = scene->xOffset - prevxoffset;
                    int c = 23436;
                }
                //std::cout << scene->xOffset - prevxoffset;
                //std::cout << " left to move: ";
                //std::cout << leftToMoveBuffer;
                //std::cout << " implied movement: ";
                //std::cout << impliedMovement;
                //std::cout << " time since last tick: ";
                //std::cout << timeSinceLastTick;
                //std::cout << "\n";
                if (scene->xOffset - prevxoffset > 5 || scene->xOffset - prevxoffset < -5)
                {
                    int dfgdfg = 4564;
                }
                // TESTING END
            }
            else {
                scene->xOffset -= impliedMovement * scene->tileWidth;
                // TESTING START
                if (prevxoffset > scene->xOffset)
                {
                    int hh = scene->xOffset - prevxoffset;
                    int c = 23436;
                }
                //std::cout << scene->xOffset - prevxoffset;
                //std::cout << " left to move: ";
                //std::cout << leftToMoveBuffer;
                //std::cout << " implied movement: ";
                //std::cout << impliedMovement;
                //std::cout << " time since last tick: ";
                //std::cout << timeSinceLastTick;
                //std::cout << "\n";
                if (scene->xOffset - prevxoffset > 5 || scene->xOffset - prevxoffset < -5)
                {
                    int dfgdfg = 4564;
                }
                // TESTING END
                if (scene->xOffset < destXOffset && (!movingRight || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x + 1, tileDestinationBuffer->y, this)))
                {
                    scene->xOffset = destXOffset;
                    // TESTING START
                    if (prevxoffset > scene->xOffset)
                    {
                        int hh = scene->xOffset - prevxoffset;
                        int c = 23436;
                    }
                    /*std::cout << scene->xOffset - prevxoffset;
                    std::cout << " left to move: ";
                    std::cout << leftToMoveBuffer;
                    std::cout << " implied movement: ";
                    std::cout << impliedMovement;
                    std::cout << " time since last tick: ";
                    std::cout << timeSinceLastTick;
                    std::cout << "\n";*/
                    if (scene->xOffset - prevxoffset > 5 || scene->xOffset - prevxoffset < -5)
                    {
                        int dfgdfg = 4564;
                    }
                    // TESTING END
                }
            }
        }
        else if (tileDestinationBuffer->x < tileLocationBuffer->x) { // moving left
            if (impliedMovement > leftToMoveBuffer && (!movingLeft || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x - 1, tileDestinationBuffer->y, this)))
            {
                remainderMovement = impliedMovement - leftToMoveBuffer;
                impliedMovement = leftToMoveBuffer;
                scene->xOffset = destXOffset;
            }
            else {
                scene->xOffset += impliedMovement * scene->tileWidth;
                if (scene->xOffset > destXOffset && (!movingLeft || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x - 1, tileDestinationBuffer->y, this)))
                {
                    scene->xOffset = destXOffset;
                }
            }
        }
        else if (tileDestinationBuffer->y > tileLocationBuffer->y) { // moving down
            if (impliedMovement > leftToMoveBuffer && (!movingDown || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x, tileDestinationBuffer->y + 1, this)))
            {
                remainderMovement = impliedMovement - leftToMoveBuffer;
                impliedMovement = leftToMoveBuffer;
                scene->yOffset = destYOffset;
            }
            else {
                scene->yOffset -= impliedMovement * scene->tileHeight;
                if (scene->yOffset < destYOffset && (!movingDown || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x, tileDestinationBuffer->y + 1, this)))
                {
                    scene->yOffset = destYOffset;
                }
            }
        }
        else if (tileDestinationBuffer->y < tileLocationBuffer->y) { //moving up
            if (impliedMovement > leftToMoveBuffer && (!movingUp || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x, tileDestinationBuffer->y - 1, this)))
            {
                remainderMovement = impliedMovement - leftToMoveBuffer;
                impliedMovement = leftToMoveBuffer;
                scene->yOffset = destYOffset;
            }
            else {
                scene->yOffset += impliedMovement * scene->tileHeight;
                if (scene->yOffset > destYOffset && (!movingUp || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x, tileDestinationBuffer->y - 1, this)))
                {
                    scene->yOffset = destYOffset;
                }
            }
        }
        if (remainderMovement > 0)
        {
            if (movingDown && scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x, tileDestinationBuffer->y + 1, this)) {
            //if (movingDown) {
                scene->yOffset -= remainderMovement * scene->tileHeight;
            }
            else if (movingUp && scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x, tileDestinationBuffer->y - 1, this)) {
            //else if (movingUp) {
                scene->yOffset += remainderMovement * scene->tileHeight;
            }
            else if (movingRight && scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x + 1, tileDestinationBuffer->y, this)) {
            //else if (movingRight) {
                scene->xOffset -= remainderMovement * scene->tileWidth;
            }
            else if (movingLeft && scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x - 1, tileDestinationBuffer->y, this)) {
            //else if (movingLeft) {
                scene->xOffset += remainderMovement * scene->tileWidth;
            }
        }
        int xdelta = scene->xOffset - prevxoffset;
        int ydelta = scene->yOffset - prevyoffset;

        if (tileDestinationBuffer->x > tileLocationBuffer->x && xdelta >= 0)
        {
            scene->xOffset = prevxoffset - 1;
        }
        else if (tileDestinationBuffer->x < tileLocationBuffer->x && xdelta <= 0) {
            scene->xOffset = prevxoffset + 1;
        }
        else if (tileDestinationBuffer->y > tileLocationBuffer->y && ydelta >= 0) {
            scene->yOffset = prevyoffset - 1;
        }
        else if (tileDestinationBuffer->y < tileLocationBuffer->y && ydelta <= 0) {
            scene->yOffset = prevyoffset + 1;
        }

        /*if (xdelta == 0 && leftToMoveBuffer > 0)
        {
            if (movingLeft) {
                scene->xOffset += 1;
            }
            else if (movingRight) {
                scene->xOffset -= 1;
            }
        }

        if (ydelta == 0 && leftToMoveBuffer > 0)
        {
            if (movingUp) {
                scene->yOffset += 1;
            }
            else if (movingDown) {
                scene->yOffset -= 1;
            }
        }*/
        // TESTING START
        xdelta = scene->xOffset - prevxoffset;
        ydelta = scene->yOffset - prevyoffset;

        if (prevxoffset == scene->xOffset && movingRight)
        {
            int hh = scene->xOffset - prevxoffset;
            int c = 23436;
        }
        std::cout << "\ndelta: ";
        std::cout << scene->xOffset - prevxoffset;
        std::cout << " base delta: ";
        std::cout << basexoff - prevxoffset;
        std::cout << " left to move: ";
        std::cout << leftToMoveBuffer;
        std::cout << " implied movement: ";
        std::cout << impliedMovement;
        std::cout << " time since last tick: ";
        std::cout << timeSinceLastTick;
        std::cout << "\nlast render time: ";
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() - lastRenderTimeStamp;
        std::cout << " fps: ";
        std::cout << scene->engine->getRollingFpsRate();
        std::cout << " tick rate: ";
        std::cout << scene->engine->getRollingTickRate();
        //std::cout << "\n";
        if (scene->xOffset - prevxoffset > 5 || scene->xOffset - prevxoffset < -5)
        {
            int dfgdfg = 4564;
        }
        // TESTING END
    }
     else {
     //std::cout << "\nnot moving\n";
    }
    
    //xdelta = scene->xOffset - prevxoffset;
    //ydelta = scene->yOffset - prevyoffset;

    //std::cout <<  "\n delta: ";
    //std::cout <<  scene->xOffset - prevxoffset;
    //std::cout << "\n";
    lastRenderTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    //if (movingRight && xdelta > 0)
    //{
    //    scene->xOffset = prevxoffset - 1;
    //}
    updateCoords();
}

void Player::updateCamera2()
{
    //updateCoords();
    double coords[2];
    SDL_AtomicLock(&scene->TileGridUnitLock);
    double destCoords[2];
    scene->coordsFromTileIndex(tileLocationBuffer->x, tileLocationBuffer->y, coords);
    scene->coordsFromTileIndex(tileDestinationBuffer->x, tileDestinationBuffer->y, destCoords);
    double x = coords[0] + ((double)destCoords[0] - (double)coords[0]) * (1 - leftToMoveBuffer);
    double y = coords[1] + ((double)destCoords[1] - (double)coords[1]) * (1 - leftToMoveBuffer);
    double desiredCoords[2];
    scene->desiredPlayerDrawLocation(desiredCoords);

    int destXOffset = desiredCoords[0] - scene->mainCanvasStartX - tileDestinationBuffer->x * scene->tileWidth;
    int destYOffset = desiredCoords[1] - tileDestinationBuffer->y * scene->tileHeight;
    SDL_AtomicUnlock(&scene->TileGridUnitLock);
    int prevxoffset = scene->xOffset;
    int prevyoffset = scene->yOffset;
    scene->xOffset += desiredCoords[0] - x;
    scene->yOffset += desiredCoords[1] - y;

    int basexoff = scene->xOffset;
    int baseyoff = scene->yOffset;

    if (scene->xOffset - prevxoffset != 0) {

        std::cout << "\nLeft To Move: ";
        std::cout << leftToMoveBuffer;
        std::cout << " change: ";
        std::cout << scene->xOffset - prevxoffset;
        std::cout << " x: ";
        std::cout << x;
        std::cout << " destx: ";
        std::cout << destCoords[0];
        std::cout << " fps: ";
        std::cout << scene->engine->getRollingFpsRate();
        std::cout << " tick rate: ";
        std::cout << scene->engine->getRollingTickRate();
        std::cout << " tile loc: ";
        std::cout << tileLocationBuffer->x;
        std::cout << " tile des: ";
        std::cout << tileDestinationBuffer->x;
    }
    //updateCoords();
}

void Player::updateCamera3()
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
    int prevxoffset = scene->xOffset;
    int prevyoffset = scene->yOffset;


    //SDL_DisplayMode current;
    //SDL_GetCurrentDisplayMode(0, &current);
    //double framesPerTick = (current.refresh_rate) / scene->engine->getRollingTickRate();
    double framesPerTick = scene->engine->getRollingFpsRate() / scene->engine->getRollingTickRate();
    double xSpeedPerTick = double(scene->tileWidth * ((double)getAttributeLevel(UNIT_STAT_SPEED) / 100));
    double ySpeedPerTick = double(scene->tileHeight * ((double)getAttributeLevel(UNIT_STAT_SPEED) / 100));
    double xBaseScrollSpeed = xSpeedPerTick / framesPerTick;
    double yBaseScrollSpeed = ySpeedPerTick / framesPerTick;
    double xScrollSpeed = 0;
    double yScrollSpeed = 0;
    double xDelta = (int)desiredX - (int)x;
    double yDelta = (int)desiredY - (int)y;
    int pathFollowed = 0;
    int xDistanceToDest = destCoords[0] - desiredCoords[0];
    int yDistanceToDest = destCoords[1] - desiredCoords[1];

    if (leftToMoveBuffer)
    {
        if (std::abs(xDelta >= 2 * scene->tileWidth))
        {
            xScrollSpeed = xDelta;
        }
        else if (xDelta < 0) // moving right
        {
            if (tileDestinationBuffer->x < tileLocationBuffer->x || (movingLeft && tileDestinationBuffer->x == tileLocationBuffer->x)) { // supposed to be moving left
                if(std::abs(xDistanceToDest) < xBaseScrollSpeed && (!movingLeft || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x - 1, tileDestinationBuffer->y, this)))
                {
                    xScrollSpeed = xDistanceToDest;
                    pathFollowed = 1;
                }
                else if ((std::abs(xDelta) > xSpeedPerTick * 1.5)) {
                    xScrollSpeed = xBaseScrollSpeed / 2;
                    pathFollowed = 2;
                }
                else {
                    xScrollSpeed = xBaseScrollSpeed;
                    pathFollowed = 3;
                }
            }
            else if (std::abs(xDelta) > xSpeedPerTick * 1.5) {
                xScrollSpeed = -xBaseScrollSpeed - 1;
                pathFollowed = 4;
            }
            else if (std::abs(xDelta) < xBaseScrollSpeed && leftToMoveBuffer < (double)getAttributeLevel(UNIT_STAT_SPEED) / (double)100 && (!movingRight || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x + 1, tileDestinationBuffer->y, this))) {
                xScrollSpeed = xDelta;
                pathFollowed = 5;
            }
            else {
                xScrollSpeed = -xBaseScrollSpeed;
                pathFollowed = 6;
            }
        } else if (xDelta > 0) // moving left
        {
            if (tileDestinationBuffer->x > tileLocationBuffer->x || (movingRight && tileDestinationBuffer->x == tileLocationBuffer->x)) { // supposed to be moving right
                if (std::abs(xDistanceToDest) < xBaseScrollSpeed && (!movingRight || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x + 1, tileDestinationBuffer->y, this)))
                {
                    xScrollSpeed = -xDistanceToDest;
                    pathFollowed = 7;
                }
                else if ((std::abs(xDelta) > xSpeedPerTick * 1.5)) {
                    xScrollSpeed = -xBaseScrollSpeed / 2;
                    pathFollowed = 8;
                }
                else {
                    xScrollSpeed = -xBaseScrollSpeed;
                    pathFollowed = 9;
                }
            }
            else if (std::abs(xDelta) > xSpeedPerTick * 1.5) {
                xScrollSpeed = xBaseScrollSpeed + 1;
                pathFollowed = 10;
            }
            else if (std::abs(xDelta) < xBaseScrollSpeed && leftToMoveBuffer < (double)getAttributeLevel(UNIT_STAT_SPEED) / (double)100 && (!movingLeft || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x - 1, tileDestinationBuffer->y, this))) {
                xScrollSpeed = xDelta;
                pathFollowed = 11;
            }
            else {
                xScrollSpeed = xBaseScrollSpeed;
                pathFollowed = 12;
            }
        }
        else if (tileDestinationBuffer->y == tileLocationBuffer->y && tileDestinationBuffer->x > tileLocationBuffer->x && (xDistanceToDest != 0 || movingRight && scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x + 1, tileDestinationBuffer->y, this))) {
            if (std::abs(xDistanceToDest) < xBaseScrollSpeed && (!movingRight || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x + 1, tileDestinationBuffer->y, this)))
            {
                if (xDistanceToDest > 0)
                {
                    xScrollSpeed = -xDistanceToDest;
                }
                else {
                    xScrollSpeed = xDistanceToDest;
                }
            }
            else {
                xScrollSpeed = -xBaseScrollSpeed;
            }
            pathFollowed = 13;
        }
        else if (tileDestinationBuffer->y == tileLocationBuffer->y && movingRight && scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x + 1, tileDestinationBuffer->y, this)) {
            xScrollSpeed = -xBaseScrollSpeed;
            pathFollowed = 14;
        }
        else if (tileDestinationBuffer->y == tileLocationBuffer->y && tileDestinationBuffer->x < tileLocationBuffer->x && (xDistanceToDest != 0 || movingLeft && scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x - 1, tileDestinationBuffer->y, this))) {
            if (std::abs(xDistanceToDest) < xBaseScrollSpeed && (!movingLeft || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x - 1, tileDestinationBuffer->y, this)))
            {
                if (xDistanceToDest > 0)
                {

                    xScrollSpeed = xDistanceToDest;
                }
                else {
                    xScrollSpeed = -xDistanceToDest;
                }
            }
            else {
                xScrollSpeed = xBaseScrollSpeed;
            }
            pathFollowed = 15;
        }
        else if (tileDestinationBuffer->y == tileLocationBuffer->y && movingLeft && scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x - 1, tileDestinationBuffer->y, this)){
            xScrollSpeed = xBaseScrollSpeed;
            pathFollowed = 16;
        }


        if (std::abs(yDelta) >= 2 * scene->tileHeight)
        {
            yScrollSpeed = yDelta;
        }
        else if (yDelta < 0) // moving down
        {
            if (tileDestinationBuffer->y < tileLocationBuffer->y || (movingUp && tileDestinationBuffer->y == tileLocationBuffer->y)) { // supposed to be moving up
                if (std::abs(yDistanceToDest) < yBaseScrollSpeed && (!movingUp || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x, tileDestinationBuffer->y - 1, this)))
                {
                    yScrollSpeed = yDistanceToDest;
                    pathFollowed = 1;
                }
                else if ((std::abs(yDelta) > ySpeedPerTick * 1.5)) {
                    yScrollSpeed = yBaseScrollSpeed / 2;
                    pathFollowed = 2;
                }
                else {
                    yScrollSpeed = yBaseScrollSpeed;
                    pathFollowed = 3;
                }
            }
            else if (std::abs(yDelta) > ySpeedPerTick * 1.5) {
                yScrollSpeed = -yBaseScrollSpeed - 1;
                pathFollowed = 4;
            }
            else if (std::abs(yDelta) < yBaseScrollSpeed && leftToMoveBuffer < (double)getAttributeLevel(UNIT_STAT_SPEED) / (double)100 && (!movingDown || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x, tileDestinationBuffer->y + 1, this))) {
                yScrollSpeed = yDelta;
                pathFollowed = 5;
            }
            else {
                yScrollSpeed = -yBaseScrollSpeed;
                pathFollowed = 6;
            }
        }
        else if (yDelta > 0) // moving up
        {
            if (tileDestinationBuffer->y > tileLocationBuffer->y || (movingDown && tileDestinationBuffer->y == tileLocationBuffer->y)) { // supposed to be moving down
                if (std::abs(yDistanceToDest) < yBaseScrollSpeed && (!movingDown || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x, tileDestinationBuffer->y + 1, this)))
                {
                    yScrollSpeed = -yDistanceToDest;
                    pathFollowed = 7;
                }
                else if ((std::abs(yDelta) > ySpeedPerTick * 1.5)) {
                    yScrollSpeed = -yBaseScrollSpeed / 2;
                    pathFollowed = 8;
                }
                else {
                    yScrollSpeed = -yBaseScrollSpeed;
                    pathFollowed = 9;
                }
            }
            else if (std::abs(yDelta) > ySpeedPerTick * 1.5) {
                yScrollSpeed = yBaseScrollSpeed + 1;
                pathFollowed = 10;
            }
            else if (std::abs(yDelta) < yBaseScrollSpeed && leftToMoveBuffer < (double)getAttributeLevel(UNIT_STAT_SPEED) / (double)100 && (!movingUp || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x, tileDestinationBuffer->y - 1, this))) {
                yScrollSpeed = yDelta;
                pathFollowed = 11;
            }
            else {
                yScrollSpeed = yBaseScrollSpeed;
                pathFollowed = 12;
            }
        }
        else if (tileDestinationBuffer->x == tileLocationBuffer->x && tileDestinationBuffer->y > tileLocationBuffer->y && (yDistanceToDest != 0 || movingDown && scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x, tileDestinationBuffer->y + 1, this))) {
            if (std::abs(yDistanceToDest) < yBaseScrollSpeed && (!movingDown || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x, tileDestinationBuffer->y + 1, this)))
            {
                if (yDistanceToDest > 0)
                {
                    yScrollSpeed = -yDistanceToDest;
                }
                else {
                    yScrollSpeed = yDistanceToDest;
                }
            }
            else {
                yScrollSpeed = -yBaseScrollSpeed;
            }
            pathFollowed = 13;
        }
        else if (tileDestinationBuffer->x == tileLocationBuffer->x && movingDown && scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x, tileDestinationBuffer->y + 1, this)) {
            yScrollSpeed = -yBaseScrollSpeed;
            pathFollowed = 14;
        }
        else if (tileDestinationBuffer->x == tileLocationBuffer->x && tileDestinationBuffer->y < tileLocationBuffer->y && (yDistanceToDest != 0 || movingUp && scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x, tileDestinationBuffer->y - 1, this))) {
            if (std::abs(yDistanceToDest) < yBaseScrollSpeed && (!movingUp || !scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x, tileDestinationBuffer->y - 1, this)))
            {
                if (yDistanceToDest > 0)
                {

                    yScrollSpeed = yDistanceToDest;
                }
                else {
                    yScrollSpeed = -yDistanceToDest;
                }
            }
            else {
                yScrollSpeed = yBaseScrollSpeed;
            }
            pathFollowed = 15;
        }
        else if (tileDestinationBuffer->x == tileLocationBuffer->x && movingUp && scene->isTilePassableIgnoreUnit(getZone(), tileDestinationBuffer->x, tileDestinationBuffer->y - 1, this)) {
            yScrollSpeed = yBaseScrollSpeed;
            pathFollowed = 16;
        }
    }
    else {
        if (std::abs(xDelta) > 4 * xSpeedPerTick || std::abs(xDelta) < xBaseScrollSpeed)
        {
            xScrollSpeed = xDelta;
        }
        else if (xDelta == 0) {
            xScrollSpeed = 0;
        }
        else if (xDelta < 0){
            xScrollSpeed = -xBaseScrollSpeed;
        }
        else {
            xScrollSpeed = xBaseScrollSpeed;
        }

        if (std::abs(yDelta) > 4 * ySpeedPerTick || std::abs(yDelta) < yBaseScrollSpeed)
        {
            yScrollSpeed = yDelta;
        }
        else if (yDelta == 0) {
            yScrollSpeed = 0;
        }
        else if (yDelta < 0) {
            yScrollSpeed = -yBaseScrollSpeed;
        }
        else {
            yScrollSpeed = yBaseScrollSpeed;
        }
    }

    if (tileDestinationBuffer->x != tileLocationBuffer->x)
    {
        yScrollSpeed = 0;
        if (yDelta > 0)
        {
            yScrollSpeed = 1;
        }
        else if (yDelta < 0) {
            yScrollSpeed = -1;
        }
    }

    if (tileDestinationBuffer->y != tileLocationBuffer->y)
    {
        xScrollSpeed = 0;
        if (xDelta > 0)
        {
            xScrollSpeed = 1;
        }
        else if (xDelta < 0) {
            xScrollSpeed = -1;
        }
    }

    
    /*if (xScrollSpeed > 0 && xScrollSpeed > lastXScrollSpeed + 1 && !changedXSpeedlastTick)
    {
        xScrollSpeed = lastXScrollSpeed + 1;
    }
    else if(changedXSpeedlastTick) {
        xScrollSpeed = lastXScrollSpeed;
    }

    if (xScrollSpeed < 0 && xScrollSpeed < lastXScrollSpeed - 1 && !changedXSpeedlastTick)
    {
        xScrollSpeed = lastXScrollSpeed - 1;
    }
    else if (changedXSpeedlastTick) {
        xScrollSpeed = lastXScrollSpeed;
    }*/

    if (xScrollSpeed > 0)
    {
        xScrollSpeed = floor(xScrollSpeed);
    }
    else {

        xScrollSpeed = ceil(xScrollSpeed);
    }

    if (yScrollSpeed > 0)
    {
        yScrollSpeed = floor(yScrollSpeed);
    }
    else {

        yScrollSpeed = ceil(yScrollSpeed);
    }

    if (changedXSpeedlastTick && xScrollSpeed != 0)
    {
        xScrollSpeed = lastXScrollSpeed;
    }
    if (changedYSpeedlastTick && yScrollSpeed != 0)
    {
        yScrollSpeed = lastYScrollSpeed;
    }

    if (lastXScrollSpeed == xScrollSpeed)
    {
        changedXSpeedlastTick = false;
        canChangeXSpeed = true;
    }
    else {
        changedXSpeedlastTick = true;
    }
    if (lastYScrollSpeed == yScrollSpeed)
    {
        changedYSpeedlastTick = false;
        canChangeYSpeed = true;
    }
    else {
        changedYSpeedlastTick = true;
    }

    lastXScrollSpeed = xScrollSpeed;
    lastYScrollSpeed = yScrollSpeed;
    scene->xOffsetTemp += xScrollSpeed;
    scene->yOffsetTemp += yScrollSpeed;
    scene->xOffset = scene->xOffsetTemp;
    scene->yOffset = scene->yOffsetTemp;

    

    int frameDelay = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() - lastRenderTimeStamp;
    lastRenderTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    
    if (xDelta!=0 || leftToMoveBuffer)
    {
        if (xScrollSpeed != 0 && scene->xOffset - prevxoffset == 0)
        {
            int dfgfdgd = 234324;
        }
        if (xDelta < 0 && tileDestinationBuffer->x < tileLocationBuffer->x)
        {
            int dfgfdg = 345435;
        }
        std::cout << "\nLeft To Move: ";
        std::cout << leftToMoveBuffer;
        std::cout << " input delta: ";
        std::cout << xDelta;
        std::cout << " xspeed: ";
        std::cout << xScrollSpeed;
        std::cout << " change: ";
        std::cout << scene->xOffset - prevxoffset;
        std::cout << " path: ";
        std::cout << pathFollowed;
        std::cout << " x: ";
        std::cout << x;
        std::cout << " destx: ";
        std::cout << destCoords[0];
        std::cout << " x Distance left: ";
        std::cout << xDistanceToDest;
        std::cout << " fps: ";
        std::cout << scene->engine->getRollingFpsRate();
        std::cout << " fps delay: ";
        std::cout << frameDelay;
        std::cout << " tick rate: ";
        std::cout << scene->engine->getRollingTickRate();
    }

    /*if (yDelta != 0 || leftToMoveBuffer)
    {
        if (yScrollSpeed != 0 && scene->yOffset - prevyoffset == 0)
        {
            int dfgfdgd = 234324;
        }
        if (yDelta < 0 && tileDestinationBuffer->y < tileLocationBuffer->y)
        {
            int dfgfdg = 345435;
        }
        std::cout << "\nLeft To Move: ";
        std::cout << leftToMoveBuffer;
        std::cout << " yinput delta: ";
        std::cout << yDelta;
        std::cout << " yspeed: ";
        std::cout << yScrollSpeed;
        std::cout << " ychange: ";
        std::cout << scene->yOffset - prevyoffset;
        std::cout << " path: ";
        std::cout << pathFollowed;
        std::cout << " y: ";
        std::cout << y;
        std::cout << " desty: ";
        std::cout << destCoords[1];
        std::cout << " y Distance left: ";
        std::cout << yDistanceToDest;
    }*/
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
    RpgUnit* squadUnit;


    for (size_t i = 1; i < MAX_NUM_SQUAD_UNITS; i++)
    {
        squadUnit = ((RpgOverWorldScene*)scene)->getSquadUnits()[i];
        if (squadUnit && squadUnit->getZone() == getZone() && scene->getZone(getZone())->manhattenDistance(tileLocation, squadUnit->tileLocation) <= 15) {
            squadUnit->portalTo(zoneId, x, y);
        }
    }
    Unit::portalTo(zoneId, x, y);
    scene->setCurrentZone(getZone());
    tileDestinationBuffer->x = x;
    tileDestinationBuffer->y = y;
}

void Player::portalToNoCommandUnits(int zoneId, int x, int y)
{
    Unit::portalTo(zoneId, x, y);
    scene->setCurrentZone(getZone());
    tileDestinationBuffer->x = x;
    tileDestinationBuffer->y = y;
}

void Player::death()
{
    /*RpgUnit::death();
    scene->engine->addScene(OVERWORLD, new RpgOverWorldScene(scene->engine));
    scene->engine->setNextScene(MAIN_MENU_SCENE);
    scene->endScene();*/
    combatExperience = combatExperienceLastLevel;

    for (int i = BARE_HANDS + 1; i != NUM_EQUIPMENT_SLOTS; i++)
    {
        unEquipItem(i);
    }
    inventory.clear();
    health = getAttributeLevel(UNIT_STAT_MAX_HEALTH);
    gold = 0;
    foodEffects.clear();
    scene->menus[INVENTORY_MENU]->rebuildMenuElements();
    scene->menus[INVENTORY_MENU]->update();
    portalToNoCommandUnits(1, 6, 6);
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

