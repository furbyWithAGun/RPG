#pragma once
#include "MapTile.h"
class BuildingTile :  public MapTile
{
public:
	//Attributes
	bool destructable;
	int maxHealth;
	int health;

	//Constructor
	BuildingTile();
	BuildingTile(bool tileIsPassable, int tileTextureKey);
	BuildingTile(bool tileIsPassable, int tileIsDestructable, int tileTextureKey);

	//methods
	bool isDamagable();
	bool isPassable();

private:
	//methods
	void init();
	void init(int tileTextureKey);
};

