#include "ZoneMap.h"
#include "BaseGameEngine.h"
#include "SaveFile.h"
#include "RpgGameConstants.h"
#include "Unit.h"
#include "TileGridScene.h"
#include "DooDadFactory.h"
#include <deque>
#include <queue>
#include "Player.h"
#include "Rat.h"
#include "RatKing.h"
#include "WhiteRat.h"
#include "Soldier.h"
#include "TownsPerson.h"
#include "Skeleton.h"
#include "SkeletonKing.h"
#include <algorithm>
#include "RpgTileGridScene.h"

const int PATH_FINDING_BREAK_LIMIT = 1500;
const int DEFAULT_MAX_UNITS = 400;

ZoneMap::ZoneMap() {
	init();
	for (size_t i = 0; i < MAX_ZONE_WIDTH; i++)
	{
		std::vector <int> zoneRow;
		for (size_t j = 0; j < MAX_ZONE_HEIGHT; j++) {
			zoneRow.push_back(0);
		}
		tileMap.push_back(zoneRow);
	}
	setUpMaps();
}

ZoneMap::ZoneMap(int newId) {
	init(newId);
	for (size_t i = 0; i < MAX_ZONE_WIDTH; i++)
	{
		std::vector <int> zoneRow;
		for (size_t j = 0; j < MAX_ZONE_HEIGHT; j++) {
			zoneRow.push_back(0);
		}
		tileMap.push_back(zoneRow);
	}
	setUpMaps();
}

ZoneMap::ZoneMap(int newId, std::vector< std::vector<int> > tiles) {
	init(newId);
	assignNewTileMap(tiles);
	setUpMaps();
}

ZoneMap::ZoneMap(SaveObject saveObject, RpgTileGridScene* gameScene) {
	init();
	std::vector< Building* > buildingsToAdd;
	std::vector< Unit* > unitsToAdd;
	std::vector< DooDad* > dooDadsToAdd;
	std::vector< ZonePortal* > portalsToAdd;
	for (int i = 0; i < saveObject.attributes.size(); i++)
	{
		switch (saveObject.attributes[i].attributeType) {
		case ZONE_MAP_ID:
			id = stoi(saveObject.attributes[i].valueString);
			break;
		case ZONE_NAME:
			zoneName = saveObject.attributes[i].valueString;
			break;
		case TILE_MAP:
			tileMap = get2dIntVectorFromSaveString(saveObject.attributes[i].valueString);
			break;
		case PORTALS:
			portalsToAdd = getPortalVectorFromSaveString(saveObject.attributes[i].valueString);
			break;
		case DOODADS:
			dooDadsToAdd = getDooDadVectorFromSaveString(saveObject.attributes[i].valueString, (TileGridScene*)gameScene);
			break;
		case BUILDINGS:
			buildingsToAdd = getBuildingVectorFromSaveString(saveObject.attributes[i].valueString);
			break;
		case UNITS:
			unitsToAdd = getUnitVectorFromSaveString(saveObject.attributes[i].valueString, gameScene);
			break;
		case MOB_SPAWN:
			mobSpawn = stoi(saveObject.attributes[i].valueString);
			break;
		case ZONE_BACKGROUND:
			backGroundTile = stoi(saveObject.attributes[i].valueString);
			break;
		case DIFFICULTY:
			difficulty = stoi(saveObject.attributes[i].valueString);
			break;
		default:
			break;
		}
	}
	setUpMaps();
	for (auto building : buildingsToAdd) {
		addBuildingToLocation(building, building->tileLocation->x, building->tileLocation->y);
	}
	for (auto unit : unitsToAdd) {
		addUnitToLocation(unit, unit->tileLocation->x, unit->tileLocation->y);
	}

	for (auto dooDad : dooDadsToAdd) {
		addDooDadToLocation(dooDad, dooDad->tileCoords[0], dooDad->tileCoords[1]);
	}

	for (auto portal : portalsToAdd) {
		addPortalToLocation(portal, portal->tileCoords[0], portal->tileCoords[1]);
	}
}

ZoneMap::ZoneMap(const ZoneMap& oldMap)
{
	init();
	id = oldMap.id;
    zoneName = oldMap.zoneName;
	tileMap = oldMap.tileMap;
	buildingMap2 = oldMap.buildingMap2;
	unitMap = oldMap.unitMap;
	itemMap = oldMap.itemMap;
	portalMap = oldMap.portalMap;
	dooDads = oldMap.dooDads;
	buildings2 = oldMap.buildings2;
	portals = oldMap.portals;
	units = oldMap.units;
	playerPresence = oldMap.playerPresence;
	difficulty = oldMap.difficulty;
	backGroundTile = oldMap.backGroundTile;
	mobSpawn = oldMap.mobSpawn;
	graph = oldMap.graph;
	dooDadMap = oldMap.dooDadMap;
}

void ZoneMap::init() {
	id = -1;
	zoneName = "";
	backGroundTile = WATER;
	mobSpawn = true;
	maxUnits = DEFAULT_MAX_UNITS;
	numUnitSpawners = 0;
	updateSpawnerNumRate = 400;
	updateSpawnerNumTick = 0;
}

void ZoneMap::init(int newId) {
	init();
	id = newId;
}

ZoneMap::~ZoneMap() {
	id = 0;
	tileMap.clear();
	portals.clear();
}

void ZoneMap::addToUnitMap(Unit* unit)
{
	addToUnitMap(unit->tileLocation->x, unit->tileLocation->x, unit);
	addToUnitMap(unit->tileDestination->x, unit->tileDestination->x, unit);
}

void ZoneMap::addToUnitMap(int x, int y, Unit* unit)
{
	int key = getMapKey(x, y);
	if (unitMap.find(key) == unitMap.end())
	{
		unitMap[key] = { unit };
	}
	else {
		if (std::find(unitMap[key].begin(), unitMap[key].end(), unit) == unitMap[key].end())
		{
			unitMap[key].push_back(unit);
		}
	}
}

Unit* ZoneMap::getUnitFromMap(int x, int y)
{
	std::vector<Unit*> unitsAtLocation = getUnitsFromMap(x, y);
	if (unitsAtLocation.size() <= 0)
	{
		return nullptr;
	}
	return unitsAtLocation[0];
}

std::vector<Unit*> ZoneMap::getUnitsFromMap(int x, int y)
{
	int key = getMapKey(x, y);
	if (unitMap.find(key) == unitMap.end())
	{
		return std::vector<Unit*>();
	}
	return unitMap[key];
}

void ZoneMap::removeUnitFromMap(Unit* unit)
{
	removeUnitFromMap(unit->tileLocation->x, unit->tileLocation->y, unit);
	removeUnitFromMap(unit->tileDestination->x, unit->tileDestination->y, unit);
}

void ZoneMap::removeUnitFromMap(int x, int y, Unit* unit)
{
	int key = getMapKey(x, y);
	auto unitIterator = unitMap[key].begin();
	while (unitIterator != unitMap[key].end())
	{
		if ((*unitIterator) == unit) {
			unitIterator = unitMap[key].erase(unitIterator);
			if (unitMap[key].size() <= 0)
			{
				unitMap.erase(key);
				break;
			}
		}
		else {
			unitIterator++;
		}
	}
}

void ZoneMap::addToPortalMap(ZonePortal* portal)
{
	addToPortalMap(portal->tileCoords[0], portal->tileCoords[1], portal);
}

void ZoneMap::addToPortalMap(int x, int y, ZonePortal* portal)
{
	int key = getMapKey(x, y);
	if (portalMap.find(key) == portalMap.end())
	{
		portalMap[key] = portal;
	}
	else {
		delete portalMap[key];
		portalMap[key] = portal;
	}
}

ZonePortal* ZoneMap::getPortalFromMap(int x, int y)
{
	int key = getMapKey(x, y);
	if (portalMap.find(key) == portalMap.end())
	{
		return nullptr;
	}
	return portalMap[key];
}

void ZoneMap::removePortalFromMap(ZonePortal* portal)
{
	removePortalFromMap(portal->tileCoords[0], portal->tileCoords[1], portal);
}

