#pragma once
#include "MenuButton.h"
#include "RpgWorldBuilderScene.h"
#include "BaseGameEngine.h"

class MapBuilderPortalButton : public MenuButton
{
public:
    //attributes
    RpgWorldBuilderScene* scene;
    int portalKey;

    //constructors
    MapBuilderPortalButton();
    MapBuilderPortalButton(RpgWorldBuilderScene* gameScene, int newPortalKey);
    MapBuilderPortalButton(int elementId, RpgWorldBuilderScene* gameScene, int newPortalKey);

    //methods
    void onClick();

private:
    void init();
    void init(RpgWorldBuilderScene* gameScene, int newPortalKey);
};

