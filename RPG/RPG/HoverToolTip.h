#pragma once
#include "UiElement.h"

class HoverToolTip : public UiElement
{
public:
    //attributes
    UiElement* parentElement;
    //constructors
    HoverToolTip();
    HoverToolTip(GameScene* gameScene, int xpos, int ypos, int elementWidth, int elementHeight);

    //methods
    void update() override;
    void draw() override;

private:
    //attributes
    int displayDelay;
    int displayDelayTick;
    int disappearDelay;
    int disappearDelayTick;

    //methods
    void init();
};

