#pragma once
#include <vector>
#include "MapTile.h"
#include "ZonePortal.h"
#include <string>
#include <algorithm>
#include "Item.h"
#include "Graph.h"
#include "BuildingFactory.h"

enum ZONE_MAP_ATTRIBUTES{
    ZONE_MAP_ID,
    TILE_MAP,
    PORTALS,
    ZONE_NAME,
    ZONE_BACKGROUND,
    MOB_SPAWN,
    DOODADS,
    DIFFICULTY,
    BUILDINGS,
    UNITS
};

class Unit;
class TileGridScene;
class RpgTileGridScene;
class DooDad;

class ZoneMap {
    public:
        //attributes
        int id;
        std::string zoneName;
        std::vector< std::vector<int> > tileMap;
        Graph graph;
        int playerPresence;
        int difficulty;
        int backGroundTile;
        bool mobSpawn;

        //need to setup save attributes:
        int maxUnits;
        int numUnitSpawners;
        int updateSpawnerNumRate;
        int updateSpawnerNumTick;

        //constructors
        ZoneMap(int newId, std::vector< std::vector<int> > tiles);
        ZoneMap(int newId);
        ZoneMap(SaveObject saveObject, RpgTileGridScene* gameScene);
        ZoneMap(const ZoneMap &oldMap);
        ZoneMap();

        //destructor
        ~ZoneMap();

        //methods
        //handle the maps
        
        std::vector<Unit*> getUnits();
        std::vector<ZonePortal*> getPortals();
        std::vector<DooDad*> getDooDads();
        std::vector<Building*> getBuildings();
        void addPortalToLocation(ZonePortal* portal, int x, int y);
        void assignNewTileMap(std::vector< std::vector<int> > tiles);
        void addZonePortal(int textureId, std::vector <int> newTileCoords, int newExitZoneId, std::vector <int> newExitTileCoords);
        ZonePortal* getPortalAtLocation(int xpos, int ypos);
        DooDad* getDooDadAtLocation(int xpos, int ypos);
        void addDooDadToLocation(DooDad* dooDad, int xpos, int ypos);
        void destroyDooDad(DooDad* dooDad);
        void destroyBuilding(Building* building);
        void destroyBuildingButNotunits(Building* building);
        std::vector<Item*> getItemsAtLocation(int xpos, int ypos);
        void removeItemAtLocation(Item* item, int xpos, int ypos);
        void addItemToLocation(Item* item, int xpos, int ypos);
        void removePortalAtLocation(int xpos, int ypos);
        std::string toSaveString();
        int getDevelopmentLevel();
        int getDifficulty();
        void draw(TileGridScene* scene);
        Building* getBuildingAtLocation(int x, int y);
        bool addBuildingToLocation(Building* building, int x, int y);
        bool removeBuildingFromZone(Building* building);
        bool removeAllBuildingTilesFromMap(Building* building);
        Unit* getUnitAtLocation(int x, int y);
        bool addUnitToLocation(Unit* unit, int x, int y);
        bool addUnitToDestinationLocation(Unit* unit);
        bool removeUnitFromZone(Unit* unit);
        std::vector<Unit*> getUnitsAtLocation(int x, int y);
        void update();
        void removeUnitFromLocation(Unit* unit, int x, int y);
        void updateUnitMap();
        bool isTilePassable(TileGridScene* scene, int x, int y);
        bool isTilePassableIgnoreAllUnits(TileGridScene* scene, int x, int y);
        bool isTilePassableIgnoreUnit(TileGridScene* scene, int x, int y, Unit* unitToIgnore);
        bool isTilePassableIgnoreUnits(TileGridScene* scene, int x, int y, std::vector<Unit*> unitsToIgnore);
        void unitEntersTile(Unit* unit, int x, int y);
        std::vector<Location*> getPath(TileGridScene* scene, Location* startLocation, Location* destinationLocation);
        std::vector<Location*> getPathIgnoreAllUnits(TileGridScene* scene, Location* startLocation, Location* destinationLocation);
        std::vector<Location*> getPathToUnit(TileGridScene* scene, Location* startLocation, Unit* unit, Unit* followingUnit);
        std::vector<int> getPathDirections(TileGridScene* scene, Location* startLocation, Location* destinationLocation);
        std::vector<int> getPathDirectionsIgnoreAllunits(TileGridScene* scene, Location* startLocation, Location* destinationLocation);
        std::vector<int> getPathDirectionsToUnit(TileGridScene* scene, Location* startLocation, Unit* unit, Unit* followingUnit);
        void setupGraph(TileGridScene* scene);
        void calculateDirectPaths(TileGridScene* scene);
        int manhattenDistance(Location* startLocation, Location* destinationLocation);
        std::vector<Location*> constructPath(std::unordered_map< Location, Location*> cameFrom, Location* startLocation, Location* destinationLocation);
        std::vector<Location*> constructPathToUnit(std::unordered_map< Location, Location*> cameFrom, Location* startLocation, Unit* unit);
        int getNumUnits();

