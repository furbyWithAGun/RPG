#pragma once
#include "MenuButton.h"
#include "RpgWorldBuilderScene.h"
#include "BaseGameEngine.h"

class MapBuilderTileButton : public MenuButton
{
public:
    //attributes
    RpgWorldBuilderScene* scene;
    BaseGameEngine* engine;
    MapTile* tile;

    //constructors
    MapBuilderTileButton();
    MapBuilderTileButton(RpgWorldBuilderScene* gameScene, MapTile* newTile);
    MapBuilderTileButton(int elementId, RpgWorldBuilderScene* gameScene, MapTile* newTile);

    //methods
    void onClick();

private:
    void init();
    void init(RpgWorldBuilderScene* gameScene, MapTile* newTile);
};

