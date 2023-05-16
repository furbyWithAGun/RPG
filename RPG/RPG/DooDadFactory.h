#pragma once
#include <unordered_map>
#include "Tree.h"
#include "HealingPad.h"
#include "TownCommand.h"
#include "FruitTree.h"
#include "BerryBush.h"
#include "UnitSpawner.h"
#include "TreasureChest.h"
#include "CampFire.h"
#include "MineBlock.h"



DooDad* createNewDooDad(int dooDadType, TileGridScene* gameScene, int zoneId);
DooDad* createNewDooDad(int dooDadType, int newTextureKey, TileGridScene* gameScene, int zoneId);
DooDad* restoreDoodadFromSaveObject(SaveObject savedDoodad, TileGridScene* gameScene);
UnitSpawner* createNewUnitSpawner(TileGridScene* gameScene, int newUnitToSpawn, int zoneId);