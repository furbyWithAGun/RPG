#pragma once
#include "LinenBody.h"
#include "LinenBoots.h"
#include "LinenGloves.h"
#include "LinenHat.h"
#include "LinenPants.h"
#include "RagBody.h"
#include "RagBoots.h"
#include "RagGloves.h"
#include "RagHat.h"
#include "RagPants.h"
#include "ShortSword.h"
#include "LongSword.h"
#include "Club.h"
#include "Mace.h"
#include <unordered_map>
#include "Food.h";

Item* createNewItem(int itemType);
Item* createNewItemBlankId(int itemType);