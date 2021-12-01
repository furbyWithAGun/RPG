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
	Building* buildingToReturn = createNewBuildingNoId(newBuildingType, direction);
	buildingToReturn->id = getUniqueBuildingId();
	return buildingToReturn;
}

Building* createNewBuildingNoId(int newBuildingType, int direction)
{
	Building* buildingToReturn;

	switch (newBuildingType)
	{
	case BUILDING_ITEM_SHOP:
		buildingToReturn = new ItemShop(direction);
		break;
	case BUILDING_CAMP_COMMAND_CENTRE:
		buildingToReturn = new CampCommandCentre(direction);
		break;
	case BUILDING_BARRACKS:
		buildingToReturn = new Barracks(direction);
		break;
	case BUILDING_WOODCUTTER:
		buildingToReturn = new WoodCutter(direction);
		break;
	default:
		printf("Warning: creating blank Building() from building factory");
		buildingToReturn = new Building();
		break;
	}
	return buildingToReturn;
}