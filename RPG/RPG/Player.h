#pragma once
#include "Unit.h"

class TileGridScene;

class Player : public Unit
{
public:
    //attributes
    //std::vector<int> startLocation;

    //constructor
    Player();
    Player(int zoneId, int unitType);
    Player(int zoneId, int unitType, TileGridScene* gameScene);
    Player(int zoneId, int unitType, TileGridScene* gameScene, int startX, int startY);
    
    //methods
    //void setStartLocation(int x, int y);
    void update();
    void faceMouseDirection(int x, int y);

private:
    //attributes

    //methods
    void createAnimations();
    void init();
    void init(TileGridScene * gameScene);
};

