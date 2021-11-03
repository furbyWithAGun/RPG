#pragma once
#include "DooDad.h"

const int BERRY_BUSH_REGROW_TIME = 10000;

enum BERRY_BUSH_SAVE_ATTRIBUTES {
	BERRY_BUSH_BERRY_GROWN = NUM_DOODAD_ATTRIBUTES,
	BERRY_BUSH_BERRY_REGROW_TICK,
	BERRY_BUSH_BERRY_STATE,
	BERRY_BUSH_GROWN_BERRY_TEXTURE_KEY,
	BERRY_BUSH_NO_BERRY_TEXTURE_KEY
};

enum BERRY_BUSH_STATES {
	BERRY_BUSH_NO_BERRIES,
	BERRY_BUSH_AVAILABLE_BERRIES
};

class BerryBush : public DooDad
{
public:
	//attributes
	int berryGrown;
	int berryRegrowTick;
	int berryState;
	int grownBerryTextureKey;
	int noBerryTextureKey;

	//contructors
	BerryBush();
	BerryBush(TileGridScene* gameScene, int textureKey, int tileX, int tileY);
	BerryBush(TileGridScene* gameScene, int tileX, int tileY);
	BerryBush(TileGridScene* gameScene);
	BerryBush(TileGridScene* gameScene, int berryToGrow);
	BerryBush(SaveObject saveObject, TileGridScene* gameScene);

	//methods
	void actionOn(Unit* unit, int actionType) override;
	void update() override;
	virtual std::string toSaveString(bool withHeaderAndFooter = true);

private:
	void init();
};

