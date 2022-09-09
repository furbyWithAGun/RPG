#include "UnitSpawner.h"
#include "RpgTileGridScene.h"
#include "RpgOverWorldScene.h"

UnitSpawner::UnitSpawner() : DooDad()
{
    init();
}

UnitSpawner::UnitSpawner(TileGridScene* gameScene, int newUnitToSpawn, int zone) : DooDad(gameScene)
{
    init();
    zoneId = zone;
    scene = gameScene;
    unitToSpawn = newUnitToSpawn;
}

UnitSpawner::UnitSpawner(SaveObject saveObject, TileGridScene* gameScene) :DooDad(saveObject, gameScene)
{
    init();
    scene = gameScene;
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case DOODAD_TEXTURE_ID:
            textureKey = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_SPAWNER_UNIT_TO_SPAWN:
            unitToSpawn = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_SPAWNER_SPAWN_DELAY:
            spawnDelay = stoi(saveObject.attributes[i].valueString);
            break;
        case UNIT_SPAWNER_SPAWN_TICK:
            spawnTick = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
}

void UnitSpawner::actionOn(Unit* unit, int actionType)
{
    switch (actionType)
    {
    case OVERWORLD_STRIKE:
        health -= 1;
        if (health <= 0)
        {
            active = false;
        }
        break;
    default:
        break;
    }
}

void UnitSpawner::update()
{
    spawnTick++;
    if (spawnTick >= spawnDelay)
    {
        spawnTick = 0;
        if (scene->engine->getProbFromSigmoid(scene->getZone(zoneId)->getDifficulty() + 100, scene->getZone(zoneId)->getDevelopmentLevel() + scene->getZone(zoneId)->getNumUnits() * 2) > scene->engine->randomDouble())
        {
            //if (scene->getUnitAtLocation(zoneId, tileCoords[0], tileCoords[1]) == nullptr){
            for (size_t i = 0; i < 10; i++)
            {

                RpgUnit* newUnit = ((RpgTileGridScene*)scene)->createUnitAtLocation(zoneId, unitToSpawn, tileCoords[0], tileCoords[1]);
                Location* newTargetLocation = ((RpgZone*)scene->getZone(zoneId))->getNearestTownLocation(newUnit->tileLocation);
                newUnit->setTargetLocation(newTargetLocation);
                delete newTargetLocation;
            }
        }
    }
}

std::string UnitSpawner::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_UNIT_SPAWNER) + "\n";
    }
    saveString += DooDad::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), UNIT_SPAWNER_UNIT_TO_SPAWN, unitToSpawn);
    saveString += getAttributeString(getUniqueId(), UNIT_SPAWNER_SPAWN_DELAY, spawnDelay);
    saveString += getAttributeString(getUniqueId(), UNIT_SPAWNER_SPAWN_TICK, spawnTick);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_UNIT_SPAWNER) + "\n";
    }
    return saveString;
}

void UnitSpawner::assignDamage(Unit* unit, int damage)
{
    DooDad::assignDamage(unit, damage);
    if (health <= 0)
    {
        int goldGiven = scene->engine->randomInt(1, 300);
        if (zoneId == scene->currentZone->id)
        {
            ((RpgTileGridScene*)scene)->addDelayedCombatMessage(15, "+" + std::to_string(goldGiven) + " Gold", COLOR_GOLD, tileCoords[0], tileCoords[1], 140);
        }
        ((RpgUnit*)unit)->gold += goldGiven;
    }
}

void UnitSpawner::init()
{
    unitToSpawn = -1;
    spawnDelay = DEFAULT_UNIT_SPAWN_DELAY;
    spawnTick = 0;
    passable = false;
    health = DEFAULT_MAX_HEALTH;
    maxHealth = DEFAULT_MAX_HEALTH;
    type = DOODAD_UNIT_SPAWNER;
    canBeDamaged = true;
}
