#pragma once
#include "Player.h"
#include "Rat.h"
#include "RatKing.h"
#include "Skeleton.h"
#include "SkeletonKing.h"
#include "Soldier.h"
#include "TownsPerson.h"
#include "WhiteRat.h"
//class GameScene;

Unit* createNewUnit(ZoneMap* zone, RpgTileGridScene* gameScene, int unitType);
Unit* createNewUnitBlankId(ZoneMap* zone, RpgTileGridScene* gameScene, int unitType);
Unit* restoreUnitFromSaveObject(SaveObject savedUnit, RpgTileGridScene* gameScene);

//std::string getUnitVectorSaveString(std::vector<Item*> vector);
//std::vector<Item*> getUnitVectorFromSaveString(std::string saveString);