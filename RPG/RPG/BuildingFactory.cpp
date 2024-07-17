#include "BuildingFactory.h"
#include "MenuText.h"


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
	case BUILDING_HOUSE:
		buildingToReturn = new House(direction);
		break;
	case BUILDING_GUARDHOUSE:
		buildingToReturn = new GuardHouse(direction);
		break;
	case BUILDING_APPLE_ORCHARD:
		buildingToReturn = new Orchard(direction);
		break;
	case BUILDING_SMELTING_WORKS:
		buildingToReturn = new SmeltingWorks(direction);
		break;
	default:
		printf("Warning: creating blank Building() from building factory");
		buildingToReturn = new Building();
		break;
	}
	return buildingToReturn;
}

Building* restoreBuildingFromSaveObject(SaveObject savedBuilding)
{
	for (int j = 0; j < savedBuilding.attributes.size(); j++)
	{
		if (savedBuilding.attributes[j].attributeType == BULDING_TYPE)
		{
			switch (stoi(savedBuilding.attributes[j].valueString)) {
				case BUILDING_ITEM_SHOP:
					return new ItemShop(savedBuilding.rawString);
					break;
				case BUILDING_CAMP_COMMAND_CENTRE:
					return new CampCommandCentre(savedBuilding.rawString);
					break;
				case BUILDING_BARRACKS:
					return new Barracks(savedBuilding.rawString);
					break;
				case BUILDING_WOODCUTTER:
					return new WoodCutter(savedBuilding.rawString);
					break;
				case BUILDING_HOUSE:
					return new House(savedBuilding.rawString);
					break;
				case BUILDING_GUARDHOUSE:
					return new GuardHouse(savedBuilding.rawString);
					break;
				case BUILDING_APPLE_ORCHARD:
					return new Orchard(savedBuilding.rawString);
					break;
				case BUILDING_SMELTING_WORKS:
					return new SmeltingWorks(savedBuilding.rawString);
					break;
				default:
					return new Building(savedBuilding.rawString);
					break;
				}
			break;
		}
	}
}

HoverToolTip* createBuildBuildingToolTip(Building* building, GameScene* scene)
{
	HoverToolTip* returnToolTip = new HoverToolTip();
	returnToolTip->setdimensions(scene->engine->screenWidth * 0.15, scene->engine->screenHeight * 0.2);
	returnToolTip->subElements.push_back(new MenuText(scene,building->getBuildingName(), COLOR_WHITE, 10, 10));
	if (building->goldCost > 0)
	{
		returnToolTip->subElements.push_back(new MenuText(scene, "Gold Cost: " + std::to_string(building->goldCost), COLOR_WHITE, 10, 40));
	}
	if (building->woodCost > 0)
	{
		returnToolTip->subElements.push_back(new MenuText(scene, "Wood Cost: " + std::to_string(building->woodCost), COLOR_WHITE, 10, 70));
	}

	else if (building->getPopSupported() > 0) {
		returnToolTip->subElements.push_back(new MenuText(scene, "Population Supported: " + std::to_string(building->getPopSupported()), COLOR_WHITE, 10, 100, scene->engine->screenWidth * 0.14, scene->engine->screenHeight * 0.03));
	}
	

	returnToolTip->setScene(scene);
	return returnToolTip;
}