void ZoneMap::removePortalFromMap(int x, int y, ZonePortal* portal)
{
	int key = getMapKey(x, y);
	portalMap[key] = nullptr;
	portalMap.erase(key);
}

void ZoneMap::addToDooDadMap(DooDad* dooDad, int x, int y)
{
	int key = getMapKey(x, y);
	if (dooDadMap.find(key) == dooDadMap.end())
	{
		dooDadMap[key] = dooDad;
	}
	else {
		if (dooDadMap[key] != nullptr)
		{
			destroyDooDad(dooDadMap[key]);
		}
		dooDadMap[key] = dooDad;
	}
}

DooDad* ZoneMap::getDooDadFromMap(int x, int y)
{
	int key = getMapKey(x, y);
	if (dooDadMap.find(key) == dooDadMap.end())
	{
		return nullptr;
	}
	return dooDadMap[key];
}

void ZoneMap::removeDooDadFromMap(DooDad* dooDad, int x, int y)
{
	int key = getMapKey(x, y);
	dooDadMap[key] = nullptr;
	dooDadMap.erase(key);
}

void ZoneMap::addToBuildingMap(Building* building, int x, int y)
{
	int key = getMapKey(x, y);
	if (buildingMap2.find(key) == buildingMap2.end())
	{
		buildingMap2[key] = building;
	}
	else {
		//delete buildingMap2[key];
		//buildingMap2.erase(buildingMap2.find(key));
		destroyBuilding(buildingMap2[key]);
		buildingMap2[key] = building;
	}
}

Building* ZoneMap::getBuildingFromMap(int x, int y)
{
	int key = getMapKey(x, y);
	if (buildingMap2.find(key) == buildingMap2.end())
	{
		return nullptr;
	}
	return buildingMap2[key];
}

void ZoneMap::removeBuildingFromMap(Building* building, int x, int y)
{
	int key = getMapKey(x, y);
	buildingMap2[key] = nullptr;
	buildingMap2.erase(key);
}

std::vector<Unit*> ZoneMap::getUnits()
{
	return units;
}

std::vector<ZonePortal*> ZoneMap::getPortals()
{
	return portals;
}

std::vector<DooDad*> ZoneMap::getDooDads()
{
	return dooDads;
}

std::vector<Building*> ZoneMap::getBuildings()
{
	return buildings2;
}

void ZoneMap::addPortalToLocation(ZonePortal* portal, int x, int y)
{
	addToPortalMap(x, y, portal);
	addToPortalVector(portal);
}

void ZoneMap::addToItemMap(int x, int y, Item* item)
{
	int key = getMapKey(x, y);
	if (itemMap.find(key) == itemMap.end())
	{
		itemMap[key] = { item };
	}
	else {
		itemMap[key].push_back(item);
		//not sure why I have below check :/
		//if (std::find(itemMap[key].begin(), itemMap[key].end(), item) == itemMap[key].end())
		//{
			//itemMap[key].push_back(item);
		//}
	}
}

Item* ZoneMap::getItemFromMap(int x, int y)
{
	std::vector<Item*> itemsAtLocation = getItemsFromMap(x, y);
	if (itemsAtLocation.size() <= 0)
	{
		return nullptr;
	}
	return itemsAtLocation[0];
}

std::vector<Item*> ZoneMap::getItemsFromMap(int x, int y)
{
	int key = getMapKey(x, y);
	if (itemMap.find(key) == itemMap.end())
	{
		return std::vector<Item*>();
	}
	return itemMap[key];
}

void ZoneMap::removeItemFromMap(int x, int y, Item* item)
{
	int key = getMapKey(x, y);
	auto itemIterator = itemMap[key].begin();
	while (itemIterator != itemMap[key].end())
	{
		if ((*itemIterator) == item) {
			itemIterator = itemMap[key].erase(itemIterator);
			if (itemMap[key].size() <= 0)
			{
				itemMap.erase(key);
				break;
			}
		}
		else {
			itemIterator++;
		}
	}
}

void ZoneMap::assignNewTileMap(std::vector< std::vector<int> > tiles) {
	if (tiles.size() > 0)
	{
		tileMap.resize(tiles.size());
		for (int i = 0; i < tiles.size(); i++)
		{
			if (tiles[i].size() > 0)
			{
				tileMap[i].resize(tiles[i].size());
				for (int j = 0; j < tiles[i].size(); j++) {
					tileMap[i][j] = tiles[i][j];
				}
			}
		}
	}
	setUpMaps();
}

void ZoneMap::addZonePortal(int textureId, std::vector <int> newTileCoords, int newExitZoneId, std::vector <int> newExitTileCoords) {
	ZonePortal* newPortal; 
	newPortal = new ZonePortal(textureId, newTileCoords, newExitZoneId, newExitTileCoords);
	addToPortalVector(newPortal);
	addToPortalMap(newPortal);
}

//ZonePortal* ZoneMap::getPortalAtLocation(int xpos, int ypos)
//{
//	for (auto portal : portals) {
//		if (portal->tileCoords[0] == xpos && portal->tileCoords[1] == ypos)
//		{
//			return portal;
//		}
//	}
//	return nullptr;
//}

ZonePortal* ZoneMap::getPortalAtLocation(int xpos, int ypos)
{
	return getPortalFromMap(xpos, ypos);
}


DooDad* ZoneMap::getDooDadAtLocation(int xpos, int ypos)
{
	return getDooDadFromMap(xpos, ypos);
}

void ZoneMap::addDooDadToLocation(DooDad* dooDad, int xpos, int ypos)
{
	dooDad->zoneId = id;
	dooDad->tileCoords[0] = xpos;
	dooDad->tileCoords[1] = ypos;
	addToDooDadVector(dooDad);
	addToDooDadMap(dooDad, xpos, ypos);
}

void ZoneMap::destroyDooDad(DooDad* dooDad)
{
	if (dooDad->assignedToBuilding != nullptr)
	{
		dooDad->assignedToBuilding->unAssignDooDad(dooDad);
	}
	removeDooDadFromMap(dooDad, dooDad->tileCoords[0], dooDad->tileCoords[1]);
	removeFromDooDadVector(dooDad);
	delete dooDad;
}

void ZoneMap::destroyBuilding(Building* building)
{
	removeBuildingFromZone(building);
	for (auto unit : building->assignedUnits)
	{
		auto unitIterator = building->assignedUnits.begin();
		while (unitIterator != building->assignedUnits.end())
		{
			if ((*unitIterator) == unit) {
				unitIterator = building->assignedUnits.erase(unitIterator);
			}
			else {
				unitIterator++;
			}
		}
		unit->assignedToBuilding = nullptr;
		((TileGridScene*)unit->scene)->addUnitToDestroy(unit);
	}
	delete building;
}

void ZoneMap::destroyBuildingButNotunits(Building* building)
{
	removeBuildingFromZone(building);
	delete building;
}


std::vector<Item*> ZoneMap::getItemsAtLocation(int xpos, int ypos)
{
	return getItemsFromMap(xpos, ypos);
}

void ZoneMap::removeItemAtLocation(Item* item, int xpos, int ypos)
{
	removeItemFromMap(xpos, ypos, item);
}

void ZoneMap::addItemToLocation(Item* item, int xpos, int ypos)
{
	addToItemMap(xpos, ypos, item);
}

void ZoneMap::removePortalAtLocation(int xpos, int ypos)
{
	ZonePortal* portalToDelete = getPortalAtLocation(xpos, ypos);
	if (portalToDelete != nullptr)
	{
		removePortalFromMap(portalToDelete);
		removeFromPortalVector(portalToDelete);
		delete portalToDelete;
	}
}

