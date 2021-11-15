#pragma once
#include "Sprite.h"
#include "Building.h"

enum DOODAD_ATTRIBUTES {
	DOODAD_TEXTURE_ID,
	DOODAD_TYPE,
	DOODAD_TILE_COORDS,
	DOODAD_PASSABLE,
	DOODAD_ASSIGNED_TO_BUILDING,
	DOODAD_ZONE_ID,
	DOODAD_HEALTH,
	DOODAD_MAX_HEALTH,
	DOODAD_CAN_BE_DAMAGED,
	NUM_DOODAD_ATTRIBUTES
};

class TileGridScene;
class Unit;

class DooDad : public Sprite
{
public:
	//attributes
	TileGridScene* scene;
	int zoneId;
	std::vector <int> tileCoords;
	int type;
	bool passable;
	Building* assignedToBuilding;
	bool canBeDamaged;
	int health;
	int maxHealth;

	//special attributes for loading saved dooDads
	int assignedToBuildingId;

	//contructors
	DooDad();
	DooDad(TileGridScene* gameScene, int textureKey, int tileX, int tileY);
	DooDad(TileGridScene* gameScene, int tileX, int tileY);
	DooDad(TileGridScene* gameScene);
	DooDad(SaveObject saveObject, TileGridScene* gameScene);
	
	//methods
	virtual void walkOn(Unit* unit);
	virtual void actionOn(Unit* unit, int actionType);
	virtual std::string toSaveString(bool withHeaderAndFooter = true);
	virtual void update() {};
	virtual void assignDamage(int damage);
	virtual void assignDamage(Unit* unit, int damage);
	void drawHealth();

private:
	void init();
	void init(TileGridScene* gameScene);
};

