#pragma once
#include "RpgUnit.h"

class RpgTileGridScene;

class Player : public RpgUnit
{
public:
    //attributes
    bool cameraFollowPlayer;

    //constructor
    Player();
    Player(SaveObject saveObject, RpgTileGridScene* gameScene);
    Player(int zoneId, int unitType);
    Player(int zoneId, int unitType, RpgTileGridScene* gameScene);
    Player(int zoneId, int unitType, RpgTileGridScene* gameScene, int startX, int startY);
    
    //methods
    //void setStartLocation(int x, int y);
    void update();
    void updateCamera();
    void faceMouseDirection(int x, int y);
    void portalTo(int zoneId, int x, int y) override;
    void death() override;
    void draw() override;

private:
    //attributes
    int lastXDelta;
    int lastXDelta2;
    int lastXDelta3;
    int lastYDelta;
    int lastYDelta2;
    int lastYDelta3;
    //methods
    void createAnimations() override;
    void init();
    void init(RpgTileGridScene * gameScene);
};

