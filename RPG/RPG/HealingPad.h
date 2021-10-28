#pragma once
#include "DooDad.h"
class HealingPad : public DooDad
{
public:
	//contructors
	HealingPad();
	HealingPad(TileGridScene* gameScene, int textureKey, int tileX, int tileY);
	HealingPad(TileGridScene* gameScene);
	HealingPad(SaveObject saveObject, TileGridScene* gameScene);

	//methods
	void walkOn(Unit* unit) override;

private:
	void init();
};

