#include "UnitFactory.h"
#include "GameScene.h"
#include "MenuText.h"


Unit* createNewUnit(ZoneMap* zone, RpgTileGridScene* gameScene, int unitType)
{
	Unit* unitToReturn;
	
	unitToReturn = createNewUnitBlankId(zone, gameScene, unitType);
	unitToReturn->id = getUniqueUnitId();
	return unitToReturn;
}

Unit* createNewUnitBlankId(ZoneMap* zone, RpgTileGridScene* gameScene, int unitType)
{
	Unit* createdUnit;
	switch (unitType)
	{
	case PLAYER:
		createdUnit = new Player(zone->id, PLAYER, gameScene);
		break;
	case RAT:
		createdUnit = new Rat(zone->id, RAT, gameScene);
		break;
	case RAT_KING:
		createdUnit = new RatKing(zone->id, RAT_KING, gameScene);
		break;
	case WHITE_RAT:
		createdUnit = new WhiteRat(zone->id, WHITE_RAT, gameScene);
		break;
	case SOLDIER:
		createdUnit = new Soldier(zone->id, SOLDIER, gameScene);
		break;
	case TOWNSPERSON:
		createdUnit = new TownsPerson(zone->id, TOWNSPERSON, gameScene);
		break;
	case SKELETON:
		createdUnit = new Skeleton(zone->id, SKELETON, gameScene);
		break;
	case SKELETON_KING:
		createdUnit = new SkeletonKing(zone->id, SKELETON_KING, gameScene);
		break;
	default:
		createdUnit = NULL;
		break;
	}

	return createdUnit;
}

Unit* restoreUnitFromSaveObject(SaveObject savedUnit, RpgTileGridScene* gameScene)
{
	for (int j = 0; j < savedUnit.attributes.size(); j++)
	{
		if (savedUnit.attributes[j].attributeType == UNIT_TYPE)
		{
			switch (stoi(savedUnit.attributes[j].valueString)) {
			case PLAYER:
				return new Player(savedUnit.rawString, gameScene);
				break;
			case RAT:
				return new Rat(savedUnit.rawString, gameScene);
				break;
			case SOLDIER:
				return new Soldier(savedUnit.rawString, gameScene);
				break;
			case TOWNSPERSON:
				return new TownsPerson(savedUnit.rawString, gameScene);
				break;
			case WHITE_RAT:
				return new WhiteRat(savedUnit.rawString, gameScene);
				break;
			case RAT_KING:
				return new RatKing(savedUnit.rawString, gameScene);
				break;
			case SKELETON:
				return new Skeleton(savedUnit.rawString, gameScene);
				break;
			case SKELETON_KING:
				return new SkeletonKing(savedUnit.rawString, gameScene);
				break;
			default:
				return new RpgUnit(savedUnit.rawString, gameScene);
				break;
			}
			break;
		}
	}
}
