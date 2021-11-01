#pragma once
#include <unordered_map>
#include "Tree.h"
#include "HealingPad.h"
#include "TownCommand.h"

DooDad* createNewDooDad(int dooDadType, TileGridScene* gameScene);
DooDad* createNewDooDad(int dooDadType, int newTextureKey, TileGridScene* gameScene);