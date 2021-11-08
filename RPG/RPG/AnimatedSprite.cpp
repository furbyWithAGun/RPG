#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite() : Sprite()
{
    init();
}

AnimatedSprite::AnimatedSprite(GameScene* gameScene) : Sprite(gameScene)
{
    init();
}

void AnimatedSprite::init() {
    currentAnimation = NULL;
    tempAnimation = NULL;
}

void AnimatedSprite::addAnimation(int animationKey, int spriteSheetKey, int numFrames, int ticksBetweenFrames, bool isLoop)
{
    if (!animations.count(animationKey))
    {
        animations[animationKey] = Animation(scene, spriteSheetKey, numFrames, ticksBetweenFrames, isLoop);
    }
    if (currentAnimation == NULL)
    {
        setup();
    }
}

void AnimatedSprite::setAnimation(int animationKey) {
    if (currentAnimation != &animations[animationKey])
    {
        currentAnimation = &animations[animationKey];
    }
}

void AnimatedSprite::playAnimation(int animationKey) {
    if (tempAnimation != &animations[animationKey])
    {
        tempAnimation = &animations[animationKey];
    }
    tempAnimation->resetAnimation();
}

void AnimatedSprite::playAnimation(int animationKey, int duration) {
    if (tempAnimation != &animations[animationKey])
    {
        tempAnimation = &animations[animationKey];
    }
    tempAnimation->setAnimationLength(duration);
    tempAnimation->resetAnimation();
}

void AnimatedSprite::setup()
{
    currentAnimation = &animations.begin()->second;
    if (width == -1)
    {
        width = currentAnimation->frameWidth;
    }
    if (height == -1)
    {
        height = currentAnimation->frameHeight;
    }
    currentAnimation->resetAnimation();
}

void AnimatedSprite::update()
{
    if (tempAnimation != NULL && tempAnimation->active)
    {
        tempAnimation->tick();
    }
    else {
        if (true)
        {

        }
        currentAnimation->tick();
    }
}

void AnimatedSprite::draw()
{
    if (tempAnimation != NULL && tempAnimation->active)
    {
        scene->engine->renderAnimation(tempAnimation, xpos, ypos, width, height);
    }
    else if (currentAnimation != NULL && currentAnimation->active) {
        scene->engine->renderAnimation(currentAnimation, xpos, ypos, width, height);
    }
}

void AnimatedSprite::resize(int x, int y) {
    width = x;
    height = y;
}