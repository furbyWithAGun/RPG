#pragma once
#include "DooDad.h"
#include <vector>

enum TREASURE_CHEST_SAVE_ATTRIBUTES {
	TREASURE_CHEST_CLOSED = NUM_DOODAD_ATTRIBUTES,
};



class TreasureChest : public DooDad
{
public:
	//attributes
	bool closed;

	//contructors
	TreasureChest();
	TreasureChest(TileGridScene* gameScene, int textureKey, int tileX, int tileY);
	TreasureChest(TileGridScene* gameScene, int tileX, int tileY);
	TreasureChest(TileGridScene* gameScene);
	TreasureChest(SaveObject saveObject, TileGridScene* gameScene);

	//methods
	void actionOn(Unit* unit, int actionType) override;
	virtual std::string toSaveString(bool withHeaderAndFooter = true);

private:
	void init();
	void openChest(RpgUnit* unit);
	std::vector<Item*> getDrops();
};