std::string ZoneMap::toSaveString(bool withHeaderAndFooter) {
	std::string saveString;
	int uniqueObjectId = getUniqueId();

	if (withHeaderAndFooter)
	{
		saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(ZONE_MAP) + "\n";
	}

	
	saveString += getAttributeString(getUniqueId(), ZONE_MAP_ID, id);
	saveString += getAttributeString(getUniqueId(), ZONE_NAME, zoneName);
	saveString += getAttributeString(getUniqueId(), TILE_MAP, get2DIntVectorSaveString(tileMap));
	saveString += getAttributeString(getUniqueId(), PORTALS, getPortalVectorSaveString(portals));
	saveString += getAttributeString(getUniqueId(), DOODADS, getDooDadVectorSaveString(dooDads));
	saveString += getAttributeString(getUniqueId(), BUILDINGS, getBuildingVectorSaveString(buildings2));
	saveString += getAttributeString(getUniqueId(), UNITS, getUnitVectorSaveString(units));
	saveString += getAttributeString(getUniqueId(), ZONE_BACKGROUND, backGroundTile);
	saveString += getAttributeString(getUniqueId(), MOB_SPAWN, mobSpawn);
	saveString += getAttributeString(getUniqueId(), DIFFICULTY, difficulty);
	

	if (withHeaderAndFooter)
	{
		saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(ZONE_MAP) + "\n";
	}

	return saveString;
}

int ZoneMap::getDevelopmentLevel()
{
	return playerPresence + 1;
}

int ZoneMap::getDifficulty()
{
	return difficulty + 1;
}

void ZoneMap::draw(TileGridScene* scene)
{
	//fill screen with backdrop
	/*for (size_t i = 0; i * scene->tileHeight <= (scene->engine->screenHeight + scene->tileHeight) + scene->tileHeight; i++)
	{
		for (size_t j = 0; j * scene->tileWidth <= scene->engine->screenWidth + scene->tileWidth; j++) {
			scene->renderTexture(backGroundTile, ( (scene->tileWidth * j) + scene->mainCanvasStartX) + (scene->xOffset % scene->tileWidth ) - scene->tileWidth, scene->tileHeight * i + (scene->yOffset % scene->tileHeight) - scene->tileHeight, scene->tileWidth, scene->tileHeight);
		}
	}*/

	//draw zone
	/*for (int i = 0; i < tileMap.size(); i++) {
		for (int j = 0; j < tileMap[i].size(); j++) {
			if ((((scene->tileWidth * j) + scene->mainCanvasStartX + scene->xOffset >= 0) && ((scene->tileWidth * j) + scene->mainCanvasStartX + scene->xOffset <= SCREEN_WIDTH)) && ((scene->tileHeight * i + scene->yOffset >= -scene->tileHeight) && (scene->tileHeight * i + scene->yOffset <= SCREEN_HEIGHT)))
			{
				scene->renderTexture(scene->mapTiles[tileMap[i][j]].textureKey, (scene->tileWidth * j) + scene->mainCanvasStartX + scene->xOffset, scene->tileHeight * i + scene->yOffset, scene->tileWidth, scene->tileHeight);
			}
		}
	}*/


	////draw portal
	//for (auto portal : portals) {
	//	scene->renderTexture(portal->textureId, (scene->tileWidth * portal->tileCoords[0]) + scene->mainCanvasStartX + scene->xOffset, scene->tileHeight * portal->tileCoords[1] + scene->yOffset, scene->tileWidth, scene->tileHeight);
	//}

	////draw building
	//for (auto building : buildings) {
	//	if (scene->tileCoordsAreOnDisplayedMapTile(building->tileLocation->x, building->tileLocation->y) || scene->tileCoordsAreOnDisplayedMapTile(building->tileLocation->x + building->width, building->tileLocation->y) || scene->tileCoordsAreOnDisplayedMapTile(building->tileLocation->x, building->tileLocation->y + building->height) || scene->tileCoordsAreOnDisplayedMapTile(building->tileLocation->x + building->width, building->tileLocation->y + building->height))
	//	{
	//		for (int x = 0; x < building->tileMap.size(); x++) {
	//			for (int y = 0; y < building->tileMap[x].size(); y++)
	//			{
	//				if (scene->tileCoordsAreOnDisplayedMapTile(building->tileLocation->x + x, building->tileLocation->y + y) && building->tileMap[x][y] != nullptr)
	//				{
	//					scene->renderTexture(building->tileMap[x][y]->textureKey, (scene->tileWidth * (building->tileLocation->x + x)) + scene->mainCanvasStartX + scene->xOffset, scene->tileHeight * (building->tileLocation->y + y) + scene->yOffset, scene->tileWidth, scene->tileHeight);
	//				}
	//			}
	//		}
	//	}
	//}

	////draw items
	//for (int j = 0; j < itemMap.size(); j++) {
	//	for (int i = 0; i < itemMap[j].size(); i++) {
	//		if ((((scene->tileWidth * j) + scene->mainCanvasStartX + scene->xOffset >= 0) && ((scene->tileWidth * j) + scene->mainCanvasStartX + scene->xOffset <= SCREEN_WIDTH)) && ((scene->tileHeight * i + scene->yOffset >= -scene->tileHeight) && (scene->tileHeight * i + scene->yOffset <= SCREEN_HEIGHT)))
	//		{
	//			for (int k = 0; k < itemMap[j][i].size(); k++) {
	//				scene->renderTexture(itemMap[j][i][k]->textureKey, (scene->tileWidth * j) + scene->mainCanvasStartX + scene->xOffset, scene->tileHeight * i + scene->yOffset, scene->tileWidth, scene->tileHeight);
	//			}
	//		}
	//	}
	//}

	////draw units
	//for (auto unit : units) {
	//	if (unit->active && (unit->xpos >= 0 + scene->mainCanvasStartX - scene->tileWidth && unit->xpos <= scene->engine->screenWidth + scene->tileWidth) && (unit->ypos >= 0 - scene->tileHeight && unit->ypos <= scene->engine->screenHeight + scene->tileHeight))
	//	{
	//		unit->draw();
	//	}
	//}

	//fill screen with backdrop
	for (size_t i = 0; i * scene->tileHeight <= (scene->engine->screenHeight + scene->tileHeight) + scene->tileHeight; i++)
	{
		for (size_t j = 0; j * scene->tileWidth <= scene->engine->screenWidth + scene->tileWidth; j++) {
			scene->renderTexture(backGroundTile, ((scene->tileWidth * j) + scene->mainCanvasStartX) + ((int) scene->xOffset % scene->tileWidth) - scene->tileWidth * 2, scene->tileHeight * i + ((int)scene->yOffset % scene->tileHeight) - scene->tileHeight * 2, scene->tileWidth * 3, scene->tileHeight * 3);
		}
	}

	double startcoords[2];
	double endcoords[2];
	scene->getTileIndexFromScreenCoords(0, 0, startcoords);
	scene->getTileIndexFromScreenCoords(scene->engine->screenWidth + scene->tileWidth * 2, scene->engine->screenHeight + scene->tileHeight * 2, endcoords);
	int startX = startcoords[0];
	int startY = startcoords[1];
	int endX = endcoords[0];
	int endY = endcoords[1];

	//int startX = ((RpgTileGridScene*)scene)->player->tileLocation->x - (scene->desiredTilesAcross / 2) - 1;
	if (startX < 0)
	{
		startX = 0;
	}
	if (startX >= tileMap.size())
	{
		startX = tileMap.size();
	}
	//int endX = ((RpgTileGridScene*)scene)->player->tileLocation->x + (scene->desiredTilesAcross / 2) + 1;
	if (endX < 0)
	{
		endX = 0;
	}
	if (endX >= tileMap.size())
	{
		endX = tileMap.size();
	}
	//int startY = ((RpgTileGridScene*)scene)->player->tileLocation->y - (scene->desiredTilesDown / 2) - 1;
	if (startY < 0)
	{
		startY = 0;
	}
	if (startY >= tileMap[0].size())
	{
		startY = tileMap[0].size();
	}
	//int endY = ((RpgTileGridScene*)scene)->player->tileLocation->y + (scene->desiredTilesDown / 2) + 1;
	if (endY < 0)
	{
		endY = 0;
	}
	if (endY >= tileMap[0].size())
	{
		endY = tileMap[0].size();
	}

	//draw zone
	bool logstuff = false;
	Building* buildingToRender;
	for (int y = startY; y < endY; y++) {
		for (int x = startX; x < endX; x++) {
			if ((((scene->tileWidth * (x + 1)) + scene->mainCanvasStartX + scene->xOffset >= 0) && ((scene->tileWidth * (x - 1)) + scene->mainCanvasStartX + scene->xOffset <= SCREEN_WIDTH)) && ((scene->tileHeight * (y + 1) + scene->yOffset >= -scene->tileHeight) && (scene->tileHeight * (y - 1) + scene->yOffset <= SCREEN_HEIGHT)))
			{
				//render tiles
				scene->renderTexture(scene->mapTiles[tileMap[x][y]].textureKey, (scene->tileWidth * x) + scene->mainCanvasStartX + scene->xOffset - scene->tileWidth, scene->tileHeight * y + scene->yOffset - scene->tileHeight, scene->tileWidth * 3, scene->tileHeight * 3);
			}
		}
		for (int x = startX; x < endX; x++) {
			//render buildings
			if ((((scene->tileWidth * (x + 1)) + scene->mainCanvasStartX + scene->xOffset >= 0) && ((scene->tileWidth * (x - 1)) + scene->mainCanvasStartX + scene->xOffset <= SCREEN_WIDTH)) && ((scene->tileHeight * (y + 1) + scene->yOffset >= -scene->tileHeight) && (scene->tileHeight * (y - 1) + scene->yOffset <= SCREEN_HEIGHT)))
			{
				buildingToRender = getBuildingFromMap(x, y);
				if (buildingToRender != nullptr)
				{
					if (buildingToRender->getTileAtMapLocation(x, y) != nullptr) {
						SDL_SetTextureColorMod(scene->engine->textures[buildingToRender->getTileAtMapLocation(x, y)->textureKey].texture, 255, 255, 255);
						SDL_SetTextureAlphaMod(scene->engine->textures[buildingToRender->getTileAtMapLocation(x, y)->textureKey].texture, 255);
						scene->renderTexture(buildingToRender->getTileAtMapLocation(x, y)->textureKey, (scene->tileWidth * x) + scene->mainCanvasStartX + scene->xOffset - scene->tileWidth, scene->tileHeight * y + scene->yOffset - scene->tileHeight, scene->tileWidth * 3, scene->tileHeight * 3);
						if (logstuff)
						{
							int newx = (scene->tileWidth * x) + scene->mainCanvasStartX + scene->xOffset - scene->tileWidth;
							std::cout << "\ntile x: ";
							std::cout << newx;
							std::cout << "\ndelta: ";
							std::cout << newx - lastx;
							std::cout << "\nxoffset: ";
							std::cout << scene->xOffset;
							std::cout << "\n";
							if (newx - lastx >= 60)
							{
								int dfgdfg = 34334;
							}
							lastx = newx;
							logstuff = false;
						}
					}
				}
			}
		}

		//render portals
		ZonePortal* portalToRender;
		for (int x = startX; x < endX; x++) {
			if ((((scene->tileWidth * (x + 1)) + scene->mainCanvasStartX + scene->xOffset >= 0) && ((scene->tileWidth * (x - 1)) + scene->mainCanvasStartX + scene->xOffset <= SCREEN_WIDTH)) && ((scene->tileHeight * (y + 1) + scene->yOffset >= -scene->tileHeight) && (scene->tileHeight * (y - 1) + scene->yOffset <= SCREEN_HEIGHT)))
			{
				portalToRender = getPortalAtLocation(x, y);
				if (portalToRender != nullptr) {
					scene->renderTexture(portalToRender->textureId, (scene->tileWidth * x) + scene->mainCanvasStartX + scene->xOffset - scene->tileWidth, scene->tileHeight * y + scene->yOffset - scene->tileHeight, scene->tileWidth * 3, scene->tileHeight * 3);
				}
			}
		}

		//render doodads
		for (int x = startX; x < endX; x++) {
			if ((((scene->tileWidth * (x + 1)) + scene->mainCanvasStartX + scene->xOffset >= 0) && ((scene->tileWidth * (x - 1)) + scene->mainCanvasStartX + scene->xOffset <= SCREEN_WIDTH)) && ((scene->tileHeight * (y + 1) + scene->yOffset >= -scene->tileHeight) && (scene->tileHeight * (y - 1) + scene->yOffset <= SCREEN_HEIGHT)))
			{
				DooDad* dooDadAtLocation = getDooDadAtLocation(x, y);
				if (dooDadAtLocation != nullptr) {
					scene->renderTexture(dooDadAtLocation->textureKey, (scene->tileWidth * x) + scene->mainCanvasStartX + scene->xOffset - scene->tileWidth, scene->tileHeight * y + scene->yOffset - scene->tileHeight, scene->tileWidth * 3, scene->tileHeight * 3);
					if (dooDadAtLocation->canBeDamaged) {
						dooDadAtLocation->drawHealth();
					}
				}
			}
		}

		//render items
		for (int x = startX; x < endX; x++) {
			if ((((scene->tileWidth * (x + 1)) + scene->mainCanvasStartX + scene->xOffset >= 0) && ((scene->tileWidth * (x - 1)) + scene->mainCanvasStartX + scene->xOffset <= SCREEN_WIDTH)) && ((scene->tileHeight * (y + 1) + scene->yOffset >= -scene->tileHeight) && (scene->tileHeight * (y - 1) + scene->yOffset <= SCREEN_HEIGHT)))
			{
				for (int k = 0; k < getItemsAtLocation(x, y).size(); k++) {
					scene->renderTexture(getItemsAtLocation(x, y)[k]->textureKey, (scene->tileWidth * x) + scene->mainCanvasStartX + scene->xOffset, scene->tileHeight * y + scene->yOffset, scene->tileWidth, scene->tileHeight);
				}
			}
		}
		//render units
		for (int x = startX; x < endX; x++) {
			if ((((scene->tileWidth * (x + 1)) + scene->mainCanvasStartX + scene->xOffset >= 0) && ((scene->tileWidth * (x - 1)) + scene->mainCanvasStartX + scene->xOffset <= SCREEN_WIDTH)) && ((scene->tileHeight * (y + 1) + scene->yOffset >= -scene->tileHeight) && (scene->tileHeight * (y - 1) + scene->yOffset <= SCREEN_HEIGHT)))
			{
				for (auto unit : getUnitsFromMap(x, y)) {
					unit->draw();
				}
			}
		}
	}
}

