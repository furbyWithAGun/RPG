#include <unordered_map>
#include "ItemShop.h"
#include "CampCommandCentre.h"
#include "Barracks.h"
#include "woodCutter.h"
#include "house.h"
#include "GuardHouse.h"
#include "Orchard.h"
#include "SmeltingWorks.h"

Building* createNewBuilding(int BuildingType, int direction);
Building* createNewBuildingNoId(int BuildingType, int direction);
HoverToolTip* createBuildBuildingToolTip(Building* building, GameScene* scene);