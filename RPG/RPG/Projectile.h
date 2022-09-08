#pragma once
#include "AnimatedSprite.h"
#include <functional>
#include <cmath>

class RpgUnit;
class RpgTileGridScene;

class Projectile : public AnimatedSprite
{
public:
    //attributes
    double xSpeed;
    double ySpeed;
    int direction;
    int maxDuration;
    int duration;
    //constructors
    Projectile();
    Projectile(RpgUnit* gameScene, int newTextureKey);

    //methods
    Projectile* addOnCollide(std::function<void(RpgUnit* collidedUnit)> newCallback);
    Projectile* addUpdate(std::function<void()> newCallback);
    void update();
    void deleteProjectile();
    void setTarget(double newX, double newY);
    int getTeam();

private:
    //attributes
    RpgTileGridScene* scene;
    int zoneId, xTarget, yTarget;
    std::function<void(RpgUnit* collidedUnit)> unitCollideFunction;
    std::function<void()> updateFunction;
    int team;

    //methods
    void init(RpgUnit* gameScene);
    void init();
};

