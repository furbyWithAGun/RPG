#pragma once
#include "ZoneMap.h"
#include "Projectile.h"

class RpgTileGridScene;
class RpgTown;

enum RPG_ZONE_ATTRIBUTES {
    RPG_ZONE_TYPE = 1000
};

class RpgZone : public ZoneMap
{
public:
    //attributes
    int zoneType;

    //attributes
    RpgTileGridScene* scene;

    //constructors
    RpgZone(int newId, std::vector< std::vector<int> > tiles, RpgTileGridScene* gameScene);
    RpgZone(int newId, RpgTileGridScene* gameScene);
    RpgZone(SaveObject saveObject, RpgTileGridScene* gameScene);
    RpgZone(const RpgZone& oldMap);
    RpgZone();
    RpgZone(int zoneWidth, int zoneHeight);

    //methods
    int getNumUnits();
    int getNumUnitsOnTeam(int team);
    virtual RpgTown* getNearestTown(Location* location);
    virtual RpgTown* getNearestTown(int xpos, int ypos);
    virtual Location* getNearestTownLocation(Location* location);
    virtual Location* getNearestTownLocation(int xpos, int ypos);
    virtual void update() override;
    void draw(TileGridScene* scene) override;
    //projectile vector
    void addToProjectileVector(Projectile* projectileToAdd);
    void removeFromProjectileVector(Projectile* projectileToRemove);

    virtual std::string toSaveString(bool withHeaderAndFooter = true) override;

protected:

private:
    //attributes
    std::vector<Projectile*> projectiles;

    //methods
    void init();
    void init(RpgTileGridScene* gameScene);
};

