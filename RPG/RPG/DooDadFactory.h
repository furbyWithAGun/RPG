#pragma once
#include <unordered_map>
#include "Tree.h"
#include "HealingPad.h"
#include "TownCommand.h"
#include "FruitTree.h"
#include "BerryBush.h"

DooDad* createNewDooDad(int dooDadType, TileGridScene* gameScene);
DooDad* createNewDooDad(int dooDadType, int newTextureKey, TileGridScene* gameScene);