#pragma once
#include "GameScene.h"

class Animation
{
public:
    //attributes
    GameScene * scene;
    int spriteSheetKey;
    int numFrames, frameHeight, frameWidth, ticksBetweenFrames, tickCount, currentFrame;
    bool active, loop;

    //constructors
    Animation();
    Animation(GameScene * newScene, int newSpriteSheetKey, int newNumFrames, int newTicksBetweenFrames);
    Animation(GameScene * newScene, int newSpriteSheetKey, int newNumFrames, int newTicksBetweenFrames, bool isLoop);

    //methods
    void tick();
    void resetAnimation(int startframe = 0);
    void setAnimationLength(int lengthInGameTicks);

private:
    //attributes

    //methods
    void init();
    void init(GameScene* newScene, int newSpriteSheetKey, int newNumFrames, int newTicksBetweenFrames);
};

