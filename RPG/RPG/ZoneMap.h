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
        std::vector< std::vector< std::vector<Unit*> > > unitMap;
        std::vector< std::vector<std::vector<Item*>> > itemMap;
        std::vector< std::vector<ZonePortal*> > portalMap;
        std::vector< std::vector<Building* > > buildingMap;
        std::vector< DooDad* > doodads;
        std::vector< Building* > buildings;
        std::vector<Unit*> units;
        std::vector<ZonePortal*> portals;
        Graph graph;
        int playerPresence;
        int difficulty;
        int backGroundTile;
        bool mobSpawn;

        //constructors
        ZoneMap(int newId, std::vector< std::vector<int> > tiles);
        ZoneMap(int newId);
        ZoneMap(SaveObject saveObject, RpgTileGridScene* gameScene);
        ZoneMap(const ZoneMap &oldMap);
        ZoneMap();

        //destructor
        ~ZoneMap();

        //methods
        void assignNewTileMap(std::vector< std::vector<int> > tiles);
        void addZonePortal(int textureId, std::vector <int> newTileCoords, int newExitZoneId, std::vector <int> newExitTileCoords);
        ZonePortal* getPortalAtLocation(int xpos, int ypos);
        DooDad* getDooDadAtLocation(int xpos, int ypos);
        void addDooDadToLocation(DooDad* dooDad, int xpos, int ypos);
        void destroyDooDad(DooDad* dooDad);
        void destroyBuilding(Building* building);
        void destroyBuildingButNotunits(Building* building);
        std::vector<Item*> getItemsAtLocation(int xpos, int ypos);
        void removePortalAtLocation(int xpos, int ypos);
        std::string toSaveString();
        int getDevelopmentLevel();
        int getDifficulty();
        void draw(TileGridScene* scene);
        Building* getBuildingAtLocation(int x, int y);
        bool addBuildingToLocation(Building* building, int x, int y);
        bool removeBuildingFromZone(Building* building);
        bool removeBuildingFromMap(Building* building);
        Unit* getUnitAtLocation(int x, int y);
        bool addUnitToLocation(Unit* unit, int x, int y);
        std::vector<Unit*> getUnitsAtLocation(int x, int y);
        void update();
        void removeUnitFromLocation(Unit* unit, int x, int y);
        void updateUnitMap();
        bool isTilePassable(TileGridScene* scene, int x, int y);
        bool isTilePassableIgnoreAllUnits(TileGridScene* scene, int x, int y);
        bool isTilePassableIgnoreUnit(TileGridScene* scene, int x, int y, Unit* unitToIgnore);
        bool isTilePassableIgnoreUnits(TileGridScene* scene, int x, int y, std::vector<Unit*> unitsToIgnore);
        void unitEntersTile(Unit* unit, int x, int y);
        void destroyUnit(Unit* unit);
        std::vector<Location*> getPath(TileGridScene* scene, Location* startLocation, Location* destinationLocation);
        std::vector<Location*> getPathIgnoreAllUnits(TileGridScene* scene, Location* startLocation, Location* destinationLocation);
        //std::vector<Location*> getPathToUnit(TileGridScene* scene, Location* startLocation, Unit* unit);
        std::vector<Location*> getPathToUnit(TileGridScene* scene, Location* startLocation, Unit* unit, Unit* followingUnit);
        std::vector<int> getPathDirections(TileGridScene* scene, Location* startLocation, Location* destinationLocation);
        std::vector<int> getPathDirectionsIgnoreAllunits(TileGridScene* scene, Location* startLocation, Location* destinationLocation);
        //std::vector<int> getPathDirectionsToUnit(TileGridScene* scene, Location* startLocation, Unit* unit);
        std::vector<int> getPathDirectionsToUnit(TileGridScene* scene, Location* startLocation, Unit* unit, Unit* followingUnit);
        void setupGraph(TileGridScene* scene);
        void calculateDirectPaths(TileGridScene* scene);
        int manhattenDistance(Location* startLocation, Location* destinationLocation);
        std::vector<Location*> constructPath(std::unordered_map< Location, Location*> cameFrom, Location* startLocation, Location* destinationLocation);
        std::vector<Location*> constructPathToUnit(std::unordered_map< Location, Location*> cameFrom, Location* startLocation, Unit* unit);
        //std::vector<Location*> constructPathToUnit(std::unordered_map< Location, Location*> cameFrom, Location* startLocation, Unit* unit, Unit* followingUnit);
        void removeDeadUnits();

    private:
        //attributes
        std::unordered_map<std::string, std::vector<int>> directPaths;

        //methods
        void init();
        void init(int newId);
        std::string getPortalVectorSaveString(std::vector<ZonePortal*> vector);
        std::string getDooDadVectorSaveString(std::vector<DooDad*> vector);
        std::string getBuildingVectorSaveString(std::vector<Building*> vector);
        std::vector<ZonePortal*> getPortalVectorFromSaveString(std::string saveString);
        std::vector<DooDad*> getDooDadVectorFromSaveString(std::string saveString);
        std::vector<Building*> getBuildingVectorFromSaveString(std::string saveString);
        void clearUnitMap();
        void clearItemMap();
        void clearBuildingMap();
        void clearPortalMap();
        void buildPortalMap();
        void buildBuildingMap();
        void setUpMaps();
};


std::string getLocationSaveString(Location* location);
Location* getLocationFromSaveObject(SaveObject saveObject);

std::string getUnitVectorSaveString(std::vector<Unit*> vector);
std::vector<Unit*> getUnitVectorFromSaveString(std::string saveString, RpgTileGridScene* gameScene);