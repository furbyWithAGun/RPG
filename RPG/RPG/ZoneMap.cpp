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
//#include "RpgTileGridScene.h"

ZoneMap::ZoneMap() {
	init();
	for (size_t i = 0; i < MAX_ZONE_HEIGHT; i++)
	{
		std::vector <int> zoneRow;
		for (size_t j = 0; j < MAX_ZONE_WIDTH; j++) {
			zoneRow.push_back(0);
		}
		tileMap.push_back(zoneRow);
	}
	setUpMaps();
}

ZoneMap::ZoneMap(int newId) {
	init(newId);
	for (size_t i = 0; i < MAX_ZONE_HEIGHT; i++)
	{
		std::vector <int> zoneRow;
		for (size_t j = 0; j < MAX_ZONE_WIDTH; j++) {
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
			portals = getPortalVectorFromSaveString(saveObject.attributes[i].valueString);
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
}

ZoneMap::ZoneMap(const ZoneMap& oldMap)
{
	init();
	id = oldMap.id;
    zoneName = oldMap.zoneName;
	tileMap = oldMap.tileMap;
	buildingMap = oldMap.buildingMap;
	unitMap = oldMap.unitMap;
	itemMap = oldMap.itemMap;
	portalMap = oldMap.portalMap;
	doodads = oldMap.doodads;
	buildings = oldMap.buildings;
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
	portals.push_back(newPortal);
	portalMap[newTileCoords[0]][newTileCoords[1]] = newPortal;
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
	if (xpos >= portalMap.size()) {
		return nullptr;
	} else if (ypos >= portalMap[0].size() || xpos < 0 || ypos < 0)
	{
		return nullptr;
	}
	return portalMap[xpos][ypos];
}


DooDad* ZoneMap::getDooDadAtLocation(int xpos, int ypos)
{
	if (xpos >= dooDadMap.size()) {
		return nullptr;
	}
	else if (ypos >= dooDadMap[0].size() || xpos < 0 || ypos < 0)
	{
		return nullptr;
	}
	return dooDadMap[xpos][ypos];

	/*for (auto dooDad : doodads) {
		if (dooDad->tileCoords[0] == xpos && dooDad->tileCoords[1] == ypos)
		{
			return dooDad;
		}
	}
	return nullptr;*/
}

void ZoneMap::addDooDadToLocation(DooDad* dooDad, int xpos, int ypos)
{
	dooDad->zoneId = id;
	dooDad->tileCoords[0] = xpos;
	dooDad->tileCoords[1] = ypos;
	doodads.push_back(dooDad);
	dooDadMap[xpos][ypos] = dooDad;
}

void ZoneMap::destroyDooDad(DooDad* dooDad)
{
	dooDadMap[dooDad->tileCoords[0]][dooDad->tileCoords[1]] = nullptr;
	auto dooDadIterator = doodads.begin();
	while (dooDadIterator != doodads.end())
	{
		if ((*dooDadIterator) == dooDad) {
			dooDadIterator = doodads.erase(dooDadIterator);
			break;
		}
		else {
			dooDadIterator++;
		}
	}
	if (dooDad->assignedToBuilding != nullptr)
	{
		dooDad->assignedToBuilding->unAssignDooDad(dooDad);
	}
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
		destroyUnit(unit);
		//unit->toBeDeleted = true;
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
	if (xpos < 0 || ypos < 0 || xpos >= itemMap.size() || ypos >= itemMap[0].size())
	{
		return std::vector<Item*>();
	}
	return itemMap[xpos][ypos];
}

void ZoneMap::removePortalAtLocation(int xpos, int ypos)
{
	int delIndex = -1;
	for (size_t i = 0; i < portals.size(); i++)
	{
		if (portals[i]->tileCoords[0] == xpos && portals[i]->tileCoords[1] == ypos) {
			delIndex = i;
			break;
		}
	}
	if (delIndex != -1)
	{
		delete portals[delIndex];
		portals.erase(portals.begin() + delIndex);
		portalMap[xpos][ypos] = nullptr;
	}
}

std::string ZoneMap::toSaveString() {
	std::string saveString;
	int uniqueObjectId = getUniqueId();

	saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(ZONE_MAP) + "\n";
	saveString += getAttributeString(getUniqueId(), ZONE_MAP_ID, id);
	saveString += getAttributeString(getUniqueId(), ZONE_NAME, zoneName);
	saveString += getAttributeString(getUniqueId(), TILE_MAP, get2DIntVectorSaveString(tileMap));
	saveString += getAttributeString(getUniqueId(), PORTALS, getPortalVectorSaveString(portals));
	saveString += getAttributeString(getUniqueId(), DOODADS, getDooDadVectorSaveString(doodads));
	saveString += getAttributeString(getUniqueId(), BUILDINGS, getBuildingVectorSaveString(buildings));
	saveString += getAttributeString(getUniqueId(), UNITS, getUnitVectorSaveString(units));
	saveString += getAttributeString(getUniqueId(), ZONE_BACKGROUND, backGroundTile);
	saveString += getAttributeString(getUniqueId(), MOB_SPAWN, mobSpawn);
	saveString += getAttributeString(getUniqueId(), DIFFICULTY, difficulty);
	saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(ZONE_MAP) + "\n";

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
			scene->renderTexture(backGroundTile, ((scene->tileWidth * j) + scene->mainCanvasStartX) + (scene->xOffset % scene->tileWidth) - scene->tileWidth * 2, scene->tileHeight * i + (scene->yOffset % scene->tileHeight) - scene->tileHeight * 2, scene->tileWidth * 3, scene->tileHeight * 3);
		}
	}

	int startcoords[2];
	int endcoords[2];
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
	if (startX >= tileMap[0].size())
	{
		startX = tileMap[0].size();
	}
	//int endX = ((RpgTileGridScene*)scene)->player->tileLocation->x + (scene->desiredTilesAcross / 2) + 1;
	if (endX < 0)
	{
		endX = 0;
	}
	if (endX >= tileMap[0].size())
	{
		endX = tileMap[0].size();
	}
	//int startY = ((RpgTileGridScene*)scene)->player->tileLocation->y - (scene->desiredTilesDown / 2) - 1;
	if (startY < 0)
	{
		startY = 0;
	}
	if (startY >= tileMap.size())
	{
		startY = tileMap.size();
	}
	//int endY = ((RpgTileGridScene*)scene)->player->tileLocation->y + (scene->desiredTilesDown / 2) + 1;
	if (endY < 0)
	{
		endY = 0;
	}
	if (endY >= tileMap.size())
	{
		endY = tileMap.size();
	}

	int xz = 0;

	//draw zone
	for (int i = startY; i < endY; i++) {
		for (int j = startX; j < endX; j++) {
			if ((((scene->tileWidth * (j + 1)) + scene->mainCanvasStartX + scene->xOffset >= 0) && ((scene->tileWidth * (j - 1)) + scene->mainCanvasStartX + scene->xOffset <= SCREEN_WIDTH)) && ((scene->tileHeight * (i + 1) + scene->yOffset >= -scene->tileHeight) && (scene->tileHeight * (i - 1) + scene->yOffset <= SCREEN_HEIGHT)))
			{
				//render tiles
				xz++;
				scene->renderTexture(scene->mapTiles[tileMap[i][j]].textureKey, (scene->tileWidth * j) + scene->mainCanvasStartX + scene->xOffset - scene->tileWidth, scene->tileHeight * i + scene->yOffset - scene->tileHeight, scene->tileWidth * 3, scene->tileHeight * 3);
			}
		}
		for (int j = startX; j < endX; j++) {
			//render buildings
			if ((((scene->tileWidth * (j + 1)) + scene->mainCanvasStartX + scene->xOffset >= 0) && ((scene->tileWidth * (j - 1)) + scene->mainCanvasStartX + scene->xOffset <= SCREEN_WIDTH)) && ((scene->tileHeight * (i + 1) + scene->yOffset >= -scene->tileHeight) && (scene->tileHeight * (i - 1) + scene->yOffset <= SCREEN_HEIGHT)))
			{
				if (buildingMap[j][i] != nullptr)
				{
					if (buildingMap[j][i]->getTileAtMapLocation(j, i) != nullptr) {
						SDL_SetTextureColorMod(scene->engine->textures[buildingMap[j][i]->getTileAtMapLocation(j, i)->textureKey].texture, 255, 255, 255);
						SDL_SetTextureAlphaMod(scene->engine->textures[buildingMap[j][i]->getTileAtMapLocation(j, i)->textureKey].texture, 255);
						xz++;
						scene->renderTexture(buildingMap[j][i]->getTileAtMapLocation(j, i)->textureKey, (scene->tileWidth * j) + scene->mainCanvasStartX + scene->xOffset - scene->tileWidth, scene->tileHeight * i + scene->yOffset - scene->tileHeight, scene->tileWidth * 3, scene->tileHeight * 3);
					}
				}
			}
		}

		//render portals
		for (int j = startX; j < endX; j++) {
			if ((((scene->tileWidth * (j + 1)) + scene->mainCanvasStartX + scene->xOffset >= 0) && ((scene->tileWidth * (j - 1)) + scene->mainCanvasStartX + scene->xOffset <= SCREEN_WIDTH)) && ((scene->tileHeight * (i + 1) + scene->yOffset >= -scene->tileHeight) && (scene->tileHeight * (i - 1) + scene->yOffset <= SCREEN_HEIGHT)))
			{
				if (getPortalAtLocation(j, i) != nullptr) {
					xz++;
					scene->renderTexture(portalMap[j][i]->textureId, (scene->tileWidth * j) + scene->mainCanvasStartX + scene->xOffset - scene->tileWidth, scene->tileHeight * i + scene->yOffset - scene->tileHeight, scene->tileWidth * 3, scene->tileHeight * 3);
				}
			}
		}

		//render doodads
		for (int j = startX; j < endX; j++) {
			if ((((scene->tileWidth * (j + 1)) + scene->mainCanvasStartX + scene->xOffset >= 0) && ((scene->tileWidth * (j - 1)) + scene->mainCanvasStartX + scene->xOffset <= SCREEN_WIDTH)) && ((scene->tileHeight * (i + 1) + scene->yOffset >= -scene->tileHeight) && (scene->tileHeight * (i - 1) + scene->yOffset <= SCREEN_HEIGHT)))
			{
				if (getDooDadAtLocation(j, i) != nullptr) {
					xz++;
					scene->renderTexture(getDooDadAtLocation(j, i)->textureKey, (scene->tileWidth * j) + scene->mainCanvasStartX + scene->xOffset - scene->tileWidth, scene->tileHeight * i + scene->yOffset - scene->tileHeight, scene->tileWidth * 3, scene->tileHeight * 3);
				}
			}
		}

		//render items
		for (int j = startX; j < endX; j++) {
			if ((((scene->tileWidth * (j + 1)) + scene->mainCanvasStartX + scene->xOffset >= 0) && ((scene->tileWidth * (j - 1)) + scene->mainCanvasStartX + scene->xOffset <= SCREEN_WIDTH)) && ((scene->tileHeight * (i + 1) + scene->yOffset >= -scene->tileHeight) && (scene->tileHeight * (i - 1) + scene->yOffset <= SCREEN_HEIGHT)))
			{
				for (int k = 0; k < getItemsAtLocation(j, i).size(); k++) {
					xz++;
					scene->renderTexture(itemMap[j][i][k]->textureKey, (scene->tileWidth * j) + scene->mainCanvasStartX + scene->xOffset, scene->tileHeight * i + scene->yOffset, scene->tileWidth, scene->tileHeight);
				}
			}
		}
		//render units
		for (int j = startX; j < endX; j++) {
			if ((((scene->tileWidth * (j + 1)) + scene->mainCanvasStartX + scene->xOffset >= 0) && ((scene->tileWidth * (j - 1)) + scene->mainCanvasStartX + scene->xOffset <= SCREEN_WIDTH)) && ((scene->tileHeight * (i + 1) + scene->yOffset >= -scene->tileHeight) && (scene->tileHeight * (i - 1) + scene->yOffset <= SCREEN_HEIGHT)))
			{
				for (auto unit : unitMap[j][i]) {
					xz++;
					unit->draw();
				}
			}
		}
	}
}

