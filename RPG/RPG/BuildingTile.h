#pragma once
#include "MapTile.h"
#include "SaveObject.h"
#include "RpgGameConstants.h"

enum BUILDING_TILE_SAVE_ATTRIBUTES {
	BUILDING_TILE_DESTRUCTABLE = NUM_MAP_TILE_SAVE_ATTRIBUTES,
	BUILDING_TILE_MAX_HEALTH,
	BUILDING_TILE_HEALTH
};

class BuildingTile :  public MapTile
{
public:
	//Attributes
	bool destructable;
	int maxHealth;
	int health;

	//Constructor
	BuildingTile();
	BuildingTile(SaveObject saveObject);
	BuildingTile(bool tileIsPassable, int tileTextureKey);
	BuildingTile(bool tileIsPassable, int tileIsDestructable, int tileTextureKey);

	//methods
	bool isDamagable();
	bool isPassable();
	std::string toSaveString();

private:
	//methods
	void init();
	void init(int tileTextureKey);
};