Unit* ZoneMap::getUnitAtLocation(int x, int y)
{
	std::vector<Unit*> unitsAtLocation = getUnitsFromMap(x, y);
	if (unitsAtLocation.size() > 0)
	{
		try {

			return unitsAtLocation.at(0);
		}
		catch (...) {
			return nullptr;
		}
	}
	else {
		return nullptr;
	}
}

bool ZoneMap::addUnitToLocation(Unit* unit, int x, int y)
{
	unit->zone = id;
	unit->setTileLocation(x, y);
	addToUnitVector(unit);
	addToUnitMap(x, y, unit);
	return true;
}

bool ZoneMap::addUnitToDestinationLocation(Unit* unit)
{
	unit->zone = id;
	addToUnitVector(unit);
	addToUnitMap(unit->tileDestination->x, unit->tileDestination->y, unit);
	return true;
}

bool ZoneMap::removeUnitFromZone(Unit* unit)
{
	unit->zone = -1;
	removeUnitFromMap(unit);
	removeFromUnitVector(unit);
	return true;
}

Building* ZoneMap::getBuildingAtLocation(int x, int y)
{
	return getBuildingFromMap(x, y);
}

Building* ZoneMap::getBuildingById(int buildingId)
{
	Building* returnBuilding = nullptr;
	for (auto building : buildings2) {
		if (building->id == buildingId)
		{
			returnBuilding = building;
		}
	}
	return returnBuilding;
}

bool ZoneMap::addBuildingToLocation(Building* building, int x, int y)
{
	building->tileLocation->x = x;
	building->tileLocation->y = y;
	for (size_t i = 0; i < building->width; i++)
	{
		for (size_t j = 0; j < building->height; j++)
		{
			addToBuildingMap(building, i + building->tileLocation->x, j + building->tileLocation->y);
			//buildingMap[i + building->tileLocation->x][j + building->tileLocation->y] = building;
		}
	}
	addToBuildingVector(building);
	building->setZone(this);
	return true;
}

