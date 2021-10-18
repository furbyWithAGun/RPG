#pragma once
#include "Sprite.h"

enum DOODAD_ATTRIBUTES {
	DOODAD_TEXTURE_ID,
	DOODAD_TYPE,
	DOODAD_TILE_COORDS,
};

class TileGridScene;
class Unit;

class DooDad : public Sprite
{
public:
	//attributes
	TileGridScene* scene;
	std::vector <int> tileCoords;
	int type;

	//contructors
	DooDad();
	DooDad(TileGridScene* gameScene, int textureKey, int tileX, int tileY);
	DooDad(SaveObject saveObject);
	
	//methods
	virtual void walkOn(Unit* unit);
	virtual void actionOn(Unit* unit);
	std::string DooDad::toSaveString();

private:
	void init();
};

