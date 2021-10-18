#include "HealingPad.h"
#include "Unit.h"

HealingPad::HealingPad() : DooDad()
{

}

HealingPad::HealingPad(TileGridScene* gameScene, int textureKey, int tileX, int tileY) : DooDad(gameScene, textureKey, tileX, tileY)
{
	init();
}

HealingPad::HealingPad(SaveObject saveObject) : DooDad(saveObject)
{
	init();
}

void HealingPad::walkOn(Unit* unit)
{
	unit->health = unit->maxHealth;
}

void HealingPad::init()
{
	type = HEALING_PAD;
}