bool ZoneMap::removeBuildingFromZone(Building* building)
{
	removeAllBuildingTilesFromMap(building);
	removeFromBuildingVector(building);
	while (building->assignedDooDads.size() > 0)
	{
		DooDad* dooDad = building->assignedDooDads[0];
		building->unAssignDooDad(dooDad);
		dooDad->scene->addDooDadToDestroy(dooDad);
	}
	return true;
}

bool ZoneMap::removeAllBuildingTilesFromMap(Building* building)
{
	for (size_t i = 0; i < building->width; i++)
	{
		for (size_t j = 0; j < building->height; j++)
		{
			removeBuildingFromMap(building, i + building->tileLocation->x, j + building->tileLocation->y);
			//buildingMap[i + building->tileLocation->x][j + building->tileLocation->y] = nullptr;
		}
	}
	return true;
}


std::vector<Unit*> ZoneMap::getUnitsAtLocation(int x, int y)
{
	return getUnitsFromMap(x, y);
}

void ZoneMap::update()
{
	for (auto unit : getUnits()) {
		if (unit->active)
		{
			unit->update();
		}
	}

	for (auto dooDad : getDooDads())
	{
		dooDad->update();
	}

	updateSpawnerNumTick++;
	if (updateSpawnerNumRate <= updateSpawnerNumTick)
	{
		updateSpawnerNum();
		updateSpawnerNumTick = 0;
	}
}

void ZoneMap::removeUnitFromLocation(Unit* unit, int x, int y) {
	removeUnitFromMap(x, y, unit);
}

void ZoneMap::updateUnitMap()
{
	clearUnitMap();
	for (auto unit : getUnits())
	{
		addToUnitMap(unit);
	}
}

bool ZoneMap::isTilePassable(TileGridScene* scene,  int x, int y)
{
	if (x < 0 || y < 0 || x >= tileMap.size() || y >= tileMap[x].size() || !scene->mapTiles[tileMap[x][y]].passable)
	{
		return false;
	}

	Building* building = getBuildingAtLocation(x, y);
	if (building != nullptr)
	{
		BuildingTile* tile = building->getTileAtMapLocation(x, y);
		if (tile != nullptr)
		{
			if (!tile->isPassable()) {
				return false;
			}
		}
	}

	DooDad* dooDad = getDooDadAtLocation(x, y);
	if (dooDad != nullptr && !dooDad->passable)
	{
		return false;
	}

	return getUnitAtLocation(x, y) == nullptr ;
}

bool ZoneMap::isTilePassableIgnoreAllUnits(TileGridScene* scene, int x, int y)
{
	if(x < 0 || y < 0 || x >= tileMap.size() || y >= tileMap[x].size() || !scene->mapTiles[tileMap[x][y]].passable)
	{
		return false;
	}

	Building* building = getBuildingAtLocation(x, y);
	if (building != nullptr)
	{
		BuildingTile* tile = building->getTileAtMapLocation(x, y);
		if (tile != nullptr)
		{
			if (!tile->isPassable()) {
				return false;
			}
		}
	}

	DooDad* dooDad = getDooDadAtLocation(x, y);
	if (dooDad != nullptr && !dooDad->passable)
	{
		return false;
	}

	return true;
}

bool ZoneMap::isTilePassableIgnoreUnit(TileGridScene* scene, int x, int y, Unit* unitToIgnore)
{
	if (x < 0 || y < 0 || x >= tileMap.size() || y >= tileMap[x].size() || !scene->mapTiles[tileMap[x][y]].passable)
	{
		return false;
	}

	Building* building = getBuildingAtLocation(x, y);
	if (building != nullptr)
	{
		BuildingTile* tile = building->getTileAtMapLocation(x, y);
		if (tile != nullptr)
		{
			if (!tile->isPassable()) {
				return false;
			}
		}
	}

	DooDad* dooDad = getDooDadAtLocation(x, y);
	if (dooDad != nullptr && !dooDad->passable)
	{
		return false;
	}

	bool ignoreUnitPresent = false;
	for (auto unit : getUnitsAtLocation(x, y))
	{
		if (unitToIgnore == unit) {
			ignoreUnitPresent = true;
			break;
		}
	}

	return (getUnitAtLocation(x, y) == nullptr || ignoreUnitPresent);
}

bool ZoneMap::isTilePassableIgnoreUnits(TileGridScene* scene, int x, int y, std::vector<Unit*> unitsToIgnore)
{
	if (x < 0 || y < 0 || x >= tileMap.size() || y >= tileMap[x].size() || !scene->mapTiles[tileMap[x][y]].passable)
	{
		return false;
	}

	Building* building = getBuildingAtLocation(x, y);
	if (building != nullptr)
	{
		BuildingTile* tile = building->getTileAtMapLocation(x, y);
		if (tile != nullptr)
		{
			if (!tile->isPassable()) {
				return false;
			}
		}
	}

	DooDad* dooDad = getDooDadAtLocation(x, y);
	if (dooDad != nullptr && !dooDad->passable)
	{
		return false;
	}

	bool ignoreUnitPresent = false;
	for (auto unit : getUnitsAtLocation(x, y))
	{
		for (auto unitToIgnore : unitsToIgnore) {
			if (unitToIgnore == unit) {
				ignoreUnitPresent = true;
				goto endOfLoop;
			}
		}

	}
endOfLoop:
	return (ignoreUnitPresent || getUnitAtLocation(x, y) == nullptr);
}

void ZoneMap::unitEntersTile(Unit* unit, int x, int y)
{
	if (unit->canGoThroughPortal)
	{
		ZonePortal* currentPortal = getPortalAtLocation(unit->tileLocation->x, unit->tileLocation->y);
		if (currentPortal != nullptr)
		{
			//unit->scene->portalUnit(currentPortal, unit);
			unit->portalTo(currentPortal->exitZoneId, currentPortal->exitTileCoords[0], currentPortal->exitTileCoords[1]);
		}

		DooDad* currentDooDad = getDooDadAtLocation(unit->tileLocation->x, unit->tileLocation->y);
		if (currentDooDad != nullptr)
		{
			currentDooDad->walkOn(unit);
		}
	}
}


std::vector<int> ZoneMap::getPathDirections(TileGridScene* scene, Location* startLocation, Location* destinationLocation)
{
	std::vector<int> pathDirections;
	std::vector<Location*> path = getPath(scene, startLocation, destinationLocation);
	Location* previousLocation = startLocation;
	for (auto location : path) {
		if (location->x < previousLocation->x)
		{
			pathDirections.push_back(LEFT);
			previousLocation = location;
			continue;
		}
		else if (location->x > previousLocation->x)
		{
			pathDirections.push_back(RIGHT);
			previousLocation = location;
			continue;
		}
		else if (location->y > previousLocation->y)
		{
			pathDirections.push_back(DOWN);
			previousLocation = location;
			continue;
		}
		else if (location->y < previousLocation->y)
		{
			pathDirections.push_back(UP);
			previousLocation = location;
			continue;
		}
	}
	std::reverse(pathDirections.begin(), pathDirections.end());
	return pathDirections;
}

std::vector<int> ZoneMap::getPathDirectionsIgnoreAllunits(TileGridScene* scene, Location* startLocation, Location* destinationLocation)
{
	PathKey key = {};
	key.from = startLocation;
	key.to = destinationLocation;
	if (directPaths.find(key.getString()) != directPaths.end())
	{
		return directPaths[key.getString()];
	}

	std::vector<int> pathDirections;
	std::vector<Location*> path = getPathIgnoreAllUnits(scene, startLocation, destinationLocation);
	Location* previousLocation = startLocation;
	for (auto location : path) {
		if (location->x < previousLocation->x)
		{
			pathDirections.push_back(LEFT);
			previousLocation = location;
			continue;
		}
		else if (location->x > previousLocation->x)
		{
			pathDirections.push_back(RIGHT);
			previousLocation = location;
			continue;
		}
		else if (location->y > previousLocation->y)
		{
			pathDirections.push_back(DOWN);
			previousLocation = location;
			continue;
		}
		else if (location->y < previousLocation->y)
		{
			pathDirections.push_back(UP);
			previousLocation = location;
			continue;
		}
	}
	std::reverse(pathDirections.begin(), pathDirections.end());
	directPaths[key.getString()] = pathDirections;
	return pathDirections;
}


