#pragma once
#include "DooDad.h"

class CampFire : public DooDad
{
public:
	//contructors
	CampFire();
	CampFire(TileGridScene* gameScene, int textureKey, int tileX, int tileY);
	CampFire(TileGridScene* gameScene, int tileX, int tileY);
	CampFire(TileGridScene* gameScene);
	CampFire(SaveObject saveObject, TileGridScene* gameScene);

	//methods
	void actionOn(Unit* unit, int actionType) override;

private:
	void init();
};