Unit* ZoneMap::getUnitAtLocation(int x, int y)
{
	if (x < 0 || y < 0 || x >= unitMap.size() || y >= unitMap[0].size())
	{
		return nullptr;
	}
	if (unitMap[x][y].size() > 0)
	{
		try {

			return unitMap[x][y].at(0);
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
	units.push_back(unit);
	unitMap[x][y].push_back(unit);
	return true;
}

Building* ZoneMap::getBuildingAtLocation(int x, int y)
{
	if (x < 0 || y < 0 || x >= buildingMap.size() || y >= buildingMap[0].size())
	{
		return nullptr;
	}
	return buildingMap[x][y];
}

bool ZoneMap::addBuildingToLocation(Building* building, int x, int y)
{
	building->tileLocation->x = x;
	building->tileLocation->y = y;
	for (size_t i = 0; i < building->width; i++)
	{
		for (size_t j = 0; j < building->height; j++)
		{
			buildingMap[i + building->tileLocation->x][j + building->tileLocation->y] = building;
		}
	}
	buildings.push_back(building);
	return true;
}

bool ZoneMap::removeBuildingFromZone(Building* building)
{
	removeBuildingFromMap(building);
	auto buildingIterator = buildings.begin();
	while (buildingIterator != buildings.end())
	{
		if ((*buildingIterator) == building) {
			buildingIterator = buildings.erase(buildingIterator);
			break;
		}
		else {
			buildingIterator++;
		}
	}
	while (building->assignedDooDads.size() > 0)
	{
		DooDad* dooDad = building->assignedDooDads[0];
		building->unAssignDooDad(dooDad);
		destroyDooDad(dooDad);
	}
	return true;
}

bool ZoneMap::removeBuildingFromMap(Building* building)
{
	for (size_t i = 0; i < building->width; i++)
	{
		for (size_t j = 0; j < building->height; j++)
		{
			buildingMap[i + building->tileLocation->x][j + building->tileLocation->y] = nullptr;
		}
	}
	return true;
}


std::vector<Unit*> ZoneMap::getUnitsAtLocation(int x, int y)
{
	if (x < 0 || y < 0 || x >= unitMap.size() || y >= unitMap[0].size())
	{
		std::vector<Unit*>();
	}
	if (unitMap[x][y].size() > 0)
	{
		return unitMap[x][y];
	}
	else {
		return std::vector<Unit*>();
	}
}

void ZoneMap::update()
{
	for (auto unit : units) {
		if (unit->active)
		{
			unit->update();
		}
	}

	//remove dead units
	removeDeadUnits();	

	for (auto dooDad : doodads)
	{
		dooDad->update();
	}
}

void ZoneMap::removeUnitFromLocation(Unit* unit, int x, int y) {
	auto unitIterator = unitMap[x][y].begin();
	while (unitIterator != unitMap[x][y].end())
	{
		if ((*unitIterator) == unit) {
			unitIterator = unitMap[x][y].erase(unitIterator);
		}
		else {
			unitIterator++;
		}
	}
}

void ZoneMap::updateUnitMap()
{
	clearUnitMap();
	for (auto unit : units)
	{
		unitMap[unit->tileLocation->x][unit->tileLocation->y].push_back(unit);
		unitMap[unit->tileDestination->x][unit->tileDestination->y].push_back(unit);
	}
}

bool ZoneMap::isTilePassable(TileGridScene* scene,  int x, int y)
{
	if (x < 0 || y < 0 || y >= tileMap.size() || x >= tileMap[y].size())
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

	return scene->mapTiles[tileMap[y][x]].passable && getUnitAtLocation(x, y) == nullptr ;
}

bool ZoneMap::isTilePassableIgnoreAllUnits(TileGridScene* scene, int x, int y)
{
	if (x < 0 || y < 0 || y >= tileMap.size() || x >= tileMap[y].size())
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

	return scene->mapTiles[tileMap[y][x]].passable;
}

bool ZoneMap::isTilePassableIgnoreUnit(TileGridScene* scene, int x, int y, Unit* unitToIgnore)
{
	if (x < 0 || y < 0 || y >= tileMap.size() || x >= tileMap[y].size())
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

	return scene->mapTiles[tileMap[y][x]].passable && (getUnitAtLocation(x, y) == nullptr || ignoreUnitPresent);
}

bool ZoneMap::isTilePassableIgnoreUnits(TileGridScene* scene, int x, int y, std::vector<Unit*> unitsToIgnore)
{
	if (x < 0 || y < 0 || y >= tileMap.size() || x >= tileMap[y].size())
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
	return scene->mapTiles[tileMap[y][x]].passable && (ignoreUnitPresent || getUnitAtLocation(x, y) == nullptr);
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

void ZoneMap::destroyUnit(Unit* unit)
{
	removeUnitFromLocation(unit, unit->tileLocation->x, unit->tileLocation->y);
	removeUnitFromLocation(unit, unit->tileDestination->x, unit->tileDestination->y);
	auto unitIterator = units.begin();
	while (unitIterator != units.end())
	{
		if ((*unitIterator) == unit) {
			unitIterator = units.erase(unitIterator);
			break;
		}
		else {
			unitIterator++;
		}
	}
	if (unit->beingTargetedBy.size() > 0)
	{
		for (auto targetingUnit : unit->beingTargetedBy) {
			targetingUnit->targetUnit = nullptr;
		}
	}

	delete (unit);
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
	if (unit->toBeDeleted)
	{
		return std::vector<Location*>();
	}
	int new_cost = 0;
	int priority = 0;
	typedef std::pair<int, Location*> PQElement;
	std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> frontier;
	Location* current;
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
		if (current->x == unit->tileDestination->x && current->y == unit->tileDestination->y)
		{
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
	std::vector<Location*> potentialPath = constructPath(cameFrom, startLocation, unit->tileDestination);
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

void ZoneMap::removeDeadUnits()
{
	auto unitIterator = units.begin();
	while (unitIterator != units.end())
	{
		if ((*unitIterator)->toBeDeleted) {
			removeUnitFromLocation(*unitIterator, (*unitIterator)->tileLocation->x, (*unitIterator)->tileLocation->y);
			removeUnitFromLocation(*unitIterator, (*unitIterator)->tileDestination->x, (*unitIterator)->tileDestination->y);
			for (auto unit : (*unitIterator)->beingTargetedBy) {
				unit->targetUnit = nullptr;
			}
			delete (*unitIterator);
			unitIterator = units.erase(unitIterator);
		}
		else {
			unitIterator++;
		}
	}
}

void ZoneMap::setupGraph(TileGridScene* scene)
{
	int directions[4] = { UP, DOWN, RIGHT, LEFT };
	for (int y = 0; y < tileMap.size(); y++)
	{
		for (int x = 0; x < tileMap[0].size(); x++) 
		{
			if (scene->mapTiles[tileMap[y][x]].passable)
			{
				std::vector<Location*> neighbors = std::vector<Location*>();
				for (int direction : directions) {
					switch (direction)
					{
					case UP:
						if (y > 0 && scene->mapTiles[tileMap[y - 1][x]].passable)
						{
							neighbors.push_back(new Location{ x, y - 1 });
						}
						break;
					case DOWN:
						if (y + 1 < tileMap.size() && scene->mapTiles[tileMap[y + 1][x]].passable)
						{
							neighbors.push_back(new Location{ x, y + 1 });
						}
						break;
					case LEFT:
						if (x > 0 && scene->mapTiles[tileMap[y][x - 1]].passable)
						{
							neighbors.push_back(new Location{ x - 1, y });
						}
					case RIGHT:
						if (x + 1 < tileMap[y].size() && scene->mapTiles[tileMap[y][x + 1]].passable)
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
	
	for (int y = 0; y < tileMap.size(); y++)
	{
		for (int x = 0; x < tileMap[0].size(); x++)
		{
			if (scene->mapTiles[tileMap[y][x]].passable)
			{
				for (int yto = 0; yto < tileMap.size(); yto++)
				{
					for (int xto = 0; xto < tileMap[0].size(); xto++)
					{
						if (scene->mapTiles[tileMap[yto][xto]].passable)
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
			if (savedBuildings[i].attributes[j].attributeType == BULDING_TYPE)
			{
				switch (stoi(savedBuildings[i].attributes[j].valueString)) {
				case BUILDING_ITEM_SHOP:
					returnVector.push_back(new ItemShop(savedBuildings[i].rawString));;
					break;
				case BUILDING_CAMP_COMMAND_CENTRE:
					returnVector.push_back(new CampCommandCentre(savedBuildings[i].rawString));;
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
	for (size_t i = 0; i < tileMap[0].size(); i++)
	{
		unitMap.push_back({});
		for (size_t j = 0; j < tileMap.size(); j++) {
			unitMap[i].push_back(std::vector<Unit*>());
		}
	}
}

void ZoneMap::clearItemMap()
{
	itemMap.clear();
	for (size_t i = 0; i < tileMap[0].size(); i++)
	{
		itemMap.push_back({});
		for (size_t j = 0; j < tileMap.size(); j++) {
			itemMap[i].push_back(std::vector<Item*>());
		}
	}
}
void ZoneMap::clearDooDadMap()
{
	dooDadMap.clear();
	for (size_t i = 0; i < tileMap[0].size(); i++)
	{
		dooDadMap.push_back({});
		for (size_t j = 0; j < tileMap.size(); j++) {
			dooDadMap[i].push_back(nullptr);
		}
	}
}
void ZoneMap::clearBuildingMap()
{
	buildingMap.clear();
	for (size_t i = 0; i < tileMap[0].size(); i++)
	{
		buildingMap.push_back({});
		for (size_t j = 0; j < tileMap.size(); j++) {
			buildingMap[i].push_back(nullptr);
		}
	}
}

void ZoneMap::clearPortalMap()
{
	portalMap.clear();
	for (size_t i = 0; i < tileMap[0].size(); i++)
	{
		portalMap.push_back({});
		for (size_t j = 0; j < tileMap.size(); j++) {
			portalMap[i].push_back(nullptr);
		}
	}
}

void ZoneMap::buildPortalMap()
{
	for (auto portal : portals)
	{
		portalMap[portal->tileCoords[0]][portal->tileCoords[1]] = portal;
	}
}

void ZoneMap::buildBuildingMap()
{
	for (auto building : buildings)
	{
		for (int x = 0; x < building->tileMap.size(); x++) {
			for (int y = 0; y < building->tileMap[x].size(); y++) {
				buildingMap[building->tileLocation->x + x][building->tileLocation->y + y] = building;
			}
		}
	}
}

void ZoneMap::buildDooDadMap()
{
	for (auto dooDad : doodads)
	{
		dooDadMap[dooDad->tileCoords[0]][dooDad->tileCoords[1]] = dooDad;
	}
}

void ZoneMap::setUpMaps()
{
	clearUnitMap();
	clearItemMap();
	clearBuildingMap();
	clearPortalMap();
	clearDooDadMap();
	buildPortalMap();
	buildBuildingMap();
	buildDooDadMap();
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