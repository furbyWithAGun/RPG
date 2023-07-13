#include "BuildingTile.h"

BuildingTile::BuildingTile() : MapTile()
{
	init();
}

BuildingTile::BuildingTile(SaveObject saveObject) :MapTile()
{
	init();
	for (int i = 0; i < saveObject.attributes.size(); i++)
	{
		switch (saveObject.attributes[i].attributeType) {
		case MAP_TILE_PASSABLE:
			passable = stoi(saveObject.attributes[i].valueString);
			break;
		case MAP_TILE_TEXTURE_KEY:
			textureKey = stoi(saveObject.attributes[i].valueString);
			break;
		case MAP_TILE_WIDTH:
			width = stoi(saveObject.attributes[i].valueString);
			break;
		case MAP_TILE_HEIGHT:
			height = stoi(saveObject.attributes[i].valueString);
			break;
		case BUILDING_TILE_DESTRUCTABLE:
			destructable = stoi(saveObject.attributes[i].valueString);
			break;
		case BUILDING_TILE_MAX_HEALTH:
			maxHealth = stoi(saveObject.attributes[i].valueString);
			break;
		case BUILDING_TILE_HEALTH:
			health = stoi(saveObject.attributes[i].valueString);
			break;
		default:
			break;
		}
	}
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
	if (passable == UNIT_PASSABLE || health <= 0)
	{
		return true;
	}
	return false;
}

std::string BuildingTile::toSaveString()
{
	std::string saveString;
	int uniqueObjectId = getUniqueId();

	saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_BULIDING_TILE) + "\n";
	saveString += getAttributeString(getUniqueId(), MAP_TILE_PASSABLE, passable);
	saveString += getAttributeString(getUniqueId(), MAP_TILE_TEXTURE_KEY, textureKey);
	saveString += getAttributeString(getUniqueId(), MAP_TILE_WIDTH, width);
	saveString += getAttributeString(getUniqueId(), MAP_TILE_HEIGHT, height);
	saveString += getAttributeString(getUniqueId(), BUILDING_TILE_DESTRUCTABLE, destructable);
	saveString += getAttributeString(getUniqueId(), BUILDING_TILE_HEALTH, health);
	saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_BULIDING_TILE) + "\n";

	return saveString;
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

