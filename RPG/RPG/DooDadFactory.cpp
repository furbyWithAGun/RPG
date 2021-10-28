#include "DooDadFactory.h"

DooDad* createNewDooDad(int dooDadType, TileGridScene* gameScene)
{
	DooDad* dooDadToReturn;
	switch (dooDadType)
	{
	case DOODAD_TREE:
		dooDadToReturn = new Tree(gameScene);
		break;
	case DOODAD_TOWN_COMMAND:
		dooDadToReturn = new TownCommand(gameScene);
		break;
	case HEALING_PAD:
		dooDadToReturn = new HealingPad(gameScene);
		break;
	default:
		printf("Warning: creating blank DooDad() from DooDad factory");
		dooDadToReturn = new DooDad(gameScene);
		break;
	}
	return dooDadToReturn;
}