//std::vector<int> ZoneMap::getPathDirectionsToUnit(TileGridScene* scene, Location* startLocation, Unit* unit)
//{
//	std::vector<int> pathDirections;
//	std::vector<Location*> path = getPathToUnit(scene, startLocation, unit);
//	Location* previousLocation = startLocation;
//	for (auto location : path) {
//		if (location->x < previousLocation->x)
//		{
//			pathDirections.push_back(LEFT);
//			previousLocation = location;
//			continue;
//		}
//		else if (location->x > previousLocation->x)
//		{
//			pathDirections.push_back(RIGHT);
//			previousLocation = location;
//			continue;
//		}
//		else if (location->y > previousLocation->y)
//		{
//			pathDirections.push_back(DOWN);
//			previousLocation = location;
//			continue;
//		}
//		else if (location->y < previousLocation->y)
//		{
//			pathDirections.push_back(UP);
//			previousLocation = location;
//			continue;
//		}
//	}
//	std::reverse(pathDirections.begin(), pathDirections.end());
//	return pathDirections;
//}

std::vector<int> ZoneMap::getPathDirectionsToUnit(TileGridScene* scene, Location* startLocation, Unit* unit, Unit* followingUnit)
{
	std::vector<int> pathDirections;
	std::vector<Location*> path = getPathToUnit(scene, startLocation, unit, followingUnit);
	Location* previousLocation = startLocation;
	for (auto location : path) {
		if (location->x < previousLocation->x)
		{
			pathDirections.push_back(LEFT);
			previousLocation = location;
			continue;
		}
		else if (location->x > previousLocation->x)
		{
			pathDirections.push_back(RIGHT);
			previousLocation = location;
			continue;
		}
		else if (location->y > previousLocation->y)
		{
			pathDirections.push_back(DOWN);
			previousLocation = location;
			continue;
		}
		else if (location->y < previousLocation->y)
		{
			pathDirections.push_back(UP);
			previousLocation = location;
			continue;
		}
	}
	std::reverse(pathDirections.begin(), pathDirections.end());
	return pathDirections;
}

std::vector<Location*> ZoneMap::getPath(TileGridScene* scene, Location* startLocation, Location* destinationLocation)
{
	int new_cost = 0;
	int priority = 0;
	typedef std::pair<int, Location*> PQElement;
	std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> frontier;
	Location* current;
	std::unordered_map< Location, Location*> cameFrom;
	std::unordered_map<Location, double> cost_so_far;
	Location* lowestCostLocation = startLocation;
	//double lowestH = 9999;
	int Hvalue;

	frontier.emplace(0, startLocation);
	cost_so_far[*startLocation] = 0;

	while (frontier.size() > 0)
	{
		current = frontier.top().second;
		frontier.pop();
		if (current->x == destinationLocation->x && current->y == destinationLocation->y)
		{
			break;
		}
		for (auto neighbor : graph.getNeighbors(current))
		{

			new_cost = cost_so_far[*current] + graph.cost(current, neighbor);
			if (isTilePassable(scene, neighbor->x, neighbor->y) && (!cost_so_far.count(*neighbor) > 0 || new_cost < cost_so_far[*neighbor]))
			{
				cost_so_far[*neighbor] = new_cost;
				Hvalue = manhattenDistance(neighbor, destinationLocation);
				priority = new_cost + Hvalue;
				frontier.emplace(priority, neighbor);
				cameFrom[*neighbor] = current;
				if (cameFrom.size() > PATH_FINDING_BREAK_LIMIT)
				{
					return std::vector<Location*>();
				}
				//if (lowestH > Hvalue)
				//{
				//	lowestH = Hvalue;
				//	lowestCostLocation = neighbor;
				//}

				//int screenCoords[2];
				//scene->coordsFromTileIndex(neighbor[0], neighbor[1], screenCoords);
				//scene->engine->renderText("X", screenCoords[0], screenCoords[1], scene->tileWidth, scene->tileHeight, COLOR_BLUE);
			}

		}

	}
	return constructPath(cameFrom, startLocation, destinationLocation);
	/*std::vector<Location*> potentialPath = constructPath(cameFrom, startLocation, destinationLocation);
	if (potentialPath.size() > 0)
	{
		return potentialPath;
	}
	else if (lowestCostLocation != startLocation) {
		return getPath(scene, startLocation, lowestCostLocation);
	}
	else {
		return potentialPath;
	}*/
}

std::vector<Location*> ZoneMap::getPathIgnoreAllUnits(TileGridScene* scene, Location* startLocation, Location* destinationLocation)
{
	int new_cost = 0;
	int priority = 0;
	typedef std::pair<int, Location*> PQElement;
	std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> frontier;
	Location* current;
	std::unordered_map< Location, Location*> cameFrom;
	std::unordered_map<Location, double> cost_so_far;

	frontier.emplace(0, startLocation);
	cost_so_far[*startLocation] = 0;

	while (frontier.size() > 0)
	{
		current = frontier.top().second;
		frontier.pop();
		if (current->x == destinationLocation->x && current->y == destinationLocation->y)
		{
			break;
		}
		for (auto neighbor : graph.getNeighbors(current))
		{

			new_cost = cost_so_far[*current] + graph.cost(current, neighbor);
			if (isTilePassableIgnoreAllUnits(scene, neighbor->x, neighbor->y) && (!cost_so_far.count(*neighbor) > 0 || new_cost < cost_so_far[*neighbor]))
			{
				cost_so_far[*neighbor] = new_cost;
				priority = new_cost + manhattenDistance(neighbor, destinationLocation);
				frontier.emplace(priority, neighbor);
				cameFrom[*neighbor] = current;

				//int screenCoords[2];
				//scene->coordsFromTileIndex(neighbor[0], neighbor[1], screenCoords);
				//scene->engine->renderText("X", screenCoords[0], screenCoords[1], scene->tileWidth, scene->tileHeight, COLOR_BLUE);
			}

		}

	}
	return constructPath(cameFrom, startLocation, destinationLocation);
}

//std::vector<Location*> ZoneMap::getPathToUnit(TileGridScene* scene, Location* startLocation, Unit* unit)
//{
//	if (unit->toBeDeleted)
//	{
//		return std::vector<Location*>();
//	}
//	int new_cost = 0;
//	int priority = 0;
//	typedef std::pair<int, Location*> PQElement;
//	std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> frontier;
//	Location* current;
//	std::unordered_map< Location, Location*> cameFrom;
//	std::unordered_map<Location, double> cost_so_far;
//
//	frontier.emplace(0, startLocation);
//	cost_so_far[*startLocation] = 0;
//
//	while (frontier.size() > 0)
//	{
//		current = frontier.top().second;
//		frontier.pop();
//		if (current->x == unit->tileDestination->x && current->y == unit->tileDestination->y)
//		{
//			break;
//		}
//		for (auto neighbor : graph.getNeighbors(current))
//		{
//
//			new_cost = cost_so_far[*current] + graph.cost(current, neighbor);
//			if (isTilePassableIgnoreUnit(scene, neighbor->x, neighbor->y, unit) &&(!cost_so_far.count(*neighbor) > 0 || new_cost < cost_so_far[*neighbor]))
//			{
//				cost_so_far[*neighbor] = new_cost;
//				priority = new_cost + manhattenDistance(neighbor, unit->tileDestination);
//				frontier.emplace(priority, neighbor);
//				cameFrom[*neighbor] = current;
//
//				//int screenCoords[2];
//				//scene->coordsFromTileIndex(neighbor[0], neighbor[1], screenCoords);
//				//scene->engine->renderText("X", screenCoords[0], screenCoords[1], scene->tileWidth, scene->tileHeight, COLOR_BLUE);
//			}
//
//		}
//
//	}
//	return constructPath(cameFrom, startLocation, unit->tileDestination);
//}

