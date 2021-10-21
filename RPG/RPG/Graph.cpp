#include "Graph.h"
#include "SaveFile.h"

Graph::Graph()
{
}

void Graph::addNeighbors(int x, int y, std::vector<Location*> newNeighbors)
{
    neighbors[Location{x, y}] = newNeighbors;
}

void Graph::addNeighbors(Location* location, std::vector<Location*> newNeighbors)
{
    neighbors[*location] = newNeighbors;
}

std::vector<Location*> Graph::getNeighbors(int x, int y)
{
    return neighbors[Location{ x, y }];
}

std::vector<Location*> Graph::getNeighbors(Location* location)
{
    return neighbors[*location];
}

std::vector<Location*> Graph::getNeighbors(Location location)
{
    return neighbors[location];
}

double Graph::cost(Location* fromLocation, Location* toLocation)
{
    return getCost(toLocation);
}

void Graph::addCost(Location* location, int cost)
{
    costs[*location] = cost;
}

void Graph::addCost(int x, int y, int cost)
{
    costs[Location{ x, y }] = cost;
}

int Graph::getCost(Location* location)
{
    return costs[*location];
}

int Graph::getCost(Location location)
{
    return costs[location];
}


int Graph::getCost(int x, int y)
{
    return costs[Location{ x, y }];
}
