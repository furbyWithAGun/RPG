#include "RpgZone.h"
#include "RpgUnit.h"

RpgZone::RpgZone(int newId, std::vector<std::vector<int>> tiles, RpgTileGridScene* gameScene) : ZoneMap(newId, tiles)
{
    init(gameScene);
}

RpgZone::RpgZone(int newId, RpgTileGridScene* gameScene) : ZoneMap(newId)
{
    init(gameScene);
}

RpgZone::RpgZone(SaveObject saveObject, RpgTileGridScene* gameScene) : ZoneMap(saveObject, gameScene)
{
    init(gameScene);
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case RPG_ZONE_TYPE:
            zoneType = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
}

RpgZone::RpgZone(const RpgZone& oldMap) : ZoneMap(oldMap)
{
    init();
    zoneType = oldMap.zoneType;
    scene = oldMap.scene;
}

RpgZone::RpgZone() : ZoneMap()
{
    init();
}

RpgZone::RpgZone(int zoneWidth, int zoneHeight) : ZoneMap(zoneWidth, zoneHeight)
{
    init();
}

std::string RpgZone::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_RPG_ZONE) + "\n";
    }
    saveString += ZoneMap::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), RPG_ZONE_TYPE, zoneType);
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_RPG_ZONE) + "\n";
    }
    return saveString;
}


int RpgZone::getNumUnits()
{
    return getUnits().size();
}

int RpgZone::getNumUnitsOnTeam(int team)
{
    int numUnitsOnTeam = 0;

    for (auto* unit : getUnits()) {
        if (((RpgUnit*)unit)->team == team)
        {
            numUnitsOnTeam++;
        }
    }

    return numUnitsOnTeam;
}

RpgTown* RpgZone::getNearestTown(Location* location)
{
    return nullptr;
}

RpgTown* RpgZone::getNearestTown(int xpos, int ypos)
{
    return nullptr;
}

Location* RpgZone::getNearestTownLocation(Location* location)
{
    return nullptr;
}

Location* RpgZone::getNearestTownLocation(int xpos, int ypos)
{
    return nullptr;
}

void RpgZone::update()
{
    ZoneMap::update();

    for (auto building : getBuildings())
    {
        building->update(scene);
    }

    std::vector<Projectile*>::iterator iter;
    for (iter = projectiles.begin(); iter != projectiles.end(); ) {
        (*iter)->update();
        if ((*iter)->duration > (*iter)->maxDuration || !(*iter)->active)
            iter = projectiles.erase(iter);
        else
            ++iter;
    }
}

void RpgZone::draw(TileGridScene* scene)
{
    ZoneMap::draw(scene);
    for (Projectile* projectile : projectiles) {
        projectile->draw(projectile->xpos + scene->xOffset ,projectile->ypos + scene->yOffset);
    }
}

void RpgZone::addToProjectileVector(Projectile* projectileToAdd)
{
    if (std::find(projectiles.begin(), projectiles.end(), projectileToAdd) == projectiles.end())
    {
        projectiles.push_back(projectileToAdd);
    }
}

void RpgZone::removeFromProjectileVector(Projectile* projectileToRemove)
{
    auto projectileIterator = projectiles.begin();
    while (projectileIterator != projectiles.end())
    {
        if (*(projectileIterator) == projectileToRemove) {
            delete *projectileIterator;
            projectileIterator = projectiles.erase(projectileIterator);
        }
        else {
            projectileIterator++;
        }
    }
}

void RpgZone::init()
{
    zoneType = -1;
}

void RpgZone::init(RpgTileGridScene* gameScene)
{
    init();
    scene = gameScene;
}
