#pragma once
#include "DooDad.h"
#include "ItemFactory.h"
const int TREE_REGROW_TIME = 100000;

enum TREE_SAVE_ATTRIBUTES {
	TREE_HEALTH = NUM_DOODAD_ATTRIBUTES,
	TREE_MAX_HEALTH,
	TREE_STATE,
	TREE_REGROW_TICK,
	NUM_TREE_SAVE_ATTRIBUTES
};

enum TREE_STATES {
	TREE_STATE_CUT,
	TREE_STATE_GROWING,
	TREE_STATE_FULLY_GROWN
};

enum TREE_VARIATIONS {
	TREE_TYPE_ONE,
	TREE_TYPE_TWO,
	TREE_TYPE_THREE,
	NUM_TREE_VARIATIONS
};


class Tree : public DooDad
{
public:
	//attributes
	int health, maxhealth, state, regrowTick;
	//contructors
	Tree();
	Tree(TileGridScene* gameScene, int textureKey, int tileX, int tileY);
	Tree(TileGridScene* gameScene, int tileX, int tileY);
	Tree(TileGridScene* gameScene);
	Tree(SaveObject saveObject, TileGridScene* gameScene);

	//methods
	virtual void actionOn(Unit* unit, int actionType) override;
	virtual void update() override;
	virtual std::string toSaveString(bool withHeaderAndFooter = true);

private:
	void init();
};

