#include "Animation.h"
#include "BaseGameEngine.h"

Animation::Animation()
{
    init();
}

Animation::Animation(GameScene * newScene, int newSpriteSheetKey, int newNumFrames, int newTicksBetweenFrames)
{
    init(newScene, newSpriteSheetKey, newNumFrames, newTicksBetweenFrames);
}

Animation::Animation(GameScene* newScene, int newSpriteSheetKey, int newNumFrames, int newTicksBetweenFrames, bool isLoop)
{
    init(newScene, newSpriteSheetKey, newNumFrames, newTicksBetweenFrames);
    active = loop = isLoop;
}

void Animation::init() {
    scene = NULL;
    spriteSheetKey = 0;
    numFrames = frameHeight = frameWidth = ticksBetweenFrames = 1;
    currentFrame = tickCount = 0;
    active = true;
    loop = true;
}

void Animation::init(GameScene* newScene, int newSpriteSheetKey, int newNumFrames, int newTicksBetweenFrames) {
    init();
    scene = newScene;
    spriteSheetKey = newSpriteSheetKey;
    numFrames = newNumFrames;
    frameHeight = scene->engine->textures[newSpriteSheetKey].height / newNumFrames;
    frameWidth = newScene->engine->textures[newSpriteSheetKey].width;
    ticksBetweenFrames = newTicksBetweenFrames;
}

void Animation::tick()
{
    tickCount++;
    if (tickCount >= ticksBetweenFrames)
    {
        if (currentFrame == numFrames - 1) {
            if (loop)
            {
                resetAnimation();
            } else{
                active = false;
            }
        }
        else {
            tickCount = 0;
            currentFrame++;
        }
    }
}

void Animation::resetAnimation(int startframe) {
    active = true;
    tickCount = 0;
    currentFrame = startframe;
}

void Animation::setAnimationLength(int lengthInGameTicks)
{
    ticksBetweenFrames = lengthInGameTicks / numFrames;
}
