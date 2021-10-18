#include "BareHands.h"

BareHands::BareHands() : Weapon()
{
	init();
}

void BareHands::init()
{
	name = "Bare Hands";
	maxDamage = 3;
}