std::vector<Location*> ZoneMap::getPathToUnit(TileGridScene* scene, Location* startLocation, Unit* unit, Unit* followingUnit)
{
	if (unit->scene->isUnitToBeDestroyed(unit))
	{
		return std::vector<Location*>();
	}
	int new_cost = 0;
	int priority = 0;
	typedef std::pair<int, Location*> PQElement;
	std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> frontier;
	Location* current;
	Location* target = unit->tileDestination;
	std::unordered_map< Location, Location*> cameFrom;
	std::unordered_map<Location, double> cost_so_far;
	Location* lowestCostLocation = startLocation;
	double lowestPriority = 9999;

	frontier.emplace(0, startLocation);
	cost_so_far[*startLocation] = 0;

	while (frontier.size() > 0)
	{
		current = frontier.top().second;
		frontier.pop();
		//if (current->x == unit->tileDestination->x && current->y == unit->tileDestination->y)
		if ((std::abs(current->x - unit->tileLocation->x) <= 1) && (std::abs(current->y - unit->tileLocation->y) <= 1))
		{
			target = current;
			break;
		}
		for (auto neighbor : graph.getNeighbors(current))
		{

			new_cost = cost_so_far[*current] + graph.cost(current, neighbor);
			if (isTilePassableIgnoreUnits(scene, neighbor->x, neighbor->y, { unit, followingUnit }) && (!cost_so_far.count(*neighbor) > 0 || new_cost < cost_so_far[*neighbor]))
			{
				cost_so_far[*neighbor] = new_cost;
				priority = new_cost + manhattenDistance(neighbor, unit->tileDestination);
				frontier.emplace(priority, neighbor);
				cameFrom[*neighbor] = current;

				if (lowestPriority > priority)
				{
					lowestPriority = priority;
					lowestCostLocation = neighbor;
				}
			}

		}

	}
	//std::vector<Location*> potentialPath = constructPath(cameFrom, startLocation, unit->tileDestination);
	std::vector<Location*> potentialPath = constructPath(cameFrom, startLocation, target);
	if (potentialPath.size() > 0)
	{
		return potentialPath;
	}
	else if (lowestCostLocation != startLocation){
		return getPath(scene, startLocation, lowestCostLocation);
	}
	else {
		return potentialPath;
	}
}

std::vector<Location*> ZoneMap::constructPath(std::unordered_map<Location, Location*> cameFrom, Location* startLocation, Location* destinationLocation)
{
	Location* current;
	current = destinationLocation;
	std::vector<Location*> path;
	while (current != startLocation)
	{
		path.push_back(current);
		current = cameFrom[*current];
		if (current == NULL)
		{
			return std::vector<Location*>();
		}
	}
	std::reverse(path.begin(), path.end());
	return path;
}

std::vector<Location*> ZoneMap::constructPathToUnit(std::unordered_map<Location, Location*> cameFrom, Location* startLocation, Unit* unit)
{
	Location* current;
	current = unit->tileDestination;
	std::vector<Location*> path;
	while (current != startLocation)
	{
		path.push_back(current);
		current = cameFrom[*current];
		if (current == NULL)
		{
			return std::vector<Location*>();
		}
	}
	std::reverse(path.begin(), path.end());
	return path;
}

int ZoneMap::getNumUnits()
{
	return getUnits().size();
}

void ZoneMap::setupGraph(TileGridScene* scene)
{
	int directions[4] = { UP, DOWN, RIGHT, LEFT };
	for (int x = 0; x < tileMap.size(); x++)
	{
		for (int y = 0; y < tileMap[x].size(); y++) 
		{
			if (scene->mapTiles[tileMap[x][y]].passable)
			{
				std::vector<Location*> neighbors = std::vector<Location*>();
				for (int direction : directions) {
					switch (direction)
					{
					case UP:
						if (y > 0 && scene->mapTiles[tileMap[x][y - 1]].passable)
						{
							neighbors.push_back(new Location{ x, y - 1 });
						}
						break;
					case DOWN:
						if (y + 1 < tileMap[x].size() && scene->mapTiles[tileMap[x][y + 1]].passable)
						{
							neighbors.push_back(new Location{ x, y + 1 });
						}
						break;
					case LEFT:
						if (x > 0 && scene->mapTiles[tileMap[x - 1][y]].passable)
						{
							neighbors.push_back(new Location{ x - 1, y });
						}
					case RIGHT:
						if (x + 1 < tileMap.size() && scene->mapTiles[tileMap[x + 1][y]].passable)
						{
							neighbors.push_back(new Location{ x + 1, y });
						}
					default:
						break;
					}
				}
				if (neighbors.size() > 0)
				{
					graph.addNeighbors(x, y, neighbors);
				}
				graph.addCost(x, y, 1);
			}
			else {
				graph.addCost(x, y, 9999999);
			}
		}
	}
	//calculateDirectPaths(scene);
}

void ZoneMap::calculateDirectPaths(TileGridScene* scene)
{
	
	for (int x = 0; x < tileMap.size(); x++)
	{
		for (int y = 0; y < tileMap[x].size(); y++)
		{
			if (scene->mapTiles[tileMap[x][y]].passable)
			{
				for (int xto = 0; xto < tileMap.size(); xto++)
				{
					for (int yto = 0; yto < tileMap[0].size(); yto++)
					{
						if (scene->mapTiles[tileMap[xto][yto]].passable)
						{
							PathKey key = {};
							Location* from = new Location{ 0,0 };
							Location* to = new Location{ 0,0 };
							key.from = from;
							key.to = to;
							from->x = x;
							from->y = y;
							to->x = xto;
							to->y = yto;
							directPaths[key.getString()] = getPathDirectionsIgnoreAllunits(scene, from, to);
							delete from;
							delete to;
						}
					}
				}
			}
		}
	}
}

int ZoneMap::manhattenDistance(Location* startLocation, Location* destinationLocation)
{
	return std::abs(startLocation->x - destinationLocation->x) + std::abs(startLocation->y - destinationLocation->y);
}


std::string ZoneMap::getPortalVectorSaveString(std::vector<ZonePortal*> vector) {
	std::string returnString;
	returnString += std::to_string(vector.size()) + "\n";
	for (int i = 0; i < vector.size(); i++)
	{
		returnString += vector[i]->toSaveString() + "\n";
	}
	return returnString;
}

std::string ZoneMap::getDooDadVectorSaveString(std::vector<DooDad*> vector)
{
	std::string returnString;
	returnString += std::to_string(vector.size()) + "\n";
	for (int i = 0; i < vector.size(); i++)
	{
		returnString += vector[i]->toSaveString() + "\n";
	}
	return returnString;
}

std::string ZoneMap::getBuildingVectorSaveString(std::vector<Building*> vector)
{
	std::string returnString;
	returnString += std::to_string(vector.size()) + "\n";
	for (int i = 0; i < vector.size(); i++)
	{
		returnString += vector[i]->toSaveString() + "\n";
	}
	return returnString;
}

std::vector<ZonePortal*> ZoneMap::getPortalVectorFromSaveString(std::string saveString) {
	std::vector<ZonePortal*> returnVector;

	std::vector<SaveObject> savedPortals = getSaveObjectVectorFromSaveString2(saveString);

	for (size_t i = 0; i < savedPortals.size(); i++)
	{
		returnVector.push_back(new ZonePortal(savedPortals[i].rawString));
	}


	return returnVector;
}

std::vector<DooDad*> ZoneMap::getDooDadVectorFromSaveString(std::string saveString, TileGridScene* gameScene)
{
	std::vector<DooDad*> returnVector;

	std::vector<SaveObject> savedDooDads = getSaveObjectVectorFromSaveString2(saveString);

	for (size_t i = 0; i < savedDooDads.size(); i++)
	{
		for (int j = 0; j < savedDooDads[i].attributes.size(); j++)
		{
			if (savedDooDads[i].attributes[j].attributeType == DOODAD_TYPE)
			{
				switch (stoi(savedDooDads[i].attributes[j].valueString)) {
				case HEALING_PAD:
					returnVector.push_back(new HealingPad(savedDooDads[i].rawString, gameScene));;
					break;
				case DOODAD_TOWN_COMMAND:
					returnVector.push_back(new TownCommand(savedDooDads[i].rawString, gameScene));;
					break;
				case DOODAD_TREE:
					returnVector.push_back(new Tree(savedDooDads[i].rawString, gameScene));;
					break;
				case DOODAD_APPLE_TREE:
					returnVector.push_back(new FruitTree(savedDooDads[i].rawString, gameScene));;
					break;
				case DOODAD_RASPBERRY_BUSH:
					returnVector.push_back(new BerryBush(savedDooDads[i].rawString, gameScene));;
					break;
				case DOODAD_UNIT_SPAWNER:
					returnVector.push_back(new UnitSpawner(savedDooDads[i].rawString, gameScene));;
					break;
				default:
					returnVector.push_back(new DooDad(savedDooDads[i].rawString, gameScene));
					break;
				}
				break;
			}
		}
	}


	return returnVector;
}

