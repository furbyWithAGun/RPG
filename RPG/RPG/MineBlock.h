#pragma once
#include "DooDad.h"
#include "ItemFactory.h"
const int MINEBLOCK_REGROW_TIME = 7000000;

enum MINEBLOCK_SAVE_ATTRIBUTES {
	MINEBLOCK_HEALTH = NUM_DOODAD_ATTRIBUTES,
	MINEBLOCK_MAX_HEALTH,
	MINEBLOCK_STATE,
	MINEBLOCK_REGROW_TICK,
	NUM_MINEBLOCK_SAVE_ATTRIBUTES
};

enum MINEBLOCK_STATES {
	MINEBLOCK_STATE_DEPLETED,
	MINEBLOCK_STATE_FULL
};



class MineBlock : public DooDad
{
public:
	//attributes
	int health, maxhealth, state, regrowTick;
	//contructors
	MineBlock();
	MineBlock(TileGridScene* gameScene, int textureKey, int tileX, int tileY);
	MineBlock(TileGridScene* gameScene, int tileX, int tileY);
	MineBlock(TileGridScene* gameScene);
	MineBlock(SaveObject saveObject, TileGridScene* gameScene);

	//methods
	virtual void actionOn(Unit* unit, int actionType) override;
	virtual void update() override;
	virtual std::string toSaveString(bool withHeaderAndFooter = true);

private:
	void init();
};

