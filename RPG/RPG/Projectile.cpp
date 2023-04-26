#include "Projectile.h"
#include "RpgOverWorldScene.h"
#include "RpgUnit.h"


Projectile::Projectile() : AnimatedSprite()
{
    init();
}

Projectile::Projectile(RpgUnit* unit, int newTextureKey) : AnimatedSprite(unit->scene)
{
    init(unit);
    textureKey = newTextureKey;
    addAnimation(0, textureKey, 1, 100);
    setAnimation(0);
}

Projectile* Projectile::addOnCollide(std::function<void(RpgUnit* collidedUnit)> newCallback)
{
    unitCollideFunction = newCallback;
    return this;
}

Projectile* Projectile::addUpdate(std::function<void()> newCallback)
{
    updateFunction = newCallback;
    return this;
}

void Projectile::update()
{
    duration++;
    double tileCoords[2];
    xpos += xSpeed;
    ypos += ySpeed;
    scene->getTileIndexFromScreenCoords(xpos + (width / 2) + scene->xOffset, ypos + (height / 2) + scene->yOffset, tileCoords);
    RpgUnit* collidedUnit = scene->getUnitAtLocation(zoneId, tileCoords[0], tileCoords[1]);
    if (collidedUnit)
    {
        unitCollideFunction(collidedUnit);
    }
    if (!scene->isTilePassableIgnoreAllUnits(zoneId, tileCoords[0], tileCoords[1]))
    {
        active = false;
    }
    updateFunction();
}

void Projectile::deleteProjectile()
{
    ((RpgZone*)scene->getZone(zoneId))->removeFromProjectileVector(this);
}

void Projectile::setTarget(double newX, double newY)
{
    xTarget = newX - scene->xOffset;
    yTarget = newY - scene->yOffset;
    double xDelta = xTarget - xpos;
    double yDelta = yTarget - ypos;
    double hyp = sqrt(xDelta * xDelta + yDelta * yDelta);
    double hypRatio = 25 / hyp;
    xSpeed = xDelta * hypRatio;
    ySpeed = yDelta * hypRatio;
}

int Projectile::getTeam()
{
    return team;
}

void Projectile::init(RpgUnit* unit)
{
    init();
    scene = unit->scene;
    zoneId = unit->getZone();
    team = unit->team;
    double coords[2];
    unit->getCentreCoords(coords);
    xpos = coords[0] - scene->xOffset;
    ypos = coords[1] - scene->yOffset;
}

void Projectile::init()
{
    scene = nullptr;
    unitCollideFunction = [](RpgUnit* collidedUnit) {};
    updateFunction = []() {};
    xSpeed = 1;
    ySpeed = 1;
    zoneId = -1;
    maxDuration = 200;
    duration = 0;
}
