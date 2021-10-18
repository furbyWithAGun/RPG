#include "BuildingTile.h"

BuildingTile::BuildingTile() : MapTile()
{
	init();
}

BuildingTile::BuildingTile(bool tileIsPassable, int tileTextureKey) : MapTile(tileIsPassable, tileTextureKey)
{
	init();
}

BuildingTile::BuildingTile(bool tileIsPassable, int tileIsDestructable, int tileTextureKey) : MapTile(tileIsPassable, tileTextureKey)
{
	init();
	destructable = tileIsDestructable;
}

bool BuildingTile::isDamagable()
{
	if (destructable && health > 0)
	{
		return true;
	}
	return false;
}

bool BuildingTile::isPassable()
{
	if (passable || health <= 0)
	{
		return true;
	}
	return false;
}

void BuildingTile::init()
{
	destructable = false;
	maxHealth = 1;
	health = 1;
}
void BuildingTile::init(int tileTextureKey)
{
	init();
	textureKey = tileTextureKey;
}

