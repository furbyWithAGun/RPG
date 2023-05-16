#include "DooDadFactory.h"
#include "TileGridScene.h"


std::unordered_map<int, int> SPAWNER_TEXTURE_MAP = { {RAT, TEXTURE_RAT_SPAWNER},
												{WHITE_RAT, TEXTURE_RAT_SPAWNER},
												{SKELETON, TEXTURE_RAT_SPAWNER},
};

DooDad* createNewDooDad(int dooDadType, TileGridScene* gameScene, int zoneId)
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
	case DOODAD_TREASURE_CHEST:
		dooDadToReturn = new TreasureChest(gameScene);
		break;
	case DOODAD_CAMP_FIRE:
		dooDadToReturn = new CampFire(gameScene);
		break;
	case DOODAD_MINEBLOCK:
		dooDadToReturn = new MineBlock(gameScene);
		break;
	default:
		printf("Warning: creating blank DooDad() from DooDad factory");
		dooDadToReturn = new DooDad(gameScene);
		break;
	}
	dooDadToReturn->zoneId = zoneId;
	return dooDadToReturn;
}

DooDad* createNewDooDad(int dooDadType, int newTextureKey, TileGridScene* gameScene, int zoneId)
{
	DooDad* dooDadToReturn = createNewDooDad(dooDadType, gameScene, zoneId);
	dooDadToReturn->addTextureKey(newTextureKey);
	return dooDadToReturn;
}

DooDad* restoreDoodadFromSaveObject(SaveObject savedDoodad, TileGridScene* gameScene)
{
	for (int j = 0; j < savedDoodad.attributes.size(); j++)
	{
		if (savedDoodad.attributes[j].attributeType == DOODAD_TYPE)
		{
			switch (stoi(savedDoodad.attributes[j].valueString)) {
			case HEALING_PAD:
				return new HealingPad(savedDoodad.rawString, gameScene);
				break;
			case DOODAD_TOWN_COMMAND:
				return new TownCommand(savedDoodad.rawString, gameScene);
				break;
			case DOODAD_TREE:
				return new Tree(savedDoodad.rawString, gameScene);
				break;
			case DOODAD_APPLE_TREE:
				return new FruitTree(savedDoodad.rawString, gameScene);
				break;
			case DOODAD_RASPBERRY_BUSH:
				return new BerryBush(savedDoodad.rawString, gameScene);
				break;
			case DOODAD_UNIT_SPAWNER:
				return new UnitSpawner(savedDoodad.rawString, gameScene);
				break;
			case DOODAD_TREASURE_CHEST:
				return new TreasureChest(savedDoodad.rawString, gameScene);
				break;
			case DOODAD_CAMP_FIRE:
				return new CampFire(savedDoodad.rawString, gameScene);
				break;
			case DOODAD_MINEBLOCK:
				return new MineBlock(savedDoodad.rawString, gameScene);
				break;
			default:
				return new DooDad(savedDoodad.rawString, gameScene);
				break;
			}
			break;
		}
	}
}

UnitSpawner* createNewUnitSpawner(TileGridScene* gameScene, int newUnitToSpawn, int zoneId)
{
	UnitSpawner* spawnerToReturn = new UnitSpawner(gameScene, newUnitToSpawn, zoneId);
	spawnerToReturn->addTextureKey(SPAWNER_TEXTURE_MAP[newUnitToSpawn]);
	return spawnerToReturn;
}
