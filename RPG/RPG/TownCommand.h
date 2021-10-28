#pragma once
#include "DooDad.h"
#include "SelectPrompt.h"

class TownCommand : public DooDad
{
public:
	//contructors
	TownCommand();
	TownCommand(TileGridScene* gameScene, int textureKey, int tileX, int tileY);
	TownCommand(TileGridScene* gameScene, int tileX, int tileY);
	TownCommand(TileGridScene* gameScene);
	TownCommand(SaveObject saveObject, TileGridScene* gameScene);

	//methods
	void actionOn(Unit* unit, int actionType) override;

private:
	void init();
};

