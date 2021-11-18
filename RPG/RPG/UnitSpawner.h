#pragma once
#include "DooDad.h"

const int DEFAULT_UNIT_SPAWN_DELAY = 1000;
const int DEFAULT_MAX_HEALTH = 100;

enum UNIT_SPAWNER_SAVE_ATTRIBUTES {
	UNIT_SPAWNER_UNIT_TO_SPAWN = NUM_DOODAD_ATTRIBUTES,
	UNIT_SPAWNER_SPAWN_DELAY,
	UNIT_SPAWNER_SPAWN_TICK
};

class UnitSpawner : public DooDad
{
public:
    //constructors
    UnitSpawner();
    UnitSpawner(TileGridScene* gameScene, int unitToSpawn, int zone);
    UnitSpawner(SaveObject saveObject, TileGridScene* gameScene);

    //methods
    void actionOn(Unit* unit, int actionType) override;
    void update() override;
    virtual std::string toSaveString(bool withHeaderAndFooter = true);
    void assignDamage(Unit* unit, int damage) override;

private:
    //attributes
    int unitToSpawn;
    int spawnDelay;
    int spawnTick;

    //methods
    void init();
};

