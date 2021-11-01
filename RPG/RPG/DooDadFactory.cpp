#include "DooDadFactory.h"

DooDad* createNewDooDad(int dooDadType, TileGridScene* gameScene)
{
	DooDad* dooDadToReturn;
	switch (dooDadType)
	{
	case DOODAD_TREE:
		dooDadToReturn = new Tree(gameScene);
		break;
	case DOODAD_TREE_2:
		dooDadToReturn = new Tree(gameScene);
		dooDadToReturn->addTextureKey(TREE_2);
		dooDadToReturn->type = DOODAD_TREE_2;
		break;
	case DOODAD_TREE_3:
		dooDadToReturn = new Tree(gameScene);
		dooDadToReturn->addTextureKey(TREE_3);
		dooDadToReturn->type = DOODAD_TREE_3;
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
