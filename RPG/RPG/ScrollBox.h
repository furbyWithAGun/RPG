#pragma once
#include "UiElement.h"
class ScrollBox : public UiElement
{
public:
    //attributes
    SDL_Colour arrowMoreColour;
    SDL_Colour arrowEndColour;
    SDL_Colour selectedColour;
    Sprite upArrowMore;
    Sprite upArrowEnd;
    Sprite downArrowMore;
    Sprite downArrowEnd;
    bool selectableElements;
    UiElement* selectedElement;
    std::unordered_map<UiElement*, int> elementValues;

    //constructors
    ScrollBox();
    ScrollBox(GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight);
    ScrollBox(int elementId, GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight);

    //methods
    void addElement(UiElement* newElement);
    void addElement(UiElement* newElement, int newElementValue);
    bool handleInput(InputMessage* message) override;
    int getSelectedElementValue();
    void draw() override;
    void clear();

private:
    void init();
    void updateElementsStatus();
};

