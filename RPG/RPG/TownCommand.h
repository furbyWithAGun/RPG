#pragma once
#include "DooDad.h"
#include "SelectPrompt.h"

class TownCommand : public DooDad
{
public:
	//contructors
	TownCommand();
	TownCommand(TileGridScene* gameScene, int textureKey, int tileX, int tileY);
	TownCommand(SaveObject saveObject);

	//methods
	void actionOn(Unit* unit) override;

private:
	void init();
};

