#pragma once
#include "MenuButton.h"
#include "RpgWorldBuilderScene.h"

class SaveMapBuilderButton : public MenuButton
{
public:
    //attributes
    RpgWorldBuilderScene* scene;

    //constructors
    SaveMapBuilderButton();
    SaveMapBuilderButton(RpgWorldBuilderScene* gameScene, int buttonTextureKey);
    SaveMapBuilderButton(int elementId, RpgWorldBuilderScene* gameScene, int buttonTextureKey);

    //methods
    void onClick();
};

