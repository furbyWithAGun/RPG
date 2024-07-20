#pragma once
#include "Sprite.h"
#include "Animation.h"

class AnimatedSprite : public Sprite
{
public:
    //attributes
    std::unordered_map<int, Animation> animations;
    Animation* currentAnimation;
    Animation* tempAnimation;

    //constructors
    AnimatedSprite();
    AnimatedSprite(GameScene* gameScene);

    //methods
    void addAnimation(int animationKey, int spriteSheetKey, int numFrames, int ticksBetweenFrames, bool isLoop = true);
    void replaceAnimation(int animationKey, int spriteSheetKey, int numFrames, int ticksBetweenFrames, bool isLoop = true);
    void setAnimation(int animationKey);
    void playAnimation(int animationKey);
    void playAnimation(int animationKey, int duration);
    void setup();
    virtual void update();
    void draw();
    void draw(int x, int y);
    void resize(int x , int y);

private:
    //methods
    void init();
};

