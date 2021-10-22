#include "BuildingFactory.h"


struct BuildingTemplate {
	int buildingType;
};

std::unordered_map<int, BuildingTemplate> buildingTemplates = {
	{BUILDING_ITEM_SHOP, BuildingTemplate{
		BUILDING_ITEM_SHOP
	}}
};

Building* createNewBuilding(int newBuildingType, int direction)
{
	Building* buildingToReturn;
	//BuildingTemplate buildingTemplate = buildingTemplates[newBuildingType];*/

	switch (newBuildingType)
	{
	case BUILDING_ITEM_SHOP:
		buildingToReturn = new ItemShop(direction);
		return buildingToReturn;
		break;
	default:
		printf("Warning: creating blank Building() from building factory");
		return new Building();
		break;
	}
}
