#pragma once
#include "DooDad.h"
class Furnace : public DooDad
{
public:
	//contructors
	Furnace();
	Furnace(TileGridScene* gameScene, int textureKey, int tileX, int tileY);
	Furnace(TileGridScene* gameScene, int tileX, int tileY);
	Furnace(TileGridScene* gameScene);
	Furnace(SaveObject saveObject, TileGridScene* gameScene);

	//methods
	void actionOn(Unit* unit, int actionType) override;

private:
	void init();
};

