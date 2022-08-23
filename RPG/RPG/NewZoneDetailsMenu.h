#pragma once
#include "GameMenu.h"

class RpgWorldBuilderScene;

class NewZoneDetailsMenu : public GameMenu
{
public:
    //constructors
    NewZoneDetailsMenu();
    NewZoneDetailsMenu(RpgWorldBuilderScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);
    NewZoneDetailsMenu(RpgWorldBuilderScene* gameScene, int newId);

private:
    //methods
    RpgWorldBuilderScene* scene;
    void init();
    void init(RpgWorldBuilderScene* gameScene);
    void buildElements();
};