std::vector<Building*> ZoneMap::getBuildingVectorFromSaveString(std::string saveString)
{
	std::vector<Building*> returnVector;

	std::vector<SaveObject> savedBuildings= getSaveObjectVectorFromSaveString2(saveString);

	for (size_t i = 0; i < savedBuildings.size(); i++)
	{
		for (int j = 0; j < savedBuildings[i].attributes.size(); j++)
		{
			if (savedBuildings[i].attributes[j].attributeType == BULDING_TYPE)
			{
				switch (stoi(savedBuildings[i].attributes[j].valueString)) {
				case BUILDING_ITEM_SHOP:
					returnVector.push_back(new ItemShop(savedBuildings[i].rawString));;
					break;
				case BUILDING_CAMP_COMMAND_CENTRE:
					returnVector.push_back(new CampCommandCentre(savedBuildings[i].rawString));;
					break;
				case BUILDING_BARRACKS:
					returnVector.push_back(new Barracks(savedBuildings[i].rawString));;
					break;
				case BUILDING_WOODCUTTER:
					returnVector.push_back(new WoodCutter(savedBuildings[i].rawString));;
					break;
				case BUILDING_HOUSE:
					returnVector.push_back(new House(savedBuildings[i].rawString));;
					break;
				default:
					returnVector.push_back(new Building(savedBuildings[i].rawString));
					break;
				}
				break;
			}
		}
	}


	return returnVector;
}

void ZoneMap::clearUnitMap()
{
	unitMap.clear();
}

void ZoneMap::clearItemMap()
{
	itemMap.clear();
}
void ZoneMap::clearDooDadMap()
{
	dooDadMap.clear();
}
void ZoneMap::clearBuildingMap()
{
	buildingMap2.clear();
}

void ZoneMap::clearPortalMap()
{
	portalMap.clear();
}

void ZoneMap::setUpMaps()
{
	clearUnitMap();
	clearItemMap();
	clearBuildingMap();
	clearPortalMap();
	clearDooDadMap();
}

void ZoneMap::updateSpawnerNum()
{
	numUnitSpawners = 0;
	for (auto dooDad : dooDads)
	{
		if (dooDad->type == DOODAD_UNIT_SPAWNER)
		{
			numUnitSpawners++;
		}
	}
}

void ZoneMap::addToUnitVector(Unit* unitToAdd)
{
	if (std::find(units.begin(), units.end(), unitToAdd) == units.end())
	{
		units.push_back(unitToAdd);
	}
}

void ZoneMap::removeFromUnitVector(Unit* unitToRemove)
{
	auto unitIterator = units.begin();
	while (unitIterator != units.end())
	{
		if ((*unitIterator) == unitToRemove) {
			unitIterator = units.erase(unitIterator);
		}
		else {
			unitIterator++;
		}
	}
}

void ZoneMap::addToPortalVector(ZonePortal* portalToAdd)
{
	if (std::find(portals.begin(), portals.end(), portalToAdd) == portals.end())
	{
		portals.push_back(portalToAdd);
	}
}

void ZoneMap::removeFromPortalVector(ZonePortal* portalToRemove)
{
	auto portalIterator = portals.begin();
	while (portalIterator != portals.end())
	{
		if ((*portalIterator) == portalToRemove) {
			portalIterator = portals.erase(portalIterator);
		}
		else {
			portalIterator++;
		}
	}
}

void ZoneMap::addToDooDadVector(DooDad* dooDadToAdd)
{
	if (std::find(dooDads.begin(), dooDads.end(), dooDadToAdd) == dooDads.end())
	{
		dooDads.push_back(dooDadToAdd);
	}
}

void ZoneMap::removeFromDooDadVector(DooDad* dooDadToRemove)
{
	auto dooDadIterator = dooDads.begin();
	while (dooDadIterator != dooDads.end())
	{
		if ((*dooDadIterator) == dooDadToRemove) {
			dooDadIterator = dooDads.erase(dooDadIterator);
		}
		else {
			dooDadIterator++;
		}
	}
}

void ZoneMap::addToBuildingVector(Building* buildingToAdd)
{
	if (std::find(buildings2.begin(), buildings2.end(), buildingToAdd) == buildings2.end())
	{
		buildings2.push_back(buildingToAdd);
	}
}

void ZoneMap::removeFromBuildingVector(Building* buildingToRemove)
{
	auto buildingIterator = buildings2.begin();
	while (buildingIterator != buildings2.end())
	{
		if ((*buildingIterator) == buildingToRemove) {
			buildingIterator = buildings2.erase(buildingIterator);
		}
		else {
			buildingIterator++;
		}
	}
}

int ZoneMap::getMapKey(int x, int y)
{
	return x * tileMap.size() + y;
}



std::string getLocationSaveString(Location* location)
{
	std::string saveString;
	int uniqueObjectId = getUniqueId();

	saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(LOCATION) + "\n";
	saveString += getAttributeString(getUniqueId(), X_COORD, location->x);
	saveString += getAttributeString(getUniqueId(), Y_COORD, location->y);
	saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(LOCATION) + "\n";
	return saveString;
}

Location* getLocationFromSaveObject(SaveObject saveObject)
{
	Location* returnLocation = new Location{0, 0};
	for (int i = 0; i < saveObject.attributes.size(); i++)
	{
		switch (saveObject.attributes[i].attributeType) {
		case X_COORD:
			returnLocation->x = stoi(saveObject.attributes[i].valueString);
			break;
		case Y_COORD:
			returnLocation->y = stoi(saveObject.attributes[i].valueString);
			break;
		default:
			break;
		}
	}
	return returnLocation;
}


std::string getUnitVectorSaveString(std::vector<Unit*> vector) {
	std::string returnString;
	returnString += std::to_string(vector.size()) + "\n";
	for (int i = 0; i < vector.size(); i++)
	{
		returnString += vector[i]->toSaveString() + "\n";
	}
	return returnString;
}

std::vector<Unit*> getUnitVectorFromSaveString(std::string saveString, RpgTileGridScene* gameScene) {
	std::vector<Unit*> returnVector;

	std::vector<SaveObject> savedItems = getSaveObjectVectorFromSaveString2(saveString);

	for (size_t i = 0; i < savedItems.size(); i++)
	{
		for (int j = 0; j < savedItems[i].attributes.size(); j++)
		{
			if (savedItems[i].attributes[j].attributeType == UNIT_TYPE)
			{
				switch (stoi(savedItems[i].attributes[j].valueString)) {
				case PLAYER:
					returnVector.push_back(new Player(savedItems[i].rawString, gameScene));;
					break;
				case RAT:
					returnVector.push_back(new Rat(savedItems[i].rawString, gameScene));;
					break;
				case SOLDIER:
					returnVector.push_back(new Soldier(savedItems[i].rawString, gameScene));;
					break;
				case TOWNSPERSON:
					returnVector.push_back(new TownsPerson(savedItems[i].rawString, gameScene));;
					break;
				case WHITE_RAT:
					returnVector.push_back(new WhiteRat(savedItems[i].rawString, gameScene));;
					break;
				case RAT_KING:
					returnVector.push_back(new RatKing(savedItems[i].rawString, gameScene));;
					break;
				case SKELETON:
					returnVector.push_back(new Skeleton(savedItems[i].rawString, gameScene));;
					break;
				case SKELETON_KING:
					returnVector.push_back(new SkeletonKing(savedItems[i].rawString, gameScene));;
					break;
				default:
					returnVector.push_back(new RpgUnit(savedItems[i].rawString, gameScene));
					break;
				}
				break;
			}
		}
	}

	return returnVector;
}