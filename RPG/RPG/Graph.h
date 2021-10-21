#pragma once
#include <unordered_map>
#include <string>

enum LOCATION_SAVE_ATTRIBUTES {
    X_COORD,
    Y_COORD
};

struct Location {
    int x, y;
    bool operator==(const Location& o) const {
        return x == o.x && y == o.y;
    }
};

template <> struct std::hash<Location> {
    std::size_t operator()(const Location& id) const noexcept {
        return std::hash<int>()(id.x ^ (id.y << 4));
    }
};

struct PathKey {
    Location* from;
    Location* to;
    bool operator==(const PathKey& o) const {
        return from->x == o.from->x && from->y == o.from->y && to->x == o.to->x && to->y == o.to->y;
    }
    std::string getString() {
        return "fromx" + std::to_string(from->x) + "y" + std::to_string(from->y) + "tox" + std::to_string(to->x) + "toy" + std::to_string(to->y);
    }
};

template <> struct std::hash<PathKey> {
    std::size_t operator()(const PathKey& id) const noexcept {
        int returnHash = std::hash<int>()(id.from->x ^ (id.from->y << 4)) ^ (id.to->x ^ (id.to->y << 4));
        return returnHash;
    }
};

class Graph
{
public:
    //constructors
    Graph();

    //methods
    void addNeighbors(int x, int y, std::vector<Location*> newNeighbors);
    void addNeighbors(Location* location, std::vector<Location*> newNeighbors);
    std::vector<Location*> getNeighbors(int x, int y);
    std::vector<Location*> getNeighbors(Location* location);
    std::vector<Location*> getNeighbors(Location location);
    double cost(Location* fromLocation, Location* toLocation);
    void addCost(Location* location, int cost);
    void addCost(int x, int y, int cost);
    int getCost(Location* location);
    int getCost(Location location);
    int getCost(int x, int y);

private:
    //attributes
    std::unordered_map<Location, std::vector<Location*>> neighbors;
    std::unordered_map<Location, int> costs;

};