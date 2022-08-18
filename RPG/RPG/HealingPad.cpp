#include "HealingPad.h"
#include "Unit.h"

HealingPad::HealingPad() : DooDad()
{

}

HealingPad::HealingPad(TileGridScene* gameScene, int textureKey, int tileX, int tileY) : DooDad(gameScene, textureKey, tileX, tileY)
{
	init();
}

HealingPad::HealingPad(TileGridScene* gameScene) : DooDad(gameScene)
{
	init();
}

HealingPad::HealingPad(SaveObject saveObject, TileGridScene* gameScene) : DooDad(saveObject, gameScene)
{
	init();
}

void HealingPad::walkOn(Unit* unit)
{
	unit->setFullHealth();
}

void HealingPad::init()
{
	type = HEALING_PAD;
}
