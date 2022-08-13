#pragma once
#include "Tree.h"

const int FRUIT_TREE_REGROW_TIME = 20000;

enum FRUIT_TREE_SAVE_ATTRIBUTES {
	FRUIT_TREE_FRUIT_GROWN = NUM_TREE_SAVE_ATTRIBUTES,
	FRUIT_TREE_FRUIT_REGROW_TICK,
	FRUIT_TREE_FRUIT_STATE,
	FRUIT_TREE_GROWN_FRUIT_TEXTURE_KEY,
	FRUIT_TREE_NO_FRUIT_TEXTURE_KEY
};

enum FRUIT_TREE_STATES {
	FRUIT_TREE_NO_FRUIT,
	FRUIT_TREE_AVAILABLE_FRUIT
};

class FruitTree : public Tree
{
public:
	//attributes
	int fruitGrown;
	int fruitRegrowTick;
	int fruitState;
	int grownFruitTextureKey;
	int noFruitTextureKey;

	//contructors
	FruitTree();
	FruitTree(TileGridScene* gameScene, int textureKey, int tileX, int tileY);
	FruitTree(TileGridScene* gameScene, int tileX, int tileY);
	FruitTree(TileGridScene* gameScene);
	FruitTree(TileGridScene* gameScene, int fruitToGrow);
	FruitTree(SaveObject saveObject, TileGridScene* gameScene);

	//methods
	void actionOn(Unit* unit, int actionType) override;
	void update() override;
	virtual std::string toSaveString(bool withHeaderAndFooter = true);

private:
	void init();
};

