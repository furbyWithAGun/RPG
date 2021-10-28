#pragma once
#include "DooDad.h"
const int TREE_REGROW_TIME = 100000;

enum TREE_SAVE_ATTRIBUTES {
	TREE_HEALTH = NUM_DOODAD_ATTRIBUTES,
	TREE_MAX_HEALTH,
	TREE_STATE,
	TREE_REGROW_TICK
};

enum TREE_STATES {
	TREE_STATE_CUT,
	TREE_STATE_GROWING,
	TREE_STATE_FULLY_GROWN
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
	void actionOn(Unit* unit, int actionType) override;
	void update() override;
	virtual std::string toSaveString(bool withHeaderAndFooter = true);

private:
	void init();
};