    private:
        //attributes
        std::unordered_map<std::string, std::vector<int>> directPaths;
        //object vectors
        std::vector<Unit*> units;
        std::vector<ZonePortal*> portals;
        std::vector< DooDad* > dooDads;
        std::vector< Building* > buildings2;
        //object maps
        std::unordered_map<int, std::vector<Unit*>> unitMap;
        std::unordered_map< int, std::vector<Item*> > itemMap;
        std::unordered_map< int, ZonePortal* > portalMap;
        std::unordered_map< int, DooDad* > dooDadMap;
        std::unordered_map< int, Building* > buildingMap2;

        //methods
        void init();
        void init(int newId);
        std::string getPortalVectorSaveString(std::vector<ZonePortal*> vector);
        std::string getDooDadVectorSaveString(std::vector<DooDad*> vector);
        std::string getBuildingVectorSaveString(std::vector<Building*> vector);
        std::vector<ZonePortal*> getPortalVectorFromSaveString(std::string saveString);
        std::vector<DooDad*> getDooDadVectorFromSaveString(std::string saveString, TileGridScene* gameScene);
        std::vector<Building*> getBuildingVectorFromSaveString(std::string saveString);
        void clearUnitMap();
        void clearItemMap();
        void clearDooDadMap();
        void clearBuildingMap();
        void clearPortalMap();
        void setUpMaps();
        void updateSpawnerNum();

        //handle object vectors
        //unit vector
        void addToUnitVector(Unit* unitToAdd);
        void removeFromUnitVector(Unit* unitToRemove);
        //portal vector
        void addToPortalVector(ZonePortal* portalToAdd);
        void removeFromPortalVector(ZonePortal* portalToRemove);
        //doodad vector
        void addToDooDadVector(DooDad* dooDadToAdd);
        void removeFromDooDadVector(DooDad* dooDadToRemove);
        //building vector
        void addToBuildingVector(Building* buildingToAdd);
        void removeFromBuildingVector(Building* buildingToRemove);

        //handle maps
        int getMapKey(int x, int y);
        //unit map
        void addToUnitMap(Unit* unit);
        void addToUnitMap(int x, int y, Unit* unit);
        Unit* getUnitFromMap(int x, int y);
        std::vector<Unit*> getUnitsFromMap(int x, int y);
        void removeUnitFromMap(Unit* unit);
        void removeUnitFromMap(int x, int y, Unit* unit);
        //portal map
        void addToPortalMap(ZonePortal* portal);
        void addToPortalMap(int x, int y, ZonePortal* portal);
        ZonePortal* getPortalFromMap(int x, int y);
        void removePortalFromMap(ZonePortal* portal);
        void removePortalFromMap(int x, int y, ZonePortal* portal);
        //dooDad map
        void addToDooDadMap(DooDad* dooDad, int x, int y);
        DooDad* getDooDadFromMap(int x, int y);
        void removeDooDadFromMap(DooDad* dooDad, int x, int y);
        //building map
        void addToBuildingMap(Building* building, int x, int y);
        Building* getBuildingFromMap(int x, int y);
        void removeBuildingFromMap(Building* building, int x, int y);
        //item map
        void addToItemMap(int x, int y, Item* item);
        Item* getItemFromMap(int x, int y);
        std::vector<Item*> getItemsFromMap(int x, int y);
        void removeItemFromMap(int x, int y, Item* item);
};


std::string getLocationSaveString(Location* location);
Location* getLocationFromSaveObject(SaveObject saveObject);

std::string getUnitVectorSaveString(std::vector<Unit*> vector);
std::vector<Unit*> getUnitVectorFromSaveString(std::string saveString, RpgTileGridScene* gameScene);