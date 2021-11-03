#include "DooDadFactory.h"
#include "TileGridScene.h"

DooDad* createNewDooDad(int dooDadType, TileGridScene* gameScene)
{
	std::unordered_map<int, int> treeTextureMap = { {TREE_TYPE_ONE, TREE},
												{TREE_TYPE_TWO, TREE_2},
												{TREE_TYPE_THREE, TREE_3},
	};
	DooDad* dooDadToReturn;
	int newTextureKey;
	switch (dooDadType)
	{
	case DOODAD_TREE:
		dooDadToReturn = new Tree(gameScene);
		newTextureKey = treeTextureMap[gameScene->engine->randomInt(0, NUM_TREE_VARIATIONS - 1)];
		dooDadToReturn->addTextureKey(newTextureKey);
		break;
	case DOODAD_TOWN_COMMAND:
		dooDadToReturn = new TownCommand(gameScene);
		break;
	case HEALING_PAD:
		dooDadToReturn = new HealingPad(gameScene);
		break;
	case DOODAD_APPLE_TREE:
		dooDadToReturn = new FruitTree(gameScene, ITEM_APPLE);
		dooDadToReturn->textureKey = TEXTURE_APPLE_TREE_WITH_FRUIT;
		dooDadToReturn->type = DOODAD_APPLE_TREE;
		((FruitTree*)dooDadToReturn)->grownFruitTextureKey = TEXTURE_APPLE_TREE_WITH_FRUIT;
		((FruitTree*)dooDadToReturn)->noFruitTextureKey = TEXTURE_APPLE_TREE_NO_FRUIT;
		break;
	case DOODAD_RASPBERRY_BUSH:
		dooDadToReturn = new BerryBush(gameScene, ITEM_RASPBERRY);
		dooDadToReturn->textureKey = TEXTURE_RASPBERRY_BUSH_WITH_BERRIES;
		dooDadToReturn->type = DOODAD_RASPBERRY_BUSH;
		((BerryBush*)dooDadToReturn)->grownBerryTextureKey = TEXTURE_RASPBERRY_BUSH_WITH_BERRIES;
		((BerryBush*)dooDadToReturn)->noBerryTextureKey = TEXTURE_RASPBERRY_BUSH_NO_BERRIES;
		break;
	default:
		printf("Warning: creating blank DooDad() from DooDad factory");
		dooDadToReturn = new DooDad(gameScene);
		break;
	}
	return dooDadToReturn;
}

DooDad* createNewDooDad(int dooDadType, int newTextureKey, TileGridScene* gameScene)
{
	DooDad* dooDadToReturn = createNewDooDad(dooDadType, gameScene);
	dooDadToReturn->addTextureKey(newTextureKey);
	return dooDadToReturn;
}
