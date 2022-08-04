#include "HoverToolTip.h"

HoverToolTip::HoverToolTip() : UiElement()
{
    init();
}

HoverToolTip::HoverToolTip(GameScene* gameScene, int xpos, int ypos, int elementWidth, int elementHeight) : UiElement(gameScene, xpos, ypos, elementWidth, elementHeight)
{
    init();
}

void HoverToolTip::update()
{
    if (parentElement->pointCollision(scene->controllerInterface->latestXpos, scene->controllerInterface->latestYpos))
    {
        disappearDelayTick = 0;
        displayDelayTick++;
    }
    else {
        disappearDelayTick++;
        displayDelayTick = 0;
    }

    if (displayDelayTick >= displayDelay)
    {
        active = true;
        xpos = scene->controllerInterface->latestXpos;
        ypos = scene->controllerInterface->latestYpos;
        for (auto element : subElements)
        {
            element->active = true;
        }
    }
    else if (disappearDelayTick >= disappearDelay)
    {
        active = false;
        for (auto element : subElements)
        {
            element->active = false;
        }
    }
}

void HoverToolTip::draw()
{
    if (active && parentElement->active)
    {
        Sprite::draw();
        if (displaySubElements)
        {
            for (auto element : subElements)
            {
                if (element->active) {
                    element->draw(xpos + element->xpos, ypos + element->ypos);
                }
            }

        }
    }
}

void HoverToolTip::init()
{
    displayDelay = 1;
    displayDelayTick = 0;
    disappearDelay = 1;
    disappearDelayTick = 0;
    parentElement = nullptr;
    active = false;
}
